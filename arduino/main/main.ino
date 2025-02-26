#include "serial_read.h"
#include "motor.h"

// motor.ino で定義されたピン変数を宣言
extern const int motor0_dir_pin;
extern const int motor0_pwm_pin;
extern const int motor1_dir_pin;
extern const int motor1_pwm_pin;
extern const int motor2_dir_pin;
extern const int motor2_pwm_pin;
extern volatile int motor2_duty_cycle;

void setup() {
  setup_serial();
  setup_motor_pins();
}

void loop() {
  read_serial();

  control_motor(vector0, motor0_dir_pin, motor0_pwm_pin, 0);
  control_motor(vector1, motor1_dir_pin, motor1_pwm_pin, 1);
  control_motor(vector2, motor2_dir_pin, motor2_pwm_pin, 2);

  // データを指定された形式でシリアルモニターに表示
  Serial.println(String("Received vectors: ") + vector0 + "%, " + vector1 + "%, " + vector2 + "%");

  // 受け取ったベクトル、DIR、PWMのデューティー比をシリアルモニターに表示
  Serial.print("v0: ");
  Serial.print(vector0);
  Serial.print(", dir0: ");
  Serial.print(digitalRead(motor0_dir_pin));
  Serial.print(", pwm0: ");
  Serial.print(OCR1A);  // PWM0の表示
  Serial.print(", v1: ");
  Serial.print(vector1);
  Serial.print(", dir1: ");
  Serial.print(digitalRead(motor1_dir_pin));
  Serial.print(", pwm1: ");
  Serial.print(OCR1B);  // PWM1の表示
  Serial.print(", v2: ");
  Serial.print(vector2);
  Serial.print(", dir2: ");
  Serial.print(digitalRead(motor2_dir_pin));
  Serial.print(", pwm2: ");
  Serial.println(motor2_duty_cycle);  // PWM2の表示
}
