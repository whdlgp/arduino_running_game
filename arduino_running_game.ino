#include "matrix_display.h"
#include "obstacle.h"
#include "chara.h"
#include "collision.h"

#include <Arduino.h>

void draw_game_play()
{
    obstacle_t* obs = obstacle_get_window();
    chara_t* chara = chara_get_window();
    collision_t* cls = collision_get_window();

    all_off();

    for(uint8_t col = 0; col < 8; col++)
    {
        for(uint8_t row = 0; row < 8; row++)
        {
            if(obs->obstacle_window[row][col] == 1)
            {
                on(row + 1, 8 - col);
            }
        }
    }

    for(uint8_t col = 0; col < 8; col++)
    {
        for(uint8_t row = 0; row < 8; row++)
        {
            if(chara->chara_window[row][col] == 1)
            {
                on(row + 1, 8 - col);
            }
        }
    }

    for(uint8_t col = 0; col < 8; col++)
    {
        for(uint8_t row = 0; row < 8; row++)
        {
            if(cls->collision_window[row][col] == 1)
            {
                on(row + 1, 8 - col);
            }
        }
    }
}

void setup()
{
    obstacle_setup();
    obstacle_set_speed(8);

    chara_setup();

    collision_setup();

    matrix_display_setup();
}

void loop()
{
    obstacle_process(100);

    chara_process(30);

    draw_game_play();

    if(collision_check() == 1)
    {
        obstacle_setup();
        obstacle_set_speed(8);
        chara_setup();
    }

    matrix_display_process(100);
}
