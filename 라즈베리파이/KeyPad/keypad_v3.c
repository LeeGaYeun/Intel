#include <stdio.h>
#include <wiringPi.h>

int i, j;
#define row 4
#define col 4
int CNUM[] = {26, 19, 13, 6}; //INPUT
int RNUM[] = {12, 16, 20, 21}; //OUTPUT

void setup();

void setup()
{
	wiringPiSetupGpio();
	for (i = 0; i < 4; i++)
	{
		pinMode(RNUM[i], OUTPUT);
		pinMode(CNUM[i], INPUT);
		pullUpDnControl(CNUM[i], PUD_UP);
		digitalWrite(RNUM[i], HIGH);
	}
}

int main()
{
	printf("KeyPad Test Start\n");
	setup();
   char CT[row][col] = {
     {'1', '2', '3', '+'},
     {'4', '5', '6', '-'},
     {'7', '8', '9', '*'},
     {'=', '0', '#', '/'}
   };
	while(1){
		for(i = 0; i < 4; i++){
			digitalWrite(RNUM[i], LOW);

			if(digitalRead(RNUM[i]) == LOW){
				for(j = 0; j < 4; j++){
					if(digitalRead(CNUM[j]) == LOW){
							printf("%c\n", CT[i][j]);
					}
				}
				delay(45);
			}

			digitalWrite(RNUM[i], HIGH);
		}
	}
	return 0;
}
