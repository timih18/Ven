#include <Servo.h>


#define SERVO_PIN          4
#define SERVO_SPEED_UP   1.5
#define SERVO_SPEED_DOWN 1.0
#define SERVO_MIN         20
#define SERVO_MAX        160

#define MOTOR_PIN          5
#define BUTTON_PIN         3


Servo servo;

boolean last_button_status = false;

boolean servo_active = true;
boolean servo_increasing = true;
int servo_value = 90;
double servo_speed_up = 1.5;
double servo_speed_down = 1.0;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(15, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  delay (10);

  // ЧТЕНИЕ КНОПКИ
  boolean button_status = !digitalRead(BUTTON_PIN);
  if (button_status != last_button_status) {
    if (button_status) {
      servo_active = !servo_active;
    }
    last_button_status = button_status;
    if (servo_active) {
      Serial.println("Activating");
      digitalWrite(MOTOR_PIN, HIGH);
      servo.attach(SERVO_PIN);
    } else {
      Serial.println("Disactivating");
      digitalWrite(MOTOR_PIN, LOW);
      servo.detach();
    }
  }
  
  // ОБРАБОТКА СЕРВО
  if (servo_active) {
    Serial.println(SERVO_PIN);
    if (servo_increasing) {
      servo_value += SERVO_SPEED_UP;
      servo.write(servo_value);
      if (servo_value >= SERVO_MAX) {
        servo_increasing = false;
      }
    } else {
      servo_value -= SERVO_SPEED_DOWN;
      servo.write(servo_value);
      if (servo_value <= SERVO_MIN) {
        servo_increasing = true;
      }
    }
  }
}
