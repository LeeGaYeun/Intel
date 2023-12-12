#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "lcd1602.h"

#define LEDNUM 6
const int LEDPIN[LEDNUM] = {17, 27, 13, 19, 26, 20};
const int pinEcho = 1;
const int pinTrigger = 0;
int xio;
int i;
void setup();

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

	setup();
	lcdClear();
	lcdLoc(LINE1);
	typeln("Ultra Start");
	delay(1000);

	while(1){
		digitalWrite(pinTrigger, HIGH);
		delayMicroseconds(15);
		digitalWrite(pinTrigger, LOW);

		while(digitalRead(pinEcho) == LOW);
		long startTime = micros();
		while(digitalRead(pinEcho) == HIGH);
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

		if(distance >= 80){
			for(int i = 0; i < LEDNUM; i++){
				digitalWrite(LEDPIN[i], 0);
			}
		}
		if (distance < 80 && distance >= 70) {
    		digitalWrite(LEDPIN[1], 1);
    		for (i = 1; i < LEDNUM; i++) {
        		digitalWrite(LEDPIN[i], 0);
    		}
		}
		if (distance < 70 && distance > 50) {
    		for (i = 0; i < 2; i++) {
        		digitalWrite(LEDPIN[i], 1);
    		}
    		for (i = 2; i < LEDNUM; i++) {
        		digitalWrite(LEDPIN[i], 0);
    		}
		}

		if (distance < 50 && distance >= 40) {
    		for (i = 0; i < 3; i++) {
        		digitalWrite(LEDPIN[i], 1);
    		}
    		for (i = 3; i < LEDNUM; i++) {
        		digitalWrite(LEDPIN[i], 0);
    		}
		}

		if (distance < 40 && distance >= 30) {
    		for (i = 0; i < 4; i++) {
        		digitalWrite(LEDPIN[i], 1);
    		}
    		for (i = 4; i < LEDNUM; i++) {
        		digitalWrite(LEDPIN[i], 0);
    		}
		}

		if (distance < 30 && distance >= 10) {
    		for (i = 0; i < 5; i++) {
        		digitalWrite(LEDPIN[i], 1);
    		}
    		for (i = 5; i < LEDNUM; i++) {
        		digitalWrite(LEDPIN[i], 0);
    		}
		}

		if (distance < 10 && distance >= 0) {
    		for (i = 0; i < 6; i++) {
        		digitalWrite(LEDPIN[i], 1);
    		}
		}
	}
	return 0;
}

void setup()
{
	for (i = 0; i < LEDNUM; i++)
	{
		pinMode(LEDPIN[i], OUTPUT);
	}
}
