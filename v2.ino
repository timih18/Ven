#include <Servo.h>

Servo servo;
int serv = 0;

boolean last_button_status = false;

boolean servo_active = false;
boolean servo_increasing = true;
int servo_value = 90;
double servo_speed_up = 1.5;
double servo_speed_down = 1.0;

void setup() {
  servo.attach(4);
  servo.write(servo_value);
  
  pinMode(3, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  pinMode(5, OUTPUT);
  
  Serial.begin(9800);
}

void loop() {
  // ЗАДЕРЖКА
  delay (10);

  // ЧТЕНИЕ КНОПКИ
  boolean button_status = !digitalRead(3);
  if (button_status != last_button_status) {
    if (button_status) {
      servo_active = !servo_active;
    }
    last_button_status = button_status;
    if (!servo_active)
      digitalWrite(5, LOW);
  }


  // ОБРАБОТКА СЕРВО
  if (servo_active) {
    digitalWrite(5, HIGH);
    if (servo_increasing) {
      servo_value += servo_speed_up;
      servo.write(servo_value);
      if (servo_value >= 160)
        servo_increasing = false;
    } else {
      servo_value -= servo_speed_down;
      servo.write(servo_value);
      if (servo_value <= 20)
        servo_increasing = true;
    }
  }
}
