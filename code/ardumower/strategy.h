#include "robot.h"

class Strategy {
public:
    virtual void setNewMotorRPM(struct sensor_data& sens, struct speed_rpm& speed){}
};

enum LaneByLaneState {
    FORWARD
    , ROLL_CLOCKWISE
    , ROLL_COUNTERCLOCKWISE
};

#define SPEED_MAX_RPM 24
#define SPEED_SLOW_RPM (SPEED_MAX / 2)

class LaneByLane: public Strategy {
public:
    LaneByLane(struct user_config& config);
private:
    void setNewMotorRPMRoll(struct sensor_data& sens, struct speed_rpm& speed, enum LaneByLaneState dir);
    void setNewMotorRPMForward(struct sensor_data& sens, struct speed_rpm& speed);
    
    
    enum LaneByLaneState currentState;
    struct user_config* conf;
    enum LaneByLaneState lastRollDir;
    uint32_t smallerCurveTick;
    uint32_t largerCurveTick;
};
    
