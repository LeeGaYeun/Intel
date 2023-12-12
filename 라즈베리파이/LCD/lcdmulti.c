#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "lcd1602.h"

int xio;

int main()
{
    printf("구구단을 외우자~!\n");
    wiringPiSetupGpio();
    xio = wiringPiI2CSetup(I2C_ADDR);
    lcd_init();

    while (1)
    {
        lcdClear();
        lcdLoc(LINE1);
        typeln("Multiplication");
        lcdLoc(LINE2);
        typeln("Table GO");
        delay(1000);

        for (int i = 2; i < 10; i++)
        {
            lcdClear();
            for (int j = 1; j < 10; j++)
            {
                lcdLoc(LINE1);
                char str1[16];
                sprintf(str1, "%d * %d = %d", i, j, i * j);
                typeln(str1);
                delay(1000);
            }
        }

        delay(2000);
    }

    return 0;
}
