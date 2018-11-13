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


#include "robot2.h"


Robot::Robot() {
    name = "Snaker";
    loadUserConfig(config);
    strategy = new LaneByLane(config);
}

void Robot::loop() {
    struct sensor_data sens;
    struct speed_rpm speed;

    collectSensorData(sens);
    strategy.setNewMotorRPM(sens, speed);
    updateSpeed(speed);
    // TODO: look after battery charge here as well
    // TODO: look after various errors and power failures
    // TODO: button support is required as well
}

void Robot::collectSensorData(struct sensor_data& sens) {
    sens.sonarDistCenter = getSonarDist(CENTER_SONAR);
    sens.sonarDistLeft = getSonarDist(LEFT_SONAR);
    sens.sonarDistRight = getSonarDist(RIGHT_SONAR);
    sens.odoLeft = getOdo(ODO_LEFT);
    sens.odoRight = getOdo(ODO_RIGHT);
}

void Robot::updateSpeed(struct speed_rpm& speed) {
    
}

