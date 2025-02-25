#include "movement.h"

void Move_Forward() {
    MotorA_Forward();
    MotorB_Forward();
}

void Move_Backward() {
    MotorA_Backward();
    MotorB_Backward();
}

void Move_Left() {
    MotorA_Backward();
    MotorB_Forward();
}

void Move_Right() {
    MotorA_Forward();
    MotorB_Backward();
}

void stop() {
    MotorA_Stop();
    MotorB_Stop();
}