#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "lcd1602.h"

int xio;

int main()
{
    printf("Raspberry Pi LCD test program\n");

    wiringPiSetupGpio();
    xio = wiringPiI2CSetup(I2C_ADDR);
    lcd_init();

    char str1[] = "Hello!";
    char str2[] = "LEE GA YEUN!!";

    while (1)
    {
        lcdClear();
        lcdLoc(LINE1);
        typeln(str1);
        lcdLoc(LINE2);
        typeln(str2);
        delay(2000);
    }

    return 0;
}
