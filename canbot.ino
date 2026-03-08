#include <Servo.h>

#define JOYSTICK_X_PIN A0
#define JOYSTICK_Y_PIN A1
#define JOYSTICK_PUSH_PIN 2
#define YAW_PIN 3
#define CLAW_PIN 4
#define ARM_PIN 5
#define DEAD_ZONE 100
#define STEP_SIZE 1

Servo yaw;
Servo arm;
Servo claw;

bool clawOpened;

int xValue, yValue, inputAngleX, inputAngleY, yawAngle, armAngle;

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
  
  if(digitalRead(JOYSTICK_PUSH_PIN) == LOW) {
    clawOpened = !clawOpened;

    if(clawOpened) claw.write(0);
    else claw.write(20);
  }

  // X Axis Control
  if (xValue > 512 + DEAD_ZONE) {
    yawAngle += STEP_SIZE;
  }
  else if (xValue < 512 - DEAD_ZONE) {
    yawAngle -= STEP_SIZE;
  }

  // Y Axis Control
  if (yValue > 512 + DEAD_ZONE) {
    armAngle += STEP_SIZE;
  }
  else if (yValue < 512 - DEAD_ZONE) {
    armAngle -= STEP_SIZE;
  }

  yaw.write(constrain(yawAngle, 0, 180));
  arm.write(constrain(armAngle, 0, 180));

  delay(20);
}