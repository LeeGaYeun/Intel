#include <stdio.h>
#include <wiringPi.h>
#include <softTone.h>

const int pinPiezo = 18;
const int melody[] = {262, 294, 330, 349, 392, 440, 494, 523};
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

	printf("Keypad 1 = C\nKeypad 2 = D\nKeypad 3 = E\nKeypad 4 = F\nKeypad 5 = G\nKeypad 6 = A\nKeypad 7 = B\nKeypad 8 = ^C\n");

	while(1){
		keypad();
	}
	return 0;
}

void setup()
{
	wiringPiSetupGpio();
	softToneCreate(pinPiezo);
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
		softToneWrite(pinPiezo, melody[0]);
		delay(200);
		softToneWrite(pinPiezo, 0);
	}
	else if(key == '2'){
		softToneWrite(pinPiezo, melody[1]);
		delay(200);
		softToneWrite(pinPiezo, 0);
	}
	else if(key == '3'){
		softToneWrite(pinPiezo, melody[2]);
		delay(200);
		softToneWrite(pinPiezo, 0);
	}
	else if(key == '4'){
		softToneWrite(pinPiezo, melody[3]);
		delay(200);
		softToneWrite(pinPiezo, 0);
	}
	else if(key == '5'){
		softToneWrite(pinPiezo, melody[4]);
		delay(200);
		softToneWrite(pinPiezo, 0);
	}
	else if(key == '6'){
		softToneWrite(pinPiezo, melody[5]);
		delay(200);
		softToneWrite(pinPiezo, 0);
	}
	else if(key == '7'){
		softToneWrite(pinPiezo, melody[6]);
		delay(200);
		softToneWrite(pinPiezo, 0);
	}
	else if(key == '8'){
		softToneWrite(pinPiezo, melody[7]);
		delay(200);
		softToneWrite(pinPiezo, 0);
	}
}
