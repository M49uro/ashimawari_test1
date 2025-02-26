#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sched.h>
#include "ps4.h"
#include "vector.h"
#include "serial.h"

void* read_ps4_data(void* arg) {
    while (1) {
        // Dualshock4のデータ取得
        PS4Data data = get_ps4_data();
        printf("Received data: x = %d, y = %d\n", data.x, data.y);

        // ベクトル変換
        int vectors[3];
        convert_to_vectors(data.x, data.y, vectors);
        printf("Vectors: %d%%, %d%%, %d%%\n", vectors[0], vectors[1], vectors[2]);

        // シリアル通信で送信
        send_serial_data(vectors, 3);

        // 遅延を最小限に
        usleep(500);  // 500マイクロ秒の遅延
    }
    return NULL;
}

#include <stdio.h>
#include <unistd.h> 
#include "ps4.h"
#include "vector.h"
#include "serial.h"

int main() {
    // 初期化
    init_ps4();
    init_vector();
    init_serial();

    int counter = 0;  // カウンタを追加
    while (1) {
        // Dualshock4のデータ取得
        PS4Data data = get_ps4_data();

        // ここでデバッグメッセージを減らす
        if (counter % 10 == 0) {  // 10回に1回表示
            printf("Received data: x = %d, y = %d\n", data.x, data.y);

            // ベクトル変換
            int vectors[3];
            convert_to_vectors(data.x, data.y, vectors);
            printf("Vectors: %d%%, %d%%, %d%%\n", vectors[0], vectors[1], vectors[2]);

            // シリアル通信で送信
            send_serial_data(vectors, 3);
        }
        counter++;

        // 遅延を短縮（500マイクロ秒に設定）
        usleep(500);  // 500マイクロ秒の遅延
    }

    // 終了処理
    close_ps4();
    close_serial();

    return 0;
}

