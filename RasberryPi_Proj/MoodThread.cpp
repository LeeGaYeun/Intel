// MyThread.cpp
#include "MoodThread.h"
#include <wiringPi.h>
#include <softPwm.h>
#include <QDebug>

const int pinLed = 3;

MyThread::MyThread(QObject *parent) : QThread(parent), moodcheck(false)
{
    wiringPiSetupGpio();
    softPwmCreate(pinLed, 0, 200); // PWM 초기화
}

MyThread::~MyThread()
{
    stopMoodLamp(); // 스레드 종료 전에 무드램프 중지
    wait();         // 스레드가 종료될 때까지 대기
}

void MyThread::run()
{
    while (moodcheck) {
        for (int i = 0; i < 200; i++) {
            if(!moodcheck)    break;
            softPwmWrite(pinLed, i);
            delay(20);
        }
    }

    // 종료 시 LED를 끈다.
    softPwmWrite(pinLed, 0);
}

void MyThread::startMoodLamp()
{
    if (!isRunning()) {
        moodcheck = true;
        start();
    } else {
        qDebug() << "Mood lamp is already running.";
    }
}

void MyThread::stopMoodLamp()
{
    if (isRunning()) {
        moodcheck = false;
        wait(); // 스레드가 종료될 때까지 대기
    } else {
        qDebug() << "Mood lamp is not running.";
    }
}
