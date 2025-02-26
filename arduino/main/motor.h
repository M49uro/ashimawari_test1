#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

extern volatile int motor2_duty_cycle;

void setup_motor_pins();
void setup_timer1();
void control_motor(int vector, int dir_pin, int pwm_pin, int motor_index);

#endif // MOTOR_H
