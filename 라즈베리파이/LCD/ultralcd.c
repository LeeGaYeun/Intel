#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "lcd1602.h"

const int pinEcho = 1;
const int pinTrigger = 0;
int xio;

int main()
{
    printf("초음파 거리 측정 시작\n");
    wiringPiSetupGpio();
    xio = wiringPiI2CSetup(I2C_ADDR);
    lcd_init();

    pinMode(pinEcho, INPUT);
    pinMode(pinTrigger, OUTPUT);
    digitalWrite(pinTrigger, LOW);
    delay(10);

    lcdClear();
    lcdLoc(LINE1);
    typeln("Ultra Start");
    delay(1000);

    while (1)
    {
        digitalWrite(pinTrigger, HIGH);
        delayMicroseconds(15);
        digitalWrite(pinTrigger, LOW);

        while (digitalRead(pinEcho) == LOW);
        long startTime = micros();
        while (digitalRead(pinEcho) == HIGH);
        long endTime = micros() - startTime;
        double distance = endTime / 58.0;

        lcdClear();
        lcdLoc(LINE1);
        char str1[16];
        sprintf(str1, "Distance");
        typeln(str1);
        lcdLoc(LINE2);
        char str2[16];
        sprintf(str2, "%.1fcm", distance);
        typeln(str2);
        delay(750);
    }

    return 0;
}
