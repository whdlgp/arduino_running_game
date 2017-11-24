#include "push_botton.h"

#define PUSH_BOTTON_PIN 12

void push_botton_setup()
{
    pinMode(PUSH_BOTTON_PIN, INPUT);
}

uint8_t push_botton_read()
{
    uint8_t botton_read = 0;
    botton_read = digitalRead(PUSH_BOTTON_PIN);

    return botton_read;
}

uint8_t push_botton_press()
{
    uint8_t retval = 0;
    static uint8_t pre_in = 1;
    uint8_t current_in = digitalRead(PUSH_BOTTON_PIN);
    if(pre_in != current_in)
    {
        if(current_in == 0)
        {
            retval = 1;
        }
    }

    pre_in = current_in;

    return retval;
}

uint8_t push_botton_release()
{
    uint8_t retval = 0;
    static uint8_t pre_in = 0;
    uint8_t current_in = digitalRead(PUSH_BOTTON_PIN);
    if(pre_in != current_in)
    {
        if(current_in == 1)
        {
            retval = 1;
        }
    }

    pre_in = current_in;

    return retval;
}
