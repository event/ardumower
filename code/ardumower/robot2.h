/*
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
  

*/

#ifndef ROBOT_H
#define ROBOT_H

#include <Arduino.h>
#include <Wire.h>  
#ifdef __AVR__
// Arduino Mega
#include <EEPROM.h>
#endif

#include "drivers.h"
#include "pid.h"
#include "adcman.h"
#include "pfod.h"
#include "RunningMedian.h"

#define VER "Snaker 0.1"

class Robot
{
public:    
    String name;

    Robot();
    void loop();
private:
    void collectSensorData(struct sensor_data& sens);
    void updateSpeed(struct speed_rpm& speed);
    
    struct user_config config;
    Strategy strategy;
}    


