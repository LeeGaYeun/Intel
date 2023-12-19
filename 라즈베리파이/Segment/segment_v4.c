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

//void ssft();
//void loop();

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
		digitalWrite(ledPin[i], 1);
		pinMode(sft[i], OUTPUT);
	}

	while(1){
		if(k == 0){
			digitalWrite(sft[k], 0);
			for(k = 1; k < 4; k++){
				digitalWrite(sft[k], 1);
			}
			for(int i = 0; i < 16; i++){
				for(int j = 0; j < 8; j++){
					digitalWrite(ledPin[j], pattern[i][j]);
				}
			delay(600);
			}
			k = 1;
		}
		else if(k == 1){
			digitalWrite(sft[k], 0);
			for(k = 2; k < 4; k++){
				digitalWrite(sft[k], 1);
			}
			digitalWrite(sft[0], 1);
			for(int i = 0; i < 16; i++){
				for(int j = 0; j < 8; j++){
					digitalWrite(ledPin[j], pattern[i][j]);
				}
			delay(600);
			}
			k = 2;
		}
		else if(k == 2){
			digitalWrite(sft[k], 0);
			for(k = 0; k < 2; k++){
            digitalWrite(sft[k], 1);
         }
         digitalWrite(sft[3], 1);
         for(int i = 0; i < 16; i++){
            for(int j = 0; j < 8; j++){
               digitalWrite(ledPin[j], pattern[i][j]);
            }
         delay(600);
         }
         k = 3;
		}
		else if(k == 3){
         digitalWrite(sft[k], 0);
         for(k = 0; k < 3; k++){
            digitalWrite(sft[k], 1);
         }
         for(int i = 0; i < 16; i++){
            for(int j = 0; j < 8; j++){
               digitalWrite(ledPin[j], pattern[i][j]);
            }
         delay(600);
         }
         k = 0;
      }

   }
	return 0;
}
