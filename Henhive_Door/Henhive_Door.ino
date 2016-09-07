#include <Stepper.h>

// THIS IS STEPS PER REVOLUTION BEFORE GEARS
#define STEPS_PER_REVOLUTION_INTERNAL 32

// GEAR RATIO IS 1:64, SO 32 * 64 = 2048
#define STEPS_PER_REVOLUTION 32 * 64

// 12 white/green -> IN4
// 11 green -> IN3
// 9 white/blue -> IN2
// 8 blue -> IN1

Stepper motor(STEPS_PER_REVOLUTION_INTERNAL, 8, 11, 9, 12 );

int lightPin = A0;
int ledPin = 13;
int buttonPin = 7;
bool door_is_open = false;
bool door_is_moving = false;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  motor.setSpeed(700);
}

void closeTheDoor() {
  door_is_moving = true;
  digitalWrite(ledPin, LOW);
  motor.step(STEPS_PER_REVOLUTION * 4);
  door_is_open = false;
  digitalWrite(ledPin, HIGH);
  door_is_moving = false;
}

void openTheDoor() {
  door_is_moving = true;
  digitalWrite(ledPin, LOW);
  motor.step(-STEPS_PER_REVOLUTION * 4);
  door_is_open = true;
  digitalWrite(ledPin, HIGH);
  door_is_moving = false;
}
void loop() {
  digitalWrite(ledPin, HIGH);
  if (digitalRead(buttonPin) == HIGH) {
    if(not door_is_moving) {
      if (door_is_open) {
        closeTheDoor();
      } else {
        openTheDoor();
      }
    }
  } 

//  if (analogRead(lightPin) > 200) {
//    if (!door_is_open) {
//      openTheDoor();
//      delay(3000);
//    }
//  }
//  
//  if (analogRead(lightPin) < 50) {
//    if (door_is_open) {
//      closeTheDoor();
//      delay(3000);
//    }
//  }

  delay(100);
  
  digitalWrite(13, LOW);    
}
