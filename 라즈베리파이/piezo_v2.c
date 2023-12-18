#include <stdio.h>
#include <wiringPi.h>
#include <softTone.h>

const int pinPiezo = 18;
const int melody[] = {131, 147, 165, 175, 196, 220, 247, 262};

int main()
{
	wiringPiSetupGpio();
	softToneCreate(pinPiezo);

	while(1){
		for(int i = 0; i < 8; i++){
			softToneWrite(pinPiezo, melody[i]);
			delay(100);
		}
		softToneWrite(pinPiezo, 0);
		delay(1000);
	}

	return 0;
}
