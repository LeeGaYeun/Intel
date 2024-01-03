#include "elevator.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <stdio.h>
#include <string.h>
#include <wiringPi.h>
#include <pthread.h>
#include <QDebug>

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

int CNUM2[] = {27, 17, 26, 1};
int RNUM2[] = {22, 23, 24, 25};
char CT2[4][4] = {
    {'1', '2', '3', 's'},
    {'4', '5', '6', 'x'},
    {'7', '8', '9', 'x'},
    {'*', '0', 'x', 'x'}
};
int pattern2[][8] = {
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

char str2[5];
static int nowf2 = 1;

void setup2();
char keypad2();
void currentloop2(int tnum);

ElevatorThread::ElevatorThread(QObject *parent) : QThread(parent), elevatorcheck(false)
{
    setup2();
    int ledPin[] = {LEDA, LEDB, LEDC, LEDD, LEDE, LEDF, LEDG, LEDDP};
    for (int i = 0; i < 8; i++) {
        digitalWrite(ledPin[i], 0);
    }

}

ElevatorThread::~ElevatorThread()
{
    stopElevator();
    wait();
}

void ElevatorThread::run()
{
    char key;
    while (elevatorcheck) {
        currentloop2(nowf2);
        char key = keypad2();
        floornum2(key);
        // 이 부분에서 LCD에 표시
        emit floorChanged(nowf2); // 시그널 발생
        if(!elevatorcheck)    break;
    }
}

void ElevatorThread::startElevator()
{
    if (!isRunning()) {
        nowf2 = 1;
        elevatorcheck = true;
        start();
    } else {
        qDebug() << "Elevator is already running.";
    }
}

void ElevatorThread::stopElevator()
{
    if (isRunning()) {
        nowf2 = 0;

        elevatorcheck = false;
        emit floorChanged(nowf2);

        wait(); // 스레드가 종료될 때까지 대기
    } else {
        qDebug() << "Elevator is not running.";
    }
}

void setup2()
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
      pinMode(RNUM2[j], OUTPUT);
      pinMode(CNUM2[j], INPUT);
      pullUpDnControl(CNUM2[j], PUD_UP);
      digitalWrite(RNUM2[j], 1);
   }

}

char keypad2()
{
    for(int i = 0; i < 4; i++){
        //현재 행이 눌렸을 때
        digitalWrite(RNUM2[i], LOW);
        if(digitalRead(RNUM2[i]) == LOW){
            for(int j = 0; j < 4; j++){
                if(digitalRead(CNUM2[j]) == LOW){
                        delay(200);
                        return CT2[i][j];
                }
            }
        }
        digitalWrite(RNUM2[i], HIGH); //다시 모든 행을 HIGH로 설정
    }
    return '\0';
}

void ElevatorThread::moveloop2(int tnum)
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
            digitalWrite(ledPin[j], pattern2[digit[0]][j]);
        }
        delay(5);
        digitalWrite(sft[3], 1);

        //십의 자리
        digitalWrite(sft[2], 0);
        for(int j = 0; j < 8; j++){
            digitalWrite(ledPin[j], pattern2[digit[1]][j]);
        }
        delay(5);
        digitalWrite(sft[2], 1);

        //백의 자리
        digitalWrite(sft[1], 0);
        for(int j = 0; j < 8; j++){
            digitalWrite(ledPin[j], pattern2[digit[2]][j]);
        }
        delay(5);
        digitalWrite(sft[1], 1);

        //천의 자리
        digitalWrite(sft[0], 0);
        for(int j = 0; j < 8; j++){
            digitalWrite(ledPin[j], pattern2[digit[3]][j]);
        }
        delay(5);
        digitalWrite(sft[0], 1);

        emit updateLCD(tnum);

        QCoreApplication::processEvents();  // 이벤트 루프 처리
   }
}

void currentloop2(int tnum)
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
        digitalWrite(ledPin[j], pattern2[digit[0]][j]);
    }
    delay(5);
    digitalWrite(sft[3], 1);

    //십의 자리
    digitalWrite(sft[2], 0);
    for(int j = 0; j < 8; j++){
            digitalWrite(ledPin[j], pattern2[digit[1]][j]);
    }
    delay(5);
    digitalWrite(sft[2], 1);

    //백의 자리
        digitalWrite(sft[1], 0);
    for(int j = 0; j < 8; j++){
            digitalWrite(ledPin[j], pattern2[digit[2]][j]);
    }
    delay(5);
    digitalWrite(sft[1], 1);

   //천의 자리
      digitalWrite(sft[0], 0);
    for(int j = 0; j < 8; j++){
        digitalWrite(ledPin[j], pattern2[digit[3]][j]);
    }
    delay(5);
    digitalWrite(sft[0], 1);
}

void ElevatorThread:: floornum2(char key)
{
    static int j = 0;
    static int l = 0;
    if(key >= '0' && key <= '9'){
            strncat(str2, &key, 1);
            qDebug() << "str : " << str2;
    }
    else if(key == '*'){
        str2[0] = '\0';
    }
    else if(key == 's'){
        int tnum = atoi(str2);

        if(tnum > nowf2 && tnum < 10000){
            qDebug() << "Going down to" << tnum;
            int upf = tnum - nowf2;
            for(int i = 1; i <= upf; i++){
                qDebug() << "Moving Up : " << nowf2 + i;
                moveloop2(nowf2 + i);
            }
            qDebug() << tnum <<"층에 도착하였습니다.";
            nowf2 = tnum;
            str2[0] = '\0';
            currentloop2(tnum);
        }
        else if(tnum < nowf2 && tnum < 10000){
            printf("Going down to %d\n", tnum);
            int downf = nowf2 - tnum;
            for(int i = 1; i <= downf; i++){
                qDebug() << "Moving Down : " << nowf2 - i;
                moveloop2(nowf2 - i);
            }
            qDebug() << tnum <<"층에 도착하였습니다.";
            nowf2 = tnum;
            str2[0] = '\0';
        }
        else{
            qDebug() << "층을 9999층 이내로 누르세요.";
            str2[0] = '\0';
        }

    }

}
