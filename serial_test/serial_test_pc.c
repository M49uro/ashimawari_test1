#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

int main() {
    int serial_fd;
    struct termios tty;

    // シリアルポートを開く
    serial_fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY);
    if (serial_fd == -1) {
        perror("Unable to open /dev/ttyACM0");
        return 1;
    }

    // シリアルポートの設定
    tcgetattr(serial_fd, &tty);
    cfsetispeed(&tty, B9600);
    cfsetospeed(&tty, B9600);
    tty.c_cflag |= (CLOCAL | CREAD);
    tcsetattr(serial_fd, TCSANOW, &tty);

    // データをシリアルポートに書き込む
    char buffer[] = "Hello Arduino\n";
    if (write(serial_fd, buffer, sizeof(buffer)) == -1) {
        perror("Error writing to serial port");
    } else {
        printf("Data written to serial port\n");
    }

    // シリアルポートを閉じる
    close(serial_fd);
    return 0;
}