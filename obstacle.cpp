#include "obstacle.h"

static obstacle_t obs = {{0,}, {0,}, 2};

static uint8_t obstacle_count = 0;
static uint8_t obstacle_period_count = 0;

obstacle_t* obstacle_get_window()
{
    return &obs;
}

void obstacle_set_speed(uint8_t speed)
{
    obs.obstacle_speed = speed;
}

void obstacle_generate()
{
    for(uint8_t i = 0; i < 10; i++)
    {
        uint8_t random_val = random(1,5);
        uint8_t temp[8] = {0,};

        for(uint8_t j = 7; j > (7 - random_val) ; j--)
            temp[j] = 1;

        for(uint8_t j = 0; j < 8; j++)
        {
            obs.obstacle_map[j][i] = temp[j];
        }
    }
}

void obstacle_setup()
{
    randomSeed(analogRead(0));

    for(uint8_t i = 0; i < 8; i++)
    {
        for(uint8_t j = 0; j < 8; j++)
        {
            obs.obstacle_window[i][j] = 0;
        }
    }

    for(uint8_t i = 0; i < 8; i++)
    {
        for(uint8_t j = 0; j < 10; j++)
        {
            obs.obstacle_window[i][j] = 0;
        }
    }

    obs.obstacle_speed = 2;

    obstacle_count = 0;
    obstacle_period_count = 0;

    obstacle_generate();
}

uint8_t obstacle_process(uint32_t period_ms)
{
    uint8_t retval = 0;

    static uint32_t pre_time = 0;
    uint32_t time = millis();

    if((time - pre_time) > period_ms)
    {
        obstacle_period_count++;

        uint8_t set_obstacle = 0;

        if(obstacle_period_count > obs.obstacle_speed)
        {
            obstacle_period_count = 0;

            set_obstacle = 1;
        }

        for(uint8_t col = 0; col < 7; col++)
        {
            for(uint8_t row = 0; row < 8; row++)
            {
                obs.obstacle_window[row][col] = obs.obstacle_window[row][col + 1];
            }
        }
        if(set_obstacle)
        {
            for(uint8_t row = 0; row < 8; row++)
            {
                obs.obstacle_window[row][7] = obs.obstacle_map[row][obstacle_count];
            }
            obstacle_count++;
        }
        else
        {
            for(uint8_t row = 0; row < 8; row++)
            {
                obs.obstacle_window[row][7] = 0;
            }
        }

        if(obstacle_count > 9)
        {
            obstacle_count = 0;
            retval = 1;
        }

        pre_time = time;
    }

    return retval;
}
