#include <stdio.h>
#include <wiringPi.h>

#define LEDE	0 	//1
#define LEDD	5 	//2
#define LEDDP	6 	//3
#define LEDC	13 //4
#define LEDG	19 //5
#define LEDF	15 //7
#define LEDA	14 //10
#define LEDB	18 //11
#define SFT1	25	//12
#define SFT2	8  //9
#define SFT3	7	//8
#define SFT4	1	//6

int pattern[][8] = {
    {1, 1, 1, 1, 1, 1, 0, 0}, // 0
    {0, 1, 1, 0, 0, 0, 0, 0}, // 1
    {1, 1, 0, 1, 1, 0, 1, 0}, // 2
    {1, 1, 1, 1, 0, 0, 1, 0}, // 3
    {0, 1, 1, 0, 0, 1, 1, 0}, // 4
    {1, 0, 1, 1, 0, 1, 1, 0}, // 5
    {1, 0, 1, 1, 1, 1, 1, 0}, // 6
    {1, 1, 1, 0, 0, 1, 0, 0}, // 7
    {1, 1, 1, 1, 1, 1, 1, 0}, // 8
    {1, 1, 1, 0, 0, 1, 1, 0}, // 9
    {1, 1, 1, 0, 1, 1, 1, 0}, // A
    {1, 1, 1, 1, 1, 1, 1, 1}, // B
    {1, 0, 0, 1, 1, 1, 0, 0}, // C
    {1, 1, 1, 1, 1, 1, 0, 1}, // D
    {1, 0, 0, 1, 1, 1, 1, 0}, // E
    {1, 0, 0, 0, 1, 1, 1, 0}  // F
};

int main()
{
   wiringPiSetupGpio();
	static int k = 0;
	int ledPin[] = {LEDA, LEDB, LEDC, LEDD, LEDE, LEDF, LEDG, LEDDP};
	int sft[] = {SFT1, SFT2, SFT3, SFT4};

	for(int i = 0; i < 8; i++){
		pinMode(ledPin[i], OUTPUT);
	}
	for(int j = 0; j < 4; j++){
		pinMode(sft[j], OUTPUT);
	}

	while(1){
		for(int j = 0; j < 4; j++){
			digitalWrite(sft[j], 1);
		}
		digitalWrite(sft[0], 0);
		for(int i = 0; i < 8; i++){
			digitalWrite(ledPin[i], pattern[0][i]);
		}
		delay(5);
		for(int j = 0; j < 4; j++){
			digitalWrite(sft[j], 1);
		}

		digitalWrite(sft[1], 0);
		for(int i = 0; i < 8; i++){
			digitalWrite(ledPin[i], pattern[1][i]);
		}
		delay(5);
		for(int j = 0; j < 4; j++){
			digitalWrite(sft[j], 1);
		}

		digitalWrite(sft[2], 0);
		for(int i =0; i < 8; i++){
			digitalWrite(ledPin[i], pattern[2][i]);
		}
		delay(5);
		for(int j = 0; j < 4; j++){
			digitalWrite(sft[j], 1);
		}

		digitalWrite(sft[3], 0);
		for(int i = 0; i < 8; i++){
			digitalWrite(ledPin[i], pattern[3][i]);
		}
		delay(5);
		for(int j = 0; j < 4; j++){
			digitalWrite(sft[j], 1);
		}
	}
	return 0;
}
