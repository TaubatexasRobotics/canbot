#include <Servo.h>

#define JOYSTICK_X_PIN A0
#define JOYSTICK_Y_PIN A1
#define ANALOG_BUTTON_PIN A4
#define ARM_PIN 10
#define YAW_PIN 9
#define CLAW_PIN 8

Servo yaw;
Servo arm;
Servo claw;

int xValue, yValue, angleX, angleY;

void setup() {
  yaw.attach(YAW_PIN);
  arm.attach(ARM_PIN);
	claw.attach(CLAW_PIN);

  pinMode(JOYSTICK_X_PIN, INPUT);
  pinMode(JOYSTICK_Y_PIN, INPUT);
}

void loop() {
  xValue = analogRead(JOYSTICK_X_PIN);
  yValue = analogRead(JOYSTICK_Y_PIN);
  
  angleX = map(xValue, 0, 1023, 0, 180);
  angleY = map(yValue, 0, 1023, 0, 180);

  yaw.write(angleX);
}