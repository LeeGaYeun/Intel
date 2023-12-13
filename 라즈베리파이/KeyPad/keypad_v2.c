#include <stdio.h>
#include <wiringPi.h>

int CNUM[] = {26, 19, 13, 6};
int RNUM[] = {12, 16, 20, 21};
int i, j;

void setup();

void setup()
{
	wiringPiSetupGpio();
	for (i = 0; i < 4; i++)
	{
		pinMode(RNUM[i], OUTPUT);
		pinMode(CNUM[i], INPUT);
		pullUpDnControl(CNUM[i], PUD_UP);
	}
}

int main()
{
	printf("KeyPad Test Start\n");
	setup();
	while(1){
		digitalWrite(RNUM[0], LOW);
		for(i = 1; i < 3; i++){
         digitalWrite(RNUM[i], HIGH);
      }

		if(digitalRead(RNUM[0]) == LOW){
			for(j = 0; j < 3; j++){
				if(digitalRead(CNUM[j]) == LOW){
					printf("%d\n", j + 1);
				}
			}
			if(digitalRead(CNUM[3]) == LOW){
				printf("+\n");
			}
			delay(50);
		}

		digitalWrite(RNUM[0], HIGH);
		digitalWrite(RNUM[1], LOW);

		if(digitalRead(RNUM[1]) == LOW){
			for(j = 0; j < 3; j++){
				if(digitalRead(CNUM[j]) == LOW){
					printf("%d\n", j + 4);
				}
			}
			if(digitalRead(CNUM[3]) == LOW){
				printf("-\n");
			}
			delay(50);
		}

		for(i = 0; i < 2; i++)
			digitalWrite(RNUM[i], HIGH);
		digitalWrite(RNUM[2], LOW);

		if(digitalRead(RNUM[2]) == LOW){
			for(j = 0; j < 3; j++){
				if(digitalRead(CNUM[j]) == LOW){
					printf("%d\n", j + 7);
				}
			}
			if(digitalRead(CNUM[3]) == LOW){
				printf("*\n");
			}
			delay(50);
		}

		digitalWrite(RNUM[2], HIGH);
		digitalWrite(RNUM[3], LOW);

		if(digitalRead(RNUM[3]) == LOW){
			if(digitalRead(CNUM[0]) == LOW){
				printf("=\n");
			}
			else if(digitalRead(CNUM[1]) == LOW){
				printf("0\n");
			}
			else if(digitalRead(CNUM[2]) == LOW){
				printf("#\n");
			}
			else if(digitalRead(CNUM[3]) == LOW){
				printf("/\n");
			}
			delay(50);
		}
		digitalWrite(RNUM[3], HIGH);

	}
	return 0;
}
