#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

const int pinLed = 23;
int CNUM[] = {26, 19, 13, 6};
int RNUM[] = {12, 16, 20, 21};

void setup();
void keypad();
void MoodLed(char key);

char CT[4][4] = {
	{'1', '2', '3', 'x'},
	{'4', '5', '6', 'x'},
	{'7', '8', '9', 'x'},
	{'x', '0', 'x', 'x'}
};

int main()
{
	setup();
	char key;

	printf("Keypad 1 = LED ON\nKeypad 2 = OFF\nKeypad 3 = MODE1\nKeypad 4 = Mode2\nKeypad 5 = Mode3\nKeypad 6 = Mode4\nKeypad 7 = Brighter\nKeypad 8 = Dark\n");

	while(1){
		keypad();
	}
	return 0;
}

void setup()
{
	wiringPiSetupGpio();
	softPwmCreate(pinLed, 0, 200);
	for(int i = 0; i < 4; i++){
		pinMode(RNUM[i], OUTPUT);
		pinMode(CNUM[i], INPUT);
		pullUpDnControl(CNUM[i], PUD_UP);
		digitalWrite(RNUM[i], HIGH);
	}
}

void keypad()
{
	for(int i = 0; i < 4; i++){
        //현재 행이 눌렸을 때
		digitalWrite(RNUM[i], LOW);
		if(digitalRead(RNUM[i]) == LOW){
            //각 열의 입력을 확인하고 해당하는 키에 대한 계산기 함수 호출
			for(int j = 0; j < 4; j++){
				if(digitalRead(CNUM[j]) == LOW){
						MoodLed(CT[i][j]);
				}
			}
			delay(45); //디바운싱을 위한 딜레이
		}

		digitalWrite(RNUM[i], HIGH); //다시 모든 행을 HIGH로 설정
	}
}

void MoodLed(char key)
{
	if(key == '1'){
			softPwmWrite(pinLed, 200);
		}
		else if(key == '2'){
			softPwmWrite(pinLed, 0);
		}
		else if(key == '3'){
			softPwmWrite(pinLed, 50);
		}
		else if(key == '4'){
			softPwmWrite(pinLed, 100);
		}
		else if(key == '5'){
			softPwmWrite(pinLed, 150);
		}
		else if(key == '6'){
			softPwmWrite(pinLed, 200);
		}
		else if(key == '7'){
			for(int i = 0; i < 200; i++){
				softPwmWrite(pinLed, i);
				delay(20);
			}
		}
		else if(key == '8'){
			for(int i = 200; i > 0; i--){
				softPwmWrite(pinLed, i);
				delay(20);
			}
		}
}
