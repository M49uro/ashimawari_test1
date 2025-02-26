#include "serial_read.h"

String inputString = "";         // 受信した文字列を一時的に保存する変数
boolean stringComplete = false;  // 受信が完了したかどうかのフラグ

int vector0 = 0;
int vector1 = 0;
int vector2 = 0;

void setup_serial() {
  Serial.begin(9600);  // シリアル通信の初期化
  inputString.reserve(200);  // メモリ確保
  Serial.println("Arduino is ready to receive data.");
}

void read_serial() {
  if (stringComplete) {
    // パケットの解析
    int startIdx = inputString.indexOf('<');
    int endIdx = inputString.indexOf('>');

    if (startIdx >= 0 && endIdx >= 0) {
      String data = inputString.substring(startIdx + 1, endIdx);
      sscanf(data.c_str(), "%d,%d,%d", &vector0, &vector1, &vector2);

      // 数値の範囲をチェックし、-100%から100%に制限
      vector0 = constrain(vector0, -100, 100);
      vector1 = constrain(vector1, -100, 100);
      vector2 = constrain(vector2, -100, 100);

      // デバッグ用にシリアル出力 (コメントアウト)
      // Serial.println(String("Received vectors: ") + vector0 + "%, " + vector1 + "%, " + vector2 + "%");
    }

    // 受信した文字列をクリア
    inputString = "";
    stringComplete = false;
  }
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == '>') {
      stringComplete = true;
    }
  }
}
