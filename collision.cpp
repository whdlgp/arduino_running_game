#include "collision.h"

#include "obstacle.h"
#include "chara.h"

static collision_t cls = {{0,}, 0};

collision_t* collision_get_window()
{
    return &cls;
}

void collision_setup()
{
    for(uint8_t i = 0; i < 8; i++)
    {
        for(uint8_t j = 0; j < 8; j++)
        {
            cls.collision_window[i][j] = 0;
        }
    }

    cls.collision_count = 0;
}

uint8_t collision_check()
{
    obstacle_t* obs = obstacle_get_window();
    chara_t* chara = chara_get_window();

    for(uint8_t i = 0; i < 8; i++)
    {
        if((obs->obstacle_window[i][0] == 1)
                && (chara->chara_window[i][0] == 1))
        {
            cls.collision_window[0][7-cls.collision_count] = 1;
            cls.collision_count++;

            if(cls.collision_count == 8)
            {
                collision_setup();
            }
            return 1;
        }
    }

    return 0;
}
