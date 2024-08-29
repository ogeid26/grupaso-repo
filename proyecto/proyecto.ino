#include <ESP32Servo.h>

const int leftButtonPin = 21;
const int rightButtonPin = 22;

int leftLastState = HIGH;
int leftCurrentState;

int rightLastState = HIGH;
int rightCurrentState;

int ledPin = 27;

int servoPin = 17;

Servo servo;

void setup() {
  pinMode(leftButtonPin, INPUT_PULLUP);
  pinMode(rightButtonPin, INPUT_PULLUP);

  pinMode(ledPin, OUTPUT);

  servo.attach(servoPin, 500, 2400);
  int pos = 0;


  Serial.begin(115200);
}

void loop() {

  leftCurrentState = digitalRead(leftButtonPin);
  rightCurrentState = digitalRead(rightButtonPin);


  if (leftLastState == LOW && leftCurrentState == HIGH) {
    Serial.println("Botón 1 presionado");
    // for (pos = 0; pos <= 180; pos += 1) {
    // servo.write(pos);
    // delay(15);
    digitalWrite(ledPin, HIGH);
  }
   else {
    Serial.println("Botón 1 no presionado");
    //  for (pos = 180; pos >= 0; pos -= 1) {
    // servo.write(pos);
    // delay(15);
    digitalWrite(ledPin, LOW);
  }
  
  leftLastState = leftCurrentState;
  delay(200);
}
