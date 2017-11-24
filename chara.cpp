#include "chara.h"

static chara_t chara = {{0,}, {0,}, 0, 3};

void chara_setup()
{
    for(uint8_t i = 0; i < 8; i++)
    {
        for(uint8_t j = 0; j < 8; j++)
        {
            chara.chara_window[i][j] = 0;
        }
    }

    for(uint8_t i = 0; i < 8; i++)
    {
        chara.chara_map[i] = 0;
    }

    chara.chara_pos = 0;
    chara.chara_speed = 3;

    chara.chara_window[7 - chara.chara_pos][0] = 1;

    Serial.begin(9600);
}

chara_t* chara_get_window()
{
    return &chara;
}

static void chara_set_pos()
{
    for(uint8_t i = 0; i < 8; i++)
    {
        chara.chara_window[i][0] = 0;
    }
    chara.chara_window[7 - chara.chara_pos][0] = 1;
}

uint8_t chara_process(uint32_t period_ms)
{
    uint8_t retval = 0;

    static uint32_t pre_time = 0;
    uint32_t time = millis();

    if((time - pre_time) > period_ms)
    {
        uint8_t user_in = 0;

        static uint8_t state = 0;
        switch(state)
        {
        case 0:
            user_in = 7 - (analogRead(5) / 147);
            if(user_in > 1)
            {
                chara.chara_pos = user_in;

                chara_set_pos();
                state = 1;
            }
            break;
        case 1:
            static uint8_t count = 0;
            count++;
            if(count > 2)
            {
                count = 0;
                chara.chara_pos--;

                chara_set_pos();
            }

            if(chara.chara_pos == 0)
            {
                state = 0;
            }
            break;
        }

        pre_time = time;
    }

    return retval;
}
