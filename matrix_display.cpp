#include "matrix_display.h"

#define ROW_DATA ((row[0]<<7)|(row[1]<<6)|(row[2]<<5)|(row[3]<<4)|(row[4]<<3)|(row[5]<<2)|(row[6]<<1)|(row[7]<<0))
#define COL_DATA ((col[0]<<7)|(col[1]<<6)|(col[2]<<5)|(col[3]<<4)|(col[4]<<3)|(col[5]<<2)|(col[6]<<1)|(col[7]<<0))

enum
{
    SER = 9,
    RCK = 10,
    SRCK = 11
};


static uint8_t row[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
static uint8_t col[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

static uint8_t screen[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

static uint8_t screenRow = 0;
static uint8_t screenCol = 0;

void matrix_display_setup()
{
    pinMode(RCK, OUTPUT);
    pinMode(SRCK, OUTPUT);
    pinMode(SER, OUTPUT);

}

//shift function
static void shiftOut(uint8_t myDataOut)
{
    //internal function setup
    boolean pinState;

    //clear shift register read for sending data
    digitalWrite(RCK, LOW);
    // for each bit in dataOut send out a bit
    for (int i = 0; i <= 7; i++)
    {
        //set clockPin to LOW prior to sending bit
        digitalWrite(SRCK, LOW);
        /*if the value of DataOut and (logical AND) a bitmask
         are true, set pinState to 1 (HIGH)*/
        if (myDataOut & (1 << i))
        {
            pinState = HIGH;
        }
        else
        {
            pinState = LOW;
        }
        //Sets the pin to HIGH or LOW depending on pinState
        digitalWrite(SER, pinState);
        //send bit out on rising edge of clock
        digitalWrite(SRCK, HIGH);
        digitalWrite(SER, LOW);
    }
    //stop shifting
    digitalWrite(SRCK, LOW);
}

static void doubleBuffer()
{
    row[screenRow] = 0;
    col[screenCol] = 1;

    screenCol++;
    if (screenCol >= 8)
    {
        screenCol = 0;
        screenRow++;
        if (screenRow >= 8)
        {
            screenRow = 0;
        }
    }

    if (((screen[screenRow] >> screenCol) & B1) == B1)
    {
        row[screenRow] = 1;
        col[screenCol] = 0;
        digitalWrite(RCK, LOW);
        shiftOut(COL_DATA);
        shiftOut(ROW_DATA);
        digitalWrite(RCK, HIGH);
    }
}

void all_off()
{
    for (int i = 0; i < 8; i++)
        screen[i] = B00000000;
}

void all_on()
{
    for (int i = 0; i < 8; i++)
        screen[i] = B11111111;
}

void on(uint8_t row, uint8_t column)
{
    screen[column - 1] |= (B1 << (row - 1));
}

void off(uint8_t row, uint8_t column)
{
    screen[column - 1] &= ~(B1 << (row - 1));
}

void matrix_display_process(uint32_t period_us)
{
    static uint32_t pre_time = 0;
    uint32_t time = micros();

    if((time - pre_time) > period_us)
    {
        doubleBuffer();

        pre_time = time;
    }
}
