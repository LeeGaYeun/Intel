#include "joystickthread.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <mcp3004.h>
#include <QDebug>

#define BASE 100
#define SPI_CHAN 0
#define SW 4

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
static int val = 0;
void moveloop(int tnum);
void currentloop(int tnum);

JoyStickThread::JoyStickThread(QObject *parent) : QThread(parent), joycheck(false)
{
    wiringPiSetupGpio();
    pinMode(SW, INPUT);
    pullUpDnControl(SW, PUD_UP);
    printf("Raseberry Pi SPI ADC Program\n");
    mcp3004Setup(BASE, SPI_CHAN);
    int ledPin[] = {LEDA, LEDB, LEDC, LEDD, LEDE, LEDF, LEDG, LEDDP};
    int sft[] = {SFT1, SFT2, SFT3, SFT4};

    for(int i = 0; i < 8; i++){
        pinMode(ledPin[i], OUTPUT);
        digitalWrite(ledPin[i], 1);
    }

}

JoyStickThread::~JoyStickThread()
{
    stopJoyStick(); // 스레드 종료 전에 무드램프 중지
    wait();         // 스레드가 종료될 때까지 대기
}

void JoyStickThread::run()
{

    static int nowval = 0;
    while (joycheck) {
        int sw = digitalRead(SW);

        currentloop(val);
        for(int i = 0; i < 2; i++){
            qDebug() << "channel" << i << "value : " << analogRead(BASE +i);
            if(i == 0){
                if(analogRead(BASE + i) > 1000){
                    val++;
                    moveloop(val);
                }
                else if(analogRead(BASE + i) < 13){
                    val--;
                    moveloop(val);
                }
            }
            if(sw == 0){
                moveloop(0);
                val = 0;
            }
        }
        emit valueChanged(val); // 시그널 발생
        if(!joycheck)    break;
    }
}

void JoyStickThread::startJoyStick()
{
    if (!isRunning()) {
        joycheck = true;
        start();
    } else {
        qDebug() << "JoyStick is already running.";
    }
}

void JoyStickThread::stopJoyStick()
{
    if (isRunning()) {
        val = 0;
        joycheck = false;
        emit valueChanged(val);
        wait(); // 스레드가 종료될 때까지 대기
    } else {
        qDebug() << "JoyStick is not running.";
    }
}

void moveloop(int tnum) //층 이동 동작을 처리하는 함수
{
    int digit[3]; //층 번호를 일의 자리, 십의 자리, 백의 자리로 분할하여 저장하는 배열
    int k = 0;
    digit[0] = tnum % 10; //일의 자리
    digit[1] = (tnum / 10) % 10; //십의 자리
    digit[2] = (tnum / 100) % 10; //백의 자리
    digit[3] = (tnum / 1000) % 10; //천의 자리
    int ledPin[] = {LEDA, LEDB, LEDC, LEDD, LEDE, LEDF, LEDG, LEDDP};
    int sft[] = {SFT1, SFT2, SFT3, SFT4}; //시프트 레지스터의 핀 배열

    for(int i = 0; i < 4; i++){
    digitalWrite(sft[i], 1); //초기에 모든 시프트 레지스터를 비활성화
   }

    for(k = 0; k < 30; k++){ //다중 자리 세그먼트 디스플레이 동적 제어를 위해 (엘리베이터의 층 이동 동작을 부드럽게 보이게 하기 위해)
   //일의 자리
    digitalWrite(sft[3], 0);
    for(int j = 0; j < 8; j++){
        digitalWrite(ledPin[j], pattern[digit[0]][j]); //일의 자리에 해당하는 패턴
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
