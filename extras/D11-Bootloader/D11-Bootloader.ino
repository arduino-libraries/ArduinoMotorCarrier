#include <Wire.h>
#include "reset.h"
#include "Sodaq_wdt.h"

#define I2C_ADDRESS 0x09
#define LED_BUILTIN 0

extern uint16_t PAGE_SIZE;
extern uint32_t dest_addr;
extern volatile uint32_t app_start_address;

extern uint32_t *flash_ptr;
volatile uint8_t buffer[64];
volatile int buf_available = 0;

inline void setup_ptrs()  __attribute__((always_inline));
inline void erase_all() __attribute__((always_inline));
inline void nvm_write_buffer(uint32_t destination_address, const uint8_t *buffer, uint16_t length) __attribute__((always_inline));
inline void nvm_erase_row(const uint32_t row_address, uint32_t PAGE_SIZE) __attribute__((always_inline));

volatile bool stay_in_bootloader = false;

void requestEvent() {
  Wire.write(dest_addr);
}

static volatile uint8_t command;
static volatile uint8_t last_crc;

void receiveEvent(int howMany) {

  command = Wire.read();
  if (command == 'r') {
    stay_in_bootloader = true;
    while (Wire.available()) {
      Wire.read();
    }
    return;
  }

  if (command == 'x') {
    digitalWrite(LED_BUILTIN, HIGH);
    stay_in_bootloader = false;
  }

  if (command == 'w') {
    last_crc = (uint8_t)Wire.read();
    while (Wire.available() && buf_available < 64) {
      buffer[buf_available++] = (uint8_t)Wire.read();
    }
    return;
  }

  // empty the buffer in case of spurious data
  while (Wire.available()) {
    Wire.read();
  }
}

void setup() {
  // put your setup code here, to run once:
  Wire.begin(I2C_ADDRESS);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(3, INPUT_PULLUP);

  setup_ptrs();
  sodaq_wdt_enable(WDT_PERIOD_2X);

  int start = millis();

  if (system_get_reset_cause() == SYSTEM_RESET_CAUSE_WDT) {
    stay_in_bootloader = true;
  }

  while (millis() - start < 100) {
    if (stay_in_bootloader) {
      erase_all();
      break;
    }
  }

  if (*flash_ptr != 0xFFFFFFFF && !stay_in_bootloader) {
    digitalWrite(LED_BUILTIN, HIGH);
    boot_app();
  }
}

int status = HIGH;
int next = 0;

void loop() {

  if ((millis() % 1000 > 500) && ((millis() / 1000) % 2 != status)) {
    digitalWrite(LED_BUILTIN, status);
    status = (millis() / 1000) % 2;
  }

  if (sodaq_wdt_flag) {
    sodaq_wdt_flag = false;
    sodaq_wdt_reset();
  }

  if (stay_in_bootloader == false) {
    NVIC_SystemReset();
  }

  if (buf_available == 64) {

    uint8_t crc = 0;

    for (int i = 0; i < 64; i++) {
      crc ^= buffer[i];
    }

    if (crc != last_crc) {
      buf_available = 0;
      return;
    }

    noInterrupts();
    nvm_write_buffer(dest_addr, (const uint8_t*)buffer, PAGE_SIZE);
    dest_addr += PAGE_SIZE;
    buf_available = 0;
    interrupts();
  }
}
