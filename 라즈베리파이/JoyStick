#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <mcp3004.h>

#define BASE 100
#define SPI_CHAN 0
#define SW 4

int main()
{
	wiringPiSetupGpio();
	pinMode(SW, INPUT);
	pullUpDnControl(SW, PUD_UP);
	printf("Raseberry Pi SPI ADC Program\n");
	mcp3004Setup(BASE, SPI_CHAN);

	while(1){
		int sw = digitalRead(SW);
		for(int i = 0; i < 2; i++){
			printf("channel %d value : %4d\t", i, analogRead(BASE + i));
			delay(200);
		}
		printf("\n");
		printf("sw : %d\n", sw);
	}
	return 0;
}
