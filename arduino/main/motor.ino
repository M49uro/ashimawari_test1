#include "motor.h"

// ピンの定義
const int motor0_dir_pin = 2;
const int motor0_pwm_pin = 9;  // OC1A ピン
const int motor1_dir_pin = 4;
const int motor1_pwm_pin = 10;  // OC1B ピン
const int motor2_dir_pin = 6;
const int motor2_pwm_pin = 11; // 手動でPWM生成用のピン

volatile int motor2_duty_cycle = 0;

void setup_motor_pins() {
  pinMode(motor0_dir_pin, OUTPUT);
  pinMode(motor0_pwm_pin, OUTPUT);
  pinMode(motor1_dir_pin, OUTPUT);
  pinMode(motor1_pwm_pin, OUTPUT);
  pinMode(motor2_dir_pin, OUTPUT);
  pinMode(motor2_pwm_pin, OUTPUT);

  // タイマーの設定
  setup_timer1();
}

void setup_timer1() {
  // タイマー1の設定（ファストPWM、ICR1をトップ値とする）
  TCCR1A = (1 << WGM11) | (1 << COM1A1) | (1 << COM1B1);
  TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11); // 分周比8で10kHzに設定
  TCNT1 = 0;  // カウンタクリア
  ICR1 = 199; // 周波数設定用（10kHz）
  TIMSK1 |= (1 << TOIE1); // オーバーフロー割り込み許可
}

void control_motor(int vector, int dir_pin, int pwm_pin, int motor_index) {
  int dir_value;
  int duty_cycle;

  if (vector >= 0) {
    digitalWrite(dir_pin, HIGH);  // 正転
    dir_value = 1;
  } else {
    digitalWrite(dir_pin, LOW);   // 逆転
    dir_value = 0;
    vector = -vector;             // ベクトルの絶対値を取得
  }

  // PWMのデューティー比を計算 (ベクトルの絶対値をそのまま199のduty比に掛け合わせ)
  duty_cycle = (vector * 199) / 100; // 0から199までの範囲にスケーリング

  if (motor_index == 0) {
    OCR1A = duty_cycle; // タイマー1の出力比較レジスタAにデューティー比を設定
  } else if (motor_index == 1) {
    OCR1B = duty_cycle; // タイマー1の出力比較レジスタBにデューティー比を設定
  } else if (motor_index == 2) {
    motor2_duty_cycle = duty_cycle; // 手動でPWM生成
  }
}

// タイマー1のオーバーフローハンドラ
ISR(TIMER1_OVF_vect) {
  static int counter = 0;
  counter++;
  
  if (counter <= motor2_duty_cycle) {
    digitalWrite(motor2_pwm_pin, HIGH);
  } else {
    digitalWrite(motor2_pwm_pin, LOW);
  }
  
  if (counter >= 199) {
    counter = 0;
  }
}
