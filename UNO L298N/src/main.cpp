#include <Arduino.h>

#define ENA 10
#define IN1 5
#define IN2 4
#define ENB 11
#define IN3 13
#define IN4 12

#define ECHO 6
#define TRIG 7

long microsecondsToCentimeters(long microseconds)
{
  // ความเร็วเสียงเดินทางในอากาศคือ 340 เมตร/วินาที หรือ 29 ไมโครวินาที ต่อเซนติเมตร
  // เวลาที่ Ping ออกไปกระทบวัตถุจนถึงกลับมาที่ตัวรับ ใช้หาระยะทางได้
  // วัตถุอยู่มีระยะทางเท่ากับครึ่งหนึ่งของเวลาที่จับได้
  // เขียนเป็นสมการคำนวนระยะทาง ได้ดังนี้
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
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(115200);
}

void motorA(bool dir, int speed)
{
  digitalWrite(IN1, dir);
  digitalWrite(IN2, !dir);
  analogWrite(ENA, speed);
}

void motorB(bool dir, int speed)
{
  digitalWrite(IN3, dir);
  digitalWrite(IN4, !dir);
  analogWrite(ENB, speed);
  // delay(3000);
  // motorB(0,0);
}

void loop()
{
  // put your main code here, to run repeatedly:
  long dis = getDistance();
  Serial.println(dis);

  if (dis < 2)
  {
    motorA(1, 255);
    motorB(1, 255);
    delay(1000);
    motorA(1, 255);
    motorB(0, 255);
    delay(1000);
  }

  motorA(0, 255);
  motorB(0, 255);

  // motorB(0,255);
}
