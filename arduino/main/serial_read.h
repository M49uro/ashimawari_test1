#ifndef SERIAL_READ_H
#define SERIAL_READ_H

#include <Arduino.h>

void setup_serial();
void read_serial();

extern int vector0;
extern int vector1;
extern int vector2;
extern boolean stringComplete;

#endif // SERIAL_READ_H
