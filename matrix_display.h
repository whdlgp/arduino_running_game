#ifndef MATRIX_DISPLAY_H_
#define MATRIX_DISPLAY_H_

#include <Arduino.h>

void matrix_display_setup();

void all_off();
void all_on();
void on(uint8_t row, uint8_t column);
void off(uint8_t row, uint8_t column);

void matrix_display_process(uint32_t period_us);

#endif /* MATRIX_DISPLAY_H_ */
