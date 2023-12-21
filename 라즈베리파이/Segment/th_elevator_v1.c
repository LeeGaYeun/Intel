#include <stdio.h>
#include <string.h>
#include <wiringPi.h>
#include <pthread.h>

#define LEDE	0 	//1
#define LEDD	5 	//2
#define LEDDP	6 	//3
#define LEDC	13 //4
#define LEDG	19 //5
#define LEDF	15 //7
#define LEDA	14 //10
#define LEDB	18 //11
#define SFT1	12	//12
#define SFT2	16 //9
#define SFT3	20	//8
#define SFT4	21	//6

int CNUM[] = {17, 4, 3, 2};
int RNUM[] = {25, 7, 1, 24};
char CT[4][4] = {
	{'1', '2', '3', 's'},
	{'4', '5', '6', 'x'},
	{'7', '8', '9', 'x'},
	{'*', '0', 'x', 'x'}
};
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
};

char str[5];
static int nowf = 1;

void setup();
char keypad();
void moveloop(int tnum);
void currentloop(int tnum);
void floornum(char key);

int main()
{
	setup();
	char key;
	int ledPin[] = {LEDA, LEDB, LEDC, LEDD, LEDE, LEDF, LEDG, LEDDP};
   for (int i = 0; i < 8; i++) {
        digitalWrite(ledPin[i], 0);
   }
	printf("Elevator Start\n");

	while(1){
		currentloop(nowf);
   	char key = keypad();
   	floornum(key);
   }
	return 0;
}

void setup()
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
      pinMode(RNUM[j], OUTPUT);
      pinMode(CNUM[j], INPUT);
      pullUpDnControl(CNUM[j], PUD_UP);
      digitalWrite(RNUM[j], 1);
   }

}

char keypad()
{
	for(int i = 0; i < 4; i++){
        //현재 행이 눌렸을 때
		digitalWrite(RNUM[i], LOW);
		if(digitalRead(RNUM[i]) == LOW){
			for(int j = 0; j < 4; j++){
				if(digitalRead(CNUM[j]) == LOW){
						delay(200);
						return CT[i][j];
				}
			}
		}
		digitalWrite(RNUM[i], HIGH); //다시 모든 행을 HIGH로 설정
	}
	return '\0';
}

void moveloop(int tnum)
{
	int digit[3];
	int k = 0;
	digit[0] = tnum % 10;
	digit[1] = (tnum / 10) % 10;
	digit[2] = (tnum / 100) % 10;
	digit[3] = (tnum / 1000) % 10;
	int ledPin[] = {LEDA, LEDB, LEDC, LEDD, LEDE, LEDF, LEDG, LEDDP};
	int sft[] = {SFT1, SFT2, SFT3, SFT4};

	for(int i = 0; i < 4; i++){
   	digitalWrite(sft[i], 1);
   }

	for(k = 0; k < 10; k++){
   //일의 자리
   	digitalWrite(sft[3], 0);
   	for(int j = 0; j < 8; j++){
      	digitalWrite(ledPin[j], pattern[digit[0]][j]);
   	}
   	delay(5);
   	digitalWrite(sft[3], 1);

	//십의 자리
   	digitalWrite(sft[2], 0);
   	for(int j = 0; j < 8; j++){
			digitalWrite(ledPin[j], pattern[digit[1]][j]);
   	}
   	delay(5);
   	digitalWrite(sft[2], 1);

	//백의 자리
		digitalWrite(sft[1], 0);
   	for(int j = 0; j < 8; j++){
			digitalWrite(ledPin[j], pattern[digit[2]][j]);
   	}
   	delay(5);
   	digitalWrite(sft[1], 1);

   //천의 자리
      digitalWrite(sft[0], 0);
   	for(int j = 0; j < 8; j++){
   		digitalWrite(ledPin[j], pattern[digit[3]][j]);
   	}
   	delay(5);
   	digitalWrite(sft[0], 1);
   }
}

void floornum(char key)
{
	static int j = 0;
	static int l = 0;
	if(key >= '0' && key <= '9'){
			strncat(str, &key, 1);
			printf("str : %s\n", str);
	}
	else if(key == '*'){
		str[0] = '\0';
	}
	else if(key == 's'){
		int tnum = atoi(str);

		if(tnum > nowf && tnum < 10000){
			printf("Going up to %d\n", tnum);
			int upf = tnum - nowf;
			for(int i = 1; i <= upf; i++){
            printf("%d\n", nowf + i);
            moveloop(nowf + i);
         }
         printf("%d 층에 도착하였습니다.\n", tnum);
			nowf = tnum;
			str[0] = '\0';
			currentloop(tnum);
		}
		else if(tnum < nowf && tnum < 10000){
			printf("Going down to %d\n", tnum);
			int downf = nowf - tnum;
			for(int i = 1; i <= downf; i++){
				printf("%d\n", nowf - i);
				moveloop(nowf - i);
			}
			printf("%d 층에 도착하였습니다.\n", tnum);
			nowf = tnum;
			str[0] = '\0';
		}
		else{
			printf("층을 9999층 이내로 누르세요.\n");
			str[0] = '\0';
		}
	}
}

void currentloop(int tnum)
{
	int digit[3];
	int k = 0;
	digit[0] = tnum % 10;
	digit[1] = (tnum / 10) % 10;
	digit[2] = (tnum / 100) % 10;
	digit[3] = (tnum / 1000) % 10;
	int ledPin[] = {LEDA, LEDB, LEDC, LEDD, LEDE, LEDF, LEDG, LEDDP};
	int sft[] = {SFT1, SFT2, SFT3, SFT4};

	for(int i = 0; i < 4; i++){
   	digitalWrite(sft[i], 1);
   }

   //일의 자리
   	digitalWrite(sft[3], 0);
   	for(int j = 0; j < 8; j++){
      	digitalWrite(ledPin[j], pattern[digit[0]][j]);
   	}
   	delay(5);
   	digitalWrite(sft[3], 1);

	//십의 자리
   	digitalWrite(sft[2], 0);
   	for(int j = 0; j < 8; j++){
			digitalWrite(ledPin[j], pattern[digit[1]][j]);
   	}
   	delay(5);
   	digitalWrite(sft[2], 1);

	//백의 자리
		digitalWrite(sft[1], 0);
   	for(int j = 0; j < 8; j++){
			digitalWrite(ledPin[j], pattern[digit[2]][j]);
   	}
   	delay(5);
   	digitalWrite(sft[1], 1);

   //천의 자리
      digitalWrite(sft[0], 0);
   	for(int j = 0; j < 8; j++){
   		digitalWrite(ledPin[j], pattern[digit[3]][j]);
   	}
   	delay(5);
   	digitalWrite(sft[0], 1);
}
