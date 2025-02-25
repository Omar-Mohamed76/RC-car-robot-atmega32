
#include <avr/io.h>
#include <util/delay.h>
#include "motor.h"


void Motor_Init() {
    MOTOR_DDR |= (1 << IN1) | (1 << IN2) | (1 << IN3) | (1 << IN4) | (1 << ENA) | (1 << ENB); // Set pins as output
    MOTOR_PORT &= ~((1 << IN1) | (1 << IN2) | (1 << IN3) | (1 << IN4)); // Initialize all motor control pins to 0
    MOTOR_PORT |= (1 << ENA) | (1 << ENB); // Enable both motors (ENA and ENB high)
}

void MotorA_Forward() {
    MOTOR_PORT |= (1 << IN1);  // IN1 = HIGH
    MOTOR_PORT &= ~(1 << IN2); // IN2 = LOW
}

void MotorA_Backward() {
    MOTOR_PORT &= ~(1 << IN1); // IN1 = LOW
    MOTOR_PORT |= (1 << IN2);  // IN2 = HIGH
}

void MotorB_Forward() {
    MOTOR_PORT |= (1 << IN3);  // IN3 = HIGH
    MOTOR_PORT &= ~(1 << IN4); // IN4 = LOW
}

void MotorB_Backward() {
    MOTOR_PORT &= ~(1 << IN3); // IN3 = LOW
    MOTOR_PORT |= (1 << IN4);  // IN4 = HIGH
}

void MotorA_Stop() {
    MOTOR_PORT &= ~((1 << IN1) | (1 << IN2)); // IN1 = LOW, IN2 = LOW
}

void MotorB_Stop() {
    MOTOR_PORT &= ~((1 << IN3) | (1 << IN4)); // IN3 = LOW, IN4 = LOW
}
/*
int main(void) {
    Motor_Init();

    while (1) {
        // Move Motor A forward and Motor B forward
        MotorA_Forward();
        MotorB_Forward();
        _delay_ms(2000); // Delay for 2 seconds

        // Stop both motors
        MotorA_Stop();
        MotorB_Stop();
        _delay_ms(1000); // Delay for 1 second

        // Move Motor A backward and Motor B backward
        MotorA_Backward();
        MotorB_Backward();
        _delay_ms(2000); // Delay for 2 seconds

        // Stop both motors
        MotorA_Stop();
        MotorB_Stop();
        _delay_ms(1000); // Delay for 1 second
    }

    return 0;
}
*/