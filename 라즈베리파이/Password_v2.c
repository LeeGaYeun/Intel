#include <stdio.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
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

int xio;

void setup(); //GPIO 및 LCD 초기화
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
      key = keypad(); //키패드에서 키 입력 받기
      delay(100);
      printf("key : %c\n", key);
      if(key == '#'){
         //비밀번호 설정 함수 #누를 때 실행
         setPassword(key);
      }
      else compare(key); //입력된 비밀번호를 설정된 비밀번호와 비교

   }
   return 0;
}

void setup()
{
   wiringPiSetupGpio();
   xio = wiringPiI2CSetup(I2C_ADDR);
   lcd_init();

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
   for(int i = 0; i <= 3; i++){ //초기화
      str[i] = '\0';
      password[i] = '\0';
   }
   while(1){
      key2 = keypad();
      delay(100);
      if(key2 >= '0' && key2 <= '9'){
         strncat(str, &key2, 1); //현재 문자열 str에 key2라는 문자를 하나씩 추가
         lcdLoc(LINE1);
         for(int i = 0; i < strlen(str);i++){
            typeln("*"); //LCD화면에 숫자 입력시 * 나옴
         }
         printf("str : %s\n", str);
      }
      else if(str[3] != '\0'){ //(str 3번방에 널이 아니면) 숫자 4자리 입력시 실행
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
   strcpy(password, str); //str에 저장된 숫자 4자리를 pwd에 저장
   printf("pwd:%s\n",password);
}

void compare(char key) //pwd와 키패드에 입력한 숫자 4자리 비교
{
   char key3 = keypad();
   printf("compare\n");
   printf("password : %s\n", password);
   lcdClear();

   while(1){
      key3 = keypad();
      delay(100);
      if(key3 == '#'){ //#을 누르면 실행
//비밀번호를 입력하는 과정에서 사용자가 #을 누르면 비밀번호를 설정하는 동작을 수행하기 위해서 
         setPassword(key);  
      }
      //비밀번호 입력
      if(key3 >= '0' && key3 <= '9' && chk == false){
         strncat(str, &key3, 1);
         printf("str : %s\n", str);
         lcdLoc(LINE1);
         typeln("Password");
         lcdLoc(LINE2);
         for(int i = 0; i < strlen(str); i++){
            typeln("*");
         }
      }
      else if(str[3] != '\0'){ //숫자 4자리 입력시 chk = true
         printf("\n save str\n");
         printf("%s\n",str);
         chk = true;
      }
//password와 str 비교하여 같고 숫자 4자리 입력시 비밀번호 해제 성공
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
         break;
      }
//비밀번호 4자리 입력하고 입력된 비밀번호가 설정된 비밀번호와 일치하지 않을 경우
      else if(chk == true){ 
         printf("Wrong\n");
         for(int i = 0; i <= 3; i++){ //초기화
             str[i] = '\0';
          }
           chk = false; //초기화
           printf("fail : %s\n",str);
           lcdClear();
           lcdLoc(LINE1);
           typeln("Fail");
           delay(1000);
           lcdClear();
           break;
      }
   }
}
