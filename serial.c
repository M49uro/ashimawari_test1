#include "serial.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

int serial_fd;

void init_serial() {
    struct termios tty;
    serial_fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY);

    if (serial_fd == -1) {
        perror("Unable to open /dev/ttyACM0");
        exit(1);
    }

    tcgetattr(serial_fd, &tty);
    cfsetispeed(&tty, B9600);  // ボーレートを9600に設定
    cfsetospeed(&tty, B9600);  // ボーレートを9600に設定
    tty.c_cflag |= (CLOCAL | CREAD);
    tcsetattr(serial_fd, TCSANOW, &tty);
}

void send_serial_data(int* vectors, int size) {
    char buffer[64];
    int len = snprintf(buffer, sizeof(buffer), "<%d,%d,%d>\n", vectors[0], vectors[1], vectors[2]);
    if (write(serial_fd, buffer, len) == -1) {
        perror("Error writing to serial port");
    }
    tcflush(serial_fd, TCOFLUSH);  // 送信バッファをクリア
    usleep(1000);  // 1ミリ秒の遅延
}

void close_serial() {
    close(serial_fd);
}
