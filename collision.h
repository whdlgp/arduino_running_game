#ifndef COLLISION_H_
#define COLLISION_H_

#include <Arduino.h>

typedef struct collision_t
{
    uint8_t collision_window[8][8];
    uint8_t collision_count;
}collision_t;

collision_t* collision_get_window();
void collision_setup();
uint8_t collision_check();

#endif /* COLLISION_H_ */
