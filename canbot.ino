#include <Servo.h>

#define JOYSTICK_X_PIN A0
#define JOYSTICK_Y_PIN A1
#define JOYSTICK_PUSH_PIN 7
#define ARM_PIN 8
#define YAW_PIN 9
#define CLAW_PIN 10

Servo yaw;
Servo arm;
Servo claw;

bool clawOpened;

int xValue, yValue, angleX, angleY;

void setup() {
  yaw.attach(YAW_PIN);
  arm.attach(ARM_PIN);
	claw.attach(CLAW_PIN);
  clawOpened = false;

  pinMode(JOYSTICK_X_PIN, INPUT);
  pinMode(JOYSTICK_Y_PIN, INPUT);
  pinMode(JOYSTICK_PUSH_PIN, INPUT_PULLUP);
}

void loop() {
  xValue = analogRead(JOYSTICK_X_PIN);
  yValue = analogRead(JOYSTICK_Y_PIN);
  
  angleX = map(xValue, 0, 1023, 0, 180);
  angleY = map(yValue, 0, 1023, 0, 180);

  yaw.write(angleX);
  arm.write(angleY);

  if(digitalRead(JOYSTICK_PUSH_PIN) == LOW) {
    clawOpened = !clawOpened;

    if(clawOpened) claw.write(0);
    else claw.write(120);
  }

  delay(20);
}