#include "piezo.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <stdio.h>
#include <wiringPi.h>
#include <softTone.h>
#include <QDebug>


const int pinPiezo = 7;
const int melody[] = {262, 294, 330, 349, 392, 440, 494, 523};
int CNUM1[] = {27, 17, 26, 1};
int RNUM1[] = {22, 23, 24, 25};
char CT1[4][4] = {
    {'1', '2', '3', 'x'},
    {'4', '5', '6', 'x'},
    {'7', '8', '9', 'x'},
    {'x', '0', 'x', 'x'}
};

void setup1();
char keypad1();
void peizoplay(char key);

PiezoThread::PiezoThread(QObject *parent) : QThread(parent), piezocheck(false)
{
    setup1();
}

PiezoThread::~PiezoThread()
{
    stopPiezo();
    wait();
}

void PiezoThread::run()
{
    char key;
    while (piezocheck) {
        char key = keypad1();
        peizoplay(key);
        if(!piezocheck)    break;
    }
}

void PiezoThread::startPiezo()
{
    if (!isRunning()) {
        piezocheck = true;
        start();
    } else {
        qDebug() << "Peizo is already running.";
    }
}

void PiezoThread::stopPiezo()
{
    if (isRunning()) {
        piezocheck = false;
        wait(); // 스레드가 종료될 때까지 대기
    } else {
        qDebug() << "Piezo is not running.";
    }
}

void setup1()
{
    wiringPiSetupGpio();
    softToneCreate(pinPiezo);
    for(int i = 0; i < 4; i++){
        pinMode(RNUM1[i], OUTPUT);
        pinMode(CNUM1[i], INPUT);
        pullUpDnControl(CNUM1[i], PUD_UP);
        digitalWrite(RNUM1[i], HIGH);
    }
}

char keypad1()
{
    for(int i = 0; i < 4; i++){
        //현재 행이 눌렸을 때
        digitalWrite(RNUM1[i], LOW);
        if(digitalRead(RNUM1[i]) == LOW){
            //각 열의 입력을 확인하고 해당하는 키 호출
            for(int j = 0; j < 4; j++){
                if(digitalRead(CNUM1[j]) == LOW){
                        return(CT1[i][j]);
                }
            }
            delay(45); //디바운싱을 위한 딜레이
        }

        digitalWrite(RNUM1[i], HIGH); //다시 모든 행을 HIGH로 설정
    }
    return '\0';
}

void peizoplay(char key)
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
