#ifndef CHARA_H_
#define CHARA_H_

#include <Arduino.h>

typedef struct chara_t
{
    uint8_t chara_window[8][8];
    uint8_t chara_map[8];
    uint8_t chara_pos;
    uint8_t chara_speed;
}chara_t;

void chara_setup();
chara_t* chara_get_window();
uint8_t chara_process(uint32_t period_ms);

#endif /* CHARA_H_ */
