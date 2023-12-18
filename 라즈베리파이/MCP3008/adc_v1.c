#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <wiringPiI2C.h>
#include <mcp3004.h>
#include "lcd1602.h"

#define BASE 100
#define SPI_CHAN 0

int xio;

int main()
{
	wiringPiSetup();
	xio = wiringPiI2CSetup(I2C_ADDR);
	lcd_init();
	printf("Raspberry Pi SPI ADC Program\n");
	mcp3004Setup(BASE, SPI_CHAN);

	int str1[16];

	while(1){
		printf("CDS : %d\n", analogRead(BASE + SPI_CHAN));
		lcdClear();
		lcdLoc(LINE1);
		sprintf(str1, "CDS : %d", analogRead(BASE + SPI_CHAN));
		typeln(str1);
		delay(500);
	}

	return 0;
}
