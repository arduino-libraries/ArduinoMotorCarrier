#include "Battery.h"
#include "Common.h"

mc::Battery::Battery() {
}

int mc::Battery::getRaw() {
  int ret;
  getData(GET_RAW_ADC_BATTERY, (uint8_t*)&ret);
  return ret;
}

int mc::Battery::getConverted() {
  int ret;
  getData(GET_CONVERTED_ADC_BATTERY, (uint8_t*)&ret);
  return ret;
}

int mc::Battery::getFiltered() {
  int ret;
  getData(GET_FILTERED_ADC_BATTERY, (uint8_t*)&ret);
  return ret;
}
