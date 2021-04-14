/*
  Battery.cpp - Library for Arduino Motor Carriers
  Copyright (c) 2018-2019 Arduino AG.  All right reserved.
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

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
