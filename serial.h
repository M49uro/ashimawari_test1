#ifndef SERIAL_H
#define SERIAL_H

void init_serial();
void send_serial_data(int* data, int length);
void close_serial();

#endif
