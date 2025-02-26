#ifndef PS4_H
#define PS4_H

typedef struct {
    int x;
    int y;
} PS4Data;

void init_ps4();
PS4Data get_ps4_data();
void close_ps4();

extern int is_wired;  // 追加

#endif
