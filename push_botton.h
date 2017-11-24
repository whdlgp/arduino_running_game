#ifndef PUSH_BOTTON_H_
#define PUSH_BOTTON_H_

#include <Arduino.h>

void push_botton_setup();

uint8_t push_botton_read();
uint8_t push_botton_press();
uint8_t push_botton_release();

#endif /* PUSH_BOTTON_H_ */
