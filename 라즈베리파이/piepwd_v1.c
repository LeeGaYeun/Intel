#include <stdio.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <softTone.h>
#include "lcd1602.h"
#include <stdbool.h>

#define row 4
#define col 4

int CNUM[] = {26, 19, 13, 6};
int RNUM[] = {12, 16, 20, 21};
char CT[row][col] = {
	{'1', '2', '3', 'x'},
	{'4', '5', '6', 'x'},
	{'7', '8', '9', 'x'},
	{'*', '0', '#', 'x'}
};

int melody1[] = {1047, 1175, 1319};

int xio;
const int pinPiezo = 18;
void setup();
void setPassword(char key);
void compare(char key);
char keypad();
char str[4];
char password[4] = "1111"; //초기 비밀번호
char prevKey = '\0';

bool chk = false;
int main()
{
	setup();
	char key;

	printf("PassWord_v1 Test Start\n");
	lcdClear();
	lcdLoc(LINE1);
	typeln("Press");
	lcdLoc(LINE2);
	typeln("PassWord");
	delay(1000);
	lcdClear();
	char newkey;
	while(1){
		key = keypad();
		delay(100);
		printf("key : %c\n", key);
		if(key == '#'){
			setPassword(key);
		}
		else compare(key);

	}
	return 0;
}

void setup()
{
	wiringPiSetupGpio();
	xio = wiringPiI2CSetup(I2C_ADDR);
	lcd_init();
	softToneCreate(pinPiezo);

	for(int i = 0; i < 4; i++){
		pinMode(RNUM[i], OUTPUT);
		pinMode(CNUM[i], INPUT);
		pullUpDnControl(CNUM[i], PUD_UP);
		digitalWrite(RNUM[i], HIGH);
	}
}

char keypad()
{
    char currentKey = '\0';
    char lastKey = '\0';

    for (int i = 0; i < 4; i++){
        digitalWrite(RNUM[i], LOW);
        if (digitalRead(RNUM[i]) == LOW)
        {
            for (int j = 0; j < 4; j++)
            {
                if (digitalRead(CNUM[j]) == LOW)
                {
                    currentKey = CT[i][j];
                    if (currentKey != lastKey)
                    {
                        delay(50);
                        if (digitalRead(CNUM[j]) == LOW)
                        {
                            lastKey = currentKey;
                            return currentKey;
                        }
                    }
                }
            }
            delay(45);
        }

        digitalWrite(RNUM[i], HIGH);
    }
    return '\0';
}

void setPassword(char key)
{
	char key2;
	printf("set\n");
	lcdClear();
	lcdLoc(LINE1);
	typeln("Set Password");
	lcdLoc(LINE2);
	typeln("Press 4digits");
	delay(1000);
	lcdClear();

	key2 = '\0';
	for(int i = 0; i <= 3; i++){
		str[i] = '\0';
		password[i] = '\0';
	}
	while(1){
		key2 = keypad();
		delay(100);
		if(key2 >= '0' && key2 <= '9'){
			strncat(str, &key2, 1);
			lcdLoc(LINE1);
			for(int i = 0; i < strlen(str); i++){
				typeln("*");
			}
			printf("str : %s\n", str);
		}
		else if(str[3] != '\0'){
			lcdClear();
			lcdLoc(LINE1);
			typeln("Set Password");
			lcdLoc(LINE2);
			typeln("Success");
			delay(1000);
			lcdClear();
			break;
		}
	}
	strcpy(password, str);
	printf("pwd:%s\n",password);
}

void compare(char key)
{
	char key3 = keypad();
	printf("compare\n");
	printf("password : %s\n", password);
	lcdClear();

	while(1){
		key3 = keypad();
		delay(100);
		if(key3 == '#'){
			setPassword(key);
		}
		if(key3 >= '0' && key3 <= '9' && chk == false){
			strncat(str, &key3, 1);
			printf("str : %s\n", str);
			lcdLoc(LINE1);
			typeln("Password");
			lcdLoc(LINE2);
			for(int i = 0; i < strlen(str); i++){
				typeln("*");
			}
			softToneWrite(pinPiezo, 988);
			delay(50);
			softToneWrite(pinPiezo, 0);
		}
		else if(str[3] != '\0'){
			printf("\nsave str\n");
			printf("%s\n",str);
			chk = true;
		}
		if(strcmp(password, str) == 0 && chk == true){
			printf("Success\n");
			lcdClear();
			lcdLoc(LINE1);
			typeln("Success");
			delay(1000);
			lcdClear();
			for(int i = 0; i <= 3; i++){ //초기화
       		str[i] = '\0';
    		}
    		for(int j = 0; j < 3; j++){
				softToneWrite(pinPiezo, melody1[j]);
				delay(200);
				softToneWrite(pinPiezo, 0);
    		}
			break;
		}
		else if(chk == true){
			printf("Wrong\n");
			for(int i = 0; i <= 3; i++){ //초기화
       		str[i] = '\0';
    		}
     		chk = false;
     		printf("fail : %s\n",str);
     		lcdClear();
     		lcdLoc(LINE1);
     		typeln("Fail");
     		delay(1000);
     		lcdClear();
     		for(int j; j < 5; j++){
				softToneWrite(pinPiezo, 988);
				delay(100);
				softToneWrite(pinPiezo, 0);
     		}
     		break;
   	}
	}
}
