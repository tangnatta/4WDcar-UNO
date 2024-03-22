#include <Arduino.h>

#define ENA 12
#define ENB 13
#define PWMA 10
#define PWMB 11

#define ECHO 6
#define TRIG 7

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}

long getDistance()
{
  digitalWrite(TRIG, 0);
  delayMicroseconds(2);
  digitalWrite(TRIG, 1);
  delayMicroseconds(5);
  digitalWrite(TRIG, 0);
  long duration = pulseIn(ECHO, 1);
  return microsecondsToCentimeters(duration);
}

void setup()
{
  // put your setup code here, to run once:
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);

  Serial.begin(115200);
}

void motorA(bool dir, int speed)
{
  digitalWrite(ENA, dir);
  analogWrite(PWMA, speed);
}

void motorB(bool dir, int speed)
{
  digitalWrite(ENB, dir);
  analogWrite(PWMB, speed);
  // delay(3000);
  // motorB(0,0);
}

void loop()
{
  // put your main code here, to run repeatedly:
  long dis = getDistance();
  Serial.println(dis);

  if (dis < 50)
  {
    motorA(1, 150);
    motorB(1, 150);
    delay(1000);
    motorA(1, 150);
    motorB(0, 150);
    delay(1000);
  }

  motorA(0, 255);
  motorB(0, 255);

  // motorB(0,255);
}
