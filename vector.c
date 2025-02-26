#include "vector.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>  // 追加

void init_vector() {
    // 初期化処理（必要に応じて追加）
}

void convert_to_vectors(int x, int y, int* vectors) {
    // ノイズを減少させるための閾値
    const int NOISE_THRESHOLD = 5;

    // ノイズフィルタリング
    if (abs(x) < NOISE_THRESHOLD) x = 0;
    if (abs(y) < NOISE_THRESHOLD) y = 0;

    // ベクトル変換
    vectors[0] = (int)(x * cos(0) - y * sin(0));         // 0度のベクトル
    vectors[1] = (int)(x * cos(2 * M_PI / 3) - y * sin(2 * M_PI / 3));  // 120度のベクトル
    vectors[2] = (int)(x * cos(4 * M_PI / 3) - y * sin(4 * M_PI / 3));  // 240度のベクトル

    // 正規化して-100から100の範囲に変換
    for (int i = 0; i < 3; i++) {
        vectors[i] = (vectors[i] * 100) / 128;  // 正規化
        if (vectors[i] > 100) vectors[i] = 100;
        if (vectors[i] < -100) vectors[i] = -100;
    }
}
