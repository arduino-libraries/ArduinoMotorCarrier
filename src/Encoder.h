/*
  Encoder.h - Library for Arduino MKR Motor Shield
  Copyright (c) 2018 Arduino AG.  All right reserved.
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

#ifndef __ENCODER_H__
#define __ENCODER_H__

#include "Arduino.h"

namespace mc {

class Encoder {
  public:
    Encoder();
    int getRawCount();
    int getOverflowUnderflow();
    int getCountPerSecond();
    void resetCounter(long value);
    void setIrqOnCount(long value);
    void setIrqOnVelocity(long value, uint8_t margin = 2);
  private:
    int instance;
};
}

#endif
