#include "doorlock.h"
#include "lcd1602.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <stdio.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdbool.h>
#include <softTone.h>
#include <QDebug>

const int pinPiezo = 7;
const int melody[] = {262,294,330,349,392,440,494,523};
int doorUnlockMelody[] = {523, 587, 659, 698, 784, 880, 988, 1047};
int wrongPasswordMelody[] = {262, 220, 196, 220};
int changePasswordMelody[] = {523, 587, 659, 698};
bool changePwd = false;
static int count = 1;
char str4[16];
int CNUM4[] = {27, 17, 26, 1};
int RNUM4[] = {22, 23, 24, 25};

// 도어락 비밀번호
char doorLockPassword[] = "0000"; // 임의의 초기 비밀번호 설정

char CT4[4][4] = {
    {'1', '2', '3', '+'},
    {'4', '5', '6', '-'},
    {'7', '8', '9', '*'},
    {'*', '0', '#', '/'}
};

void menu();
void setup4();
char keypad4();
void savekey(char key);
void unlockDoor();
void playMelody(const int *melody, int length, int delayBetweenNotes);

DoorLockThread::DoorLockThread(QObject *parent) : QThread(parent), doorlockcheck(false)
{
    setup4();
}

DoorLockThread::~DoorLockThread()
{
    stopDoorLock();
    wait();
}

void DoorLockThread::run()
{
    char key;
    delay(1000);
    menu();
    while(doorlockcheck){
        key = keypad4();
        savekey(key);
        keypad4text(key);
        if(!doorlockcheck)  break;
    }
}

void DoorLockThread::startDoorLock()
{
    if(!isRunning()){
        doorlockcheck = true;
        start();
    } else {
        qDebug() << "DoorLock is already running.";
    }
}

void DoorLockThread::stopDoorLock()
{
    if(isRunning()){
        doorlockcheck = false;
        wait();
    } else {
        qDebug() << "DoorLock is not running.";
    }
}

void setup4()
{
    wiringPiSetupGpio();
    softToneCreate(pinPiezo);
    for (int i = 0; i < 4; i++)
    {
        pinMode(RNUM4[i], OUTPUT);
        pinMode(CNUM4[i], INPUT);
        pullUpDnControl(CNUM4[i], PUD_UP);
        digitalWrite(RNUM4[i], HIGH);
    }
}

char keypad4()
{
    for(int i = 0; i < 4; i++){
        //현재 행이 눌렸을 때
        digitalWrite(RNUM4[i], LOW);
        if(digitalRead(RNUM4[i]) == LOW){
            for(int j = 0; j < 4; j++){
                if(digitalRead(CNUM4[j]) == LOW){
                        delay(200);
                        return CT4[i][j];
                }
            }
        }
        digitalWrite(RNUM4[i], HIGH); //다시 모든 행을 HIGH로 설정
    }
    return '\0';
}

// 눌린 키패드 저장 함수
void DoorLockThread::savekey(char key)
{
    if (key >= '0' && key <= '9')
    {
      softToneWrite(pinPiezo,melody[7]);
      delay(100);
      softToneWrite(pinPiezo,0);
      qDebug() << "*";
      strncat(str4, &key, 1); // str1에 키패드에서 입력받은 값을 추가
    }
    else if (key == '*')
    {
        unlockDoor(); // 도어락 열기 시도
    }
    else if(doorLockPassword[0] == '\0' && key == '#'){
        qDebug() <<"saveNewPwd";
        strcpy(doorLockPassword,str4);
        qDebug() << doorLockPassword;
        str4[0] = '\0';
        playMelody(changePasswordMelody, sizeof(changePasswordMelody) / sizeof(changePasswordMelody[0]), 150);
        str5 = '\0';
        str5.append("Save New PWD");
        emit doortext(str5);
        delay(1000);
        menu();
    }
    else if(key == '#')
    {
        str4[0] == '\0';
        doorLockPassword[0] = '\0';
        str5 = '\0';
        str5.append("Change PWD :");
        emit doortext(str5);
    }
}

// 도어락 열기 시도 함수
void DoorLockThread::unlockDoor()
{
    for(int i = 0; i <4 ; i++){
        qDebug() << "pwd : " << doorLockPassword[i];
    }
    if (strlen(str4) == strlen(doorLockPassword) && strcmp(str4, doorLockPassword) == 0)
    {
        str5 = '\0';
        str5.append("Door Unlocked!");
        emit doortext(str5);
        str5 = '\0';
        str4[0] = '\0'; // str1 초기화
        playMelody(doorUnlockMelody, sizeof(doorUnlockMelody) / sizeof(doorUnlockMelody[0]), 150);
        delay(1500);
        menu();
    }
    else
    {
        str5 = '\0';
        str5.append("Wrong PWD!");
        emit doortext(str5);
        str4[0] = '\0'; // str1 초기화
        playMelody(wrongPasswordMelody, sizeof(wrongPasswordMelody) / sizeof(wrongPasswordMelody[0]), 150);
        delay(1500);
        menu();
    }
}

void playMelody(const int *melody, int length, int delayBetweenNotes)
{
    for (int i = 0; i < length; i++)
    {
        softToneWrite(pinPiezo, melody[i]);
        delay(delayBetweenNotes);
    }
    softToneWrite(pinPiezo, 0); // 소리를 멈춤
}

void DoorLockThread::keypad4text(char key)
{
    if(key >= '0' && key <= '9')
    {
        str5.append("x");
        emit doortext(str5);
    }
}

void DoorLockThread::menu(){
    str5 = '\0';
    str5.append("Door Lock\n PWD : ");
    emit doortext(str5);
}
