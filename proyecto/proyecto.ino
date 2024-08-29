
#include <ESP32Servo.h>

const int servoPin = 18;
const int buttonPin = 27;

int lastButtonState = HIGH;  // Last state of the button
int currentButtonState;      // Current state of the button
int pressCount = 0;          // Counter for button presses

Servo servo;

void setup() {
  Serial.begin(9600);
  servo.attach(servoPin, 500, 2400); // Attach the servo to pin with min and max pulse width
  pinMode(buttonPin, INPUT_PULLUP);  // Set button pin as input with pull-up resistor
}

void loop() {
  currentButtonState = digitalRead(buttonPin);
  
  // Print the current state of the button for debugging
  Serial.print("Button State: ");
  Serial.println(currentButtonState);

  // Check if button state has changed from HIGH to LOW
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    // Button was pressed, increment pressCount and print its value
    pressCount++;
    Serial.print("Button pressed! Press count: ");
    Serial.println(pressCount);
    
    // Optional: Add debounce delay
   // delay(200);
  }
  
  lastButtonState = currentButtonState; // Save the current button state

  // Optional: Add logic for servo movement if needed
  // For example, you could use the pressCount to control servo movement
  // Example:
  /*
  if (pressCount % 2 == 0) {
    // Sweep up
    for (int pos = 0; pos <= 180; pos += 1) {
      servo.write(pos);
      delay(15);
    }
  } else {
    // Sweep down
    for (int pos = 180; pos >= 0; pos -= 1) {
      servo.write(pos);
      delay(15);
    }
  }
  */
}
