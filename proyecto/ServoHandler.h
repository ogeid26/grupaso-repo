#ifndef SERVOCONTROL_H
#define SERVOCONTROL_H

#include <ESP32Servo.h>

// Declare the external variables and functions used for servo control
extern Servo servo1;
extern Servo servo2;
extern int servo1RD;
extern int flapSpeed;

void setupServos();      // Setup the servos
void incrementServo();   // Increment servo position
void decrementServo();   // Decrement servo position

#endif

