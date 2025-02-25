
#ifndef MOTORrr_H_
#define MOTORrr_H_

#include "std_types.h"

#define MOTOR_PORT PORTA
#define MOTOR_DDR DDRA

#define IN1 PA1 // Motor A control pin 1
#define IN2 PA2 // Motor A control pin 2
#define IN3 PA3 // Motor B control pin 1
#define IN4 PA4 // Motor B control pin 2
#define ENA PA0 // Enable pin for Motor A
#define ENB PA5 // Enable pin for Motor B

void Motor_Init(void) ;
void MotorA_Forward(void);
void MotorA_Backward(void);
void MotorB_Forward(void);
void MotorB_Backward(void);
void MotorA_Stop(void);
void MotorB_Stop(void);

#endif