#include "calculator.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <stdio.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <QDebug>

int xio;
int i, j;
char str1[16];

int CNUM3[] = {27, 17, 26, 1};
int RNUM3[] = {22, 23, 24, 25};

char CT3[4][4] = {
     {'1', '2', '3', '+'},
     {'4', '5', '6', '-'},
     {'7', '8', '9', '*'},
     {'=', '0', '#', '/'}
};

void setup3();
char keypad3();
void calculator(char key);

CalculatorThread::CalculatorThread(QObject *parent) : QThread(parent), calculatorcheck(false)
{
    setup3();
}

CalculatorThread::~CalculatorThread()
{
    stopCalculator();
    wait();
}

void CalculatorThread::run()
{
    char key;
    while (calculatorcheck) {
        char key = keypad3();
        keypad3text(key);
        calculator(key);
        // 이 부분에서 LCD에 표시
        if(!calculatorcheck)    break;
    }
}

void CalculatorThread::startCalculator()
{
    if (!isRunning()) {
        calculatorcheck = true;
        start();
    } else {
        qDebug() << "Calculaotr is already running.";
    }
}

void CalculatorThread::stopCalculator()
{
    if (isRunning()) {
        calculatorcheck = false;
        wait(); // 스레드가 종료될 때까지 대기
    } else {
        qDebug() << "Calculator is not running.";
    }
}

void setup3()
{
    wiringPiSetupGpio();
    for (i = 0; i < 4; i++)
    {
        pinMode(RNUM3[i], OUTPUT); //키패드 행은 출력 모드
        pinMode(CNUM3[i], INPUT);  //키패드 열은 입력 모드
        pullUpDnControl(CNUM3[i], PUD_UP); //입력 핀에 Pull-up resistor 적용
        digitalWrite(RNUM3[i], HIGH);      //초기에는 모든 행을 HIGH로 설정
    }
}

char keypad3()
{
    for(int i = 0; i < 4; i++){
        //현재 행이 눌렸을 때
        digitalWrite(RNUM3[i], LOW);
        if(digitalRead(RNUM3[i]) == LOW){
            for(int j = 0; j < 4; j++){
                if(digitalRead(CNUM3[j]) == LOW){
                        delay(200);
                        return CT3[i][j];
                }
            }
        }
        digitalWrite(RNUM3[i], HIGH); //다시 모든 행을 HIGH로 설정
    }
    return '\0';
}

void CalculatorThread::keypad3text(char key)
{
    if(key >= '0' && key <= '9' || key == '+' || key == '-' || key == '*' || key == '/' || key == '=')
    {
        str2.append(key);
        emit updateTextKey(str2);
    }
}

void CalculatorThread::calculator(char key)
{
    //정적 변수 선언 및 초기화
    static double num = 0;
    static int num2 = 0;
    static double renum = 0;
    static int oper = 0;
    static int abs = 1;

    //숫자 키가 입력되었을 때의 동작을 처리하는 함수
    if(key >= '0' && key <= '9'){
            num = num * 10.0 + (key - '0'); //현재까지 입력된 숫자를 갱신
            sprintf(str1, "%.0f", num); //LCD에 출력할 형식으로 문자열 생성
            qDebug() << str1;
    }
    //연산자 또는 특수 키가 입력되었을 때의 동작을 처리하는 함수
    if(key == '+' || key == '-' || key == '*' || key == '/' || key == '#'){
        if (oper == 0){ //연산자 입력을 받는 중인 상태인지 확인
        switch(key){
            case('+'):
                renum += num; //누적된 결과에 현재까지 입력된 숫자를 더함
                num = 0;      //현재까지 입력된 숫자 초기화
                num2 = key;   //현재 연산자 저장
                qDebug() << "+";
                break;

            case('-'):
                renum += abs * num; //누적된 결과에 현재까지 입력된 숫자를 더하거나 빼기
                num = 0;            //현재까지 입력된 숫자 초기화
                abs = -1;           //뺄셈을 나타내는 부호 변경
                num2 = key;         //현재 연산자 저장
                qDebug() << "-";
                break;

            case('*'):
                if(renum == 0){
                    renum = 1; //처음 입력된 연산이 '*'일 때 초기값 설정
                }
                renum *= num;    //누적된 결과에 현재까지 입력된 숫자를 곱함
                num = 0;         //현재까지 입력된 숫자 초기화
                num2 = key;      //현재 연산자 저장
                qDebug() << "*";
                break;

            case('/'):
                if(renum == 0){
                    renum = num;; //처음 입력된 연산이 '/'일 때 초기값 설정
                }
                else{
                renum /= num;     //누적된 결과에 현재까지 입력된 숫자를 나눔
                }
                num = 0;          //현재까지 입력된 숫자 초기화
                num2 = key;       //현재 연산자 저장
                qDebug() << "/";
                break;

            case('#'):
                qDebug() << "Clear";
                renum = 0; //결과 변수 초기화
                num = 0;   //현재까지 입력된 숫자 초기화
                num2 = 0;  //현재 연산자 초기화
                abs = 1;   //부호 초기화
                emit updateTextKey("Clear");
                str2 = '\0';
                break;
        }
        oper = 1; //연산자 입력중인 상태로 설정
            if(key != '+' || key != '-' || key != '*' || key != '/' || key != '#'){
                oper = 0;  //다음 입력에 대한 연산자 상태 초기화
            }
        }
    }

//등호 (=) 키가 입력되었을 때의 동작을 처리하는 함수
    if(key == '='){
        switch(num2){
            case('+'):
                renum += num; //현재까지 입력된 숫자를 더함
                qDebug() << "= " << renum;
                str2.append(QString::number(renum));
                emit updateTextKey(str2);
                str2 = '\0';
                renum = 0;        //결과 변수 초기화
                num = 0;          //현재까지 입력된 숫자 초기화
                break;

            case('-'):
                renum += abs * num; //현재까지 입력된 숫자를 더하거나 빼기
                abs = 1;            //부호 초기화
                qDebug() << "= " << renum;
                str2.append(QString::number(renum));
                emit updateTextKey(str2);
                str2 = '\0';
                renum = 0;          //결과 변수 초기화
                num = 0;            //현재까지 입력된 숫자 초기화
                break;

            case('*'):
                renum *= num;       //현재까지 입력된 숫자를 곱함
                qDebug() << "= " << renum;
                str2.append(QString::number(renum));
                emit updateTextKey(str2);
                str2 = '\0';
                renum = 0;          //결과 변수 초기화
                num = 0;            //현재까지 입력된 숫자 초기화
                break;

            case('/'):
                renum /= num;
                qDebug() << "= " << renum;
                str2.append(QString::number(renum));
                emit updateTextKey(str2);
                str2 = '\0';
                renum = 0;
                num = 0;
                break;
        }
    }
}
