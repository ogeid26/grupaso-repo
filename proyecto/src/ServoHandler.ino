#include "ServoHandler.h"

// Initialize the servos
Servo servo1;
Servo servo2;

int servo1RD = 90;  // Initial rotation for servo 1
int flapSpeed = 3;  // Speed of the servo

void setupServos() {
    servo1.attach(17, 500, 2400);  // Attach servo1 to pin 17
    servo2.attach(16, 500, 2400);  // Attach servo2 to pin 16

    servo1.write(servo1RD);  // Set initial position for servo1
    servo2.write(servo1RD);  // Set initial position for servo2
}

void incrementServo() {
    if (servo1RD < 180) {
        servo1RD += flapSpeed;      // Increment the rotation
        servo1.write(servo1RD);     // Write the new rotation to servo1
        servo2.write(servo1RD);     // Write the new rotation to servo2
    }
}

void decrementServo() {
    if (servo1RD > 0) {
        servo1RD -= flapSpeed;      // Decrement the rotation
        servo1.write(servo1RD);     // Write the new rotation to servo1
        servo2.write(servo1RD);     // Write the new rotation to servo2
    }
}
