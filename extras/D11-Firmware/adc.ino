#if 0

#define WAIT_ADC_SYNC while (ADC->STATUS.bit.SYNCBUSY) {}
#define WAIT_ADC_RESET while (ADC->CTRLA.bit.SWRST) {}

void adc_reset() {
  WAIT_ADC_SYNC
  ADC->CTRLA.bit.ENABLE = 0;  //disable DAC
  WAIT_ADC_SYNC
  ADC->CTRLA.bit.SWRST = 1;   //reset ADC
  WAIT_ADC_SYNC
  WAIT_ADC_RESET
}

void adc_init() {
  //make sure the digital interface clock is enabled (should be already after reset)
  PM->APBCMASK.reg |= PM_APBCMASK_ADC;

  // Enable ADC conversion clock, take from GCLK0
  GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID( GCM_ADC ) |
                      GCLK_CLKCTRL_GEN_GCLK0     |
                      GCLK_CLKCTRL_CLKEN ;

  //reset ADC to defaults
  adc_reset();

  //Control B: Prescaler (/256), resolution selection (16 bit), correction enable (no), freerun mode (no)
  ADC->CTRLB.reg = 0x610;
  WAIT_ADC_SYNC

  //sample time in half clock cycles will be set before conversion, set to max (slow but high impedance)
  ADC->SAMPCTRL.reg = 0x3f;
  WAIT_ADC_SYNC

  //enable accumulation / averaging: 1024 samples to 16 bit resolution
  ADC->AVGCTRL.reg = 0x0a;
  WAIT_ADC_SYNC

  adc_read(0x18, true);  //dummy read a generic channel, discard result
}

uint32_t adc_read(uint8_t channel, bool onevolt) {

  if (onevolt) { //one volt full scale: use internal 1.0V reference, gain 1
    ADC->INPUTCTRL.bit.GAIN = ADC_INPUTCTRL_GAIN_1X_Val;
    ADC->REFCTRL.bit.REFSEL = ADC_REFCTRL_REFSEL_INT1V_Val;
    WAIT_ADC_SYNC
    ADC->INPUTCTRL.reg = channel | 0x1800; //select channel as MUXPOS, MUXNEG = internal GND
    WAIT_ADC_SYNC
  } else {  //3.3V full: use half supply as reference, set gain to 0.5
    ADC->INPUTCTRL.bit.GAIN = ADC_INPUTCTRL_GAIN_DIV2_Val;
    ADC->REFCTRL.bit.REFSEL = ADC_REFCTRL_REFSEL_INTVCC1_Val;
    WAIT_ADC_SYNC
    ADC->INPUTCTRL.reg = channel | 0x1900; //select channel as MUXPOS, MUXNEG = IO GND
    WAIT_ADC_SYNC
  }  
  
  ADC->SAMPCTRL.reg = 0x3f;            //make sure we're sampling slowly
  WAIT_ADC_SYNC

  ADC->CTRLA.bit.ENABLE = 1;              //enable ADC
  WAIT_ADC_SYNC

  ADC->SWTRIG.bit.START = 1;                // Start ADC conversion
  while (!(ADC->INTFLAG.bit.RESRDY)) {}     //wait until ADC conversion is done
  WAIT_ADC_SYNC
  uint32_t val = ADC->RESULT.reg;

  ADC->INTFLAG.reg = ADC_INTFLAG_RESRDY;  // clear result ready flag
  WAIT_ADC_SYNC
  
  ADC->CTRLA.bit.ENABLE = 0; //disable ADC
  WAIT_ADC_SYNC

  return val;
}


#define ADC_TEMP_CHANNEL 0x18

void temp_init() {
  SYSCTRL->VREF.reg |= SYSCTRL_VREF_TSEN;   //enable temperature sensor, route to ADC
  adc_init();
}

uint32_t temp_read_raw() {  //returns 16 bit.
  return adc_read(ADC_TEMP_CHANNEL, true);
}

int32_t temp_raw_to_mdeg(uint32_t raw) {
  int32_t adc = raw;
  //use device factory calibration values for temperature conversion (simplified)
  uint32_t* tmpLogBase = (uint32_t*)0x00806030;
  uint32_t tmpLog0 = tmpLogBase[0];
  uint32_t tmpLog1 = tmpLogBase[1];
  uint8_t roomInt = tmpLog0 & 0xff;
  uint8_t roomFrac = (tmpLog0 >> 8) & 0x0f;
  uint8_t hotInt = (tmpLog0 >> 12) & 0xff;
  uint8_t hotFrac = (tmpLog0 >> 20) & 0x0f;
  int32_t roomADC = ((tmpLog1 >> 8) & 0xfff) << 4;
  int32_t hotADC = ((tmpLog1 >> 20) & 0xfff) << 4;
  int32_t roomMdeg = 1000 * roomInt + 100 * roomFrac;
  int32_t hotMdeg = 1000 * hotInt + 100 * hotFrac;
  int32_t mdeg = roomMdeg + ((hotMdeg-roomMdeg) * (adc-roomADC)) / (hotADC-roomADC);
  return mdeg;
}

#endif
