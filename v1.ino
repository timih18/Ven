#include <Servo.h>

Servo servo;
int serv = 0;
boolean butt_flag = 0;
boolean butt;
boolean motor_flag = 0;

void setup() {
  servo.attach(4);
  pinMode(3, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  pinMode(5, OUTPUT);
  Serial.begin(9800);
}

void loop() {
  butt = !digitalRead(3);
  
  if (butt == 1 && butt_flag == 0) {
    butt_flag = 1
    motor_flag = !motor_flag;
    digitalWrite(13, motor_flag);
    digitalWrite(5, motor_flag);

    while (butt_flag) {
      while (serv <= 120) {
        servo.write(serv);
        delay(37.5);
        serv += 2.5;
      }
      while (serv >= 0) {
        servo.write(serv);
        delay(37.5);
        serv -= 2.5;
      }
    }
  }
  
  if (butt == 0 && butt_flag == 1) {
    butt_flag = 0;
  }
  Serial.println(butt_flag);
    delay (1000);
}
