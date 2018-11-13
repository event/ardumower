#include "strategy.h"

void LaneByLane::LaneByLane(struct user_config& config) {
    currentState = FORWARD;
    conf = config;
    lastRollDir = ROLL_CLOCKWISE == conf.firstRollDir ? ROLL_COUNTERCLOCKWISE : ROLL_CLOCKWISE;
    // at the edge robot would make a curve which would place it's centre where the wheel was before
    //   and reversed facing. For this one wheel makes curve, and other wheel makes 3x smaller curve
    smallerCurveTick = conf.odometryWheelBaseCm / 4 / conf.wheelDiameterCm
        * conf.ticksPerRevolution * conf.smallerCurveAdjustment;
    largerCurveTick = smallerCurveTick * 3;
}

void LaneByLane::setNewMotorRPM(struct sensor_data& sens, struct speed_rpm& speed) {
    if (FORWARD == currentState) {
        currentState = setNewMotorRPMForward(sens, new_speed);
    } else {
        currentState = setNewMotorRPMRoll(sens, new_speed, currentState);
    }
}

void LaneByLane::configureRoll(int* biggerSpeed, int* lowerSpeed, int* biggerOdoEnd, int* lowerOdoEnd) {
    *biggerSpeed = SPEED_MAX;
    *lowerSpeed = SPEED_MAX / 3;
    *biggerOdoEnd += largerCurveTicks;
    *lowerOdoEnd += smallerCurveTicks;
}


enum LaneByLaneState LaneByLane::setNewMotorRPMForward(struct sensor_data& sens, struct speed_rpm& speed) {
    if (sens.sonarDistCenter < conf.sonarDistStop
        || sens.sonarDistLeft < conf.sonarDistStop
        || sens.sonarDistRight < conf.sonarDistStop)
    {
        odoEndLeft = sens.odoLeft;
        odoEndRight = sens.odoRight;
        if (lastRollDir == ROLL_CLOCKWISE) {
            configureRoll(&speed.right, &speed.left, &odoEndRight, &odoEndLeft);
            return ROLL_COUNTERCLOCKWISE;
        } else if (lastRollDir == ROLL_COUNTERCLOCKWISE) {
            configureRoll(&speed.left, &speed.right, &odoEndLeft, &odoEndRight);
            return ROLL_CLOCKWISE;
        }
    }
    if (sens.sonarDistCenter < conf.sonarDistSlow
        || sens.sonarDistLeft < conf.sonarDistSlow
        || sens.sonarDistRight < conf.sonarDistSlow)
    {
        speed.left = SPEED_SLOW;
        speed.right = SPEED_SLOW;
    } else {
        speed.left = SPEED_MAX;
        speed.right = SPEED_MAX;
    }
    return FORWARD;
}

enum LaneByLaneState LaneByLane::setNewMotorRPMRoll(struct sensor_data& sens
                                                    , struct speed_rpm& speed, enum LaneByLaneState dir) {
    if (sens.odoLeft < odoEndLeft
        && sens.odoRight < odoEndRight)
    {
        return dir;
    }
    //TODO: for clockwise roll check right sonar for obstacle; for counterclockwise roll,
    //        check left sonar for obstacle
    lastRollDir = dir;
    return FORWARD;
}
