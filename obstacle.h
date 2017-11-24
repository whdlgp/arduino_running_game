#ifndef OBSTACLE_H_
#define OBSTACLE_H_

#include <Arduino.h>

typedef struct obstacle_t
{
    uint8_t obstacle_window[8][8];
    uint8_t obstacle_map[8][10];
    uint8_t obstacle_speed;
}obstacle_t;

void obstacle_setup();

uint8_t obstacle_process(uint32_t period_ms);

obstacle_t* obstacle_get_window();
void obstacle_set_speed(uint8_t speed);

#endif /* OBSTACLE_H_ */
