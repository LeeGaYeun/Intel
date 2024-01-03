#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MoodThread.h"
#include "joystickthread.h"
#include "piezo.h"
#include "calculator.h"
#include "elevator.h"
#include "doorlock.h"
#include <QDebug>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , myThread(new MyThread(this))
    , joyStickThread(new JoyStickThread(this))
    , piezoThread(new PiezoThread(this))
    , calculatorThread(new CalculatorThread(this))
    , elevatorThread(new ElevatorThread(this))
    , doorlockThread(new DoorLockThread(this))
{
    ui->setupUi(this);
    ptrmenu = new Menu();

    delayTimer = new QTimer(this);
    delayTimer->setSingleShot(true);
    connect(delayTimer, SIGNAL(timeout()), this, SLOT(handleDelayTimeout()));

    connect(joyStickThread, SIGNAL(valueChanged(int)), this, SLOT(handleJoystickValueChanged(int)));

    connect(elevatorThread, SIGNAL(floorChanged(int)), this, SLOT(handleElevatorValueChanged(int)));
    connect(elevatorThread, SIGNAL(updateLCD(int)), this, SLOT(updateLCD(int)));

    connect(calculatorThread, SIGNAL(updateTextKey(QString)), this, SLOT(updateTextKey(QString)));

    connect(doorlockThread, SIGNAL(doortext(QString)), this, SLOT(doortext(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete ptrmenu;

}

void MainWindow::on_pushButton_clicked()
{
    if (!myThread->isRunning()) {
        ui->pushButton->setText("Stop MoodLamp");
        myThread->startMoodLamp();
        ui->textBrowser->append("MoodLamp Started");
    }
    else {
        ui->pushButton->setText("Start MoodLamp");
        myThread->stopMoodLamp();
        ui->textBrowser->append("MoodLamp Stop");
        delayTimer->start(1000);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if (!joyStickThread->isRunning()) {
        ui->pushButton_2->setText("Stop JoyStick");
        joyStickThread->startJoyStick();
        ui->textBrowser->append("JoyStick Started");
    }
    else {
        ui->pushButton_2->setText("Start JoyStick");
        joyStickThread->stopJoyStick();
        ui->textBrowser->append("JoyStick Stop");
        delayTimer->start(1000);
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    ptrmenu -> show();
}

void MainWindow::on_pushButton_4_clicked()
{
    if (!piezoThread->isRunning()) {
        ui->pushButton_4->setText("Stop Piezo");
        piezoThread->startPiezo();
        ui->textBrowser->append("Piezo Started");
        ui->textBrowser->append("Keypad 1 = C\nKeypad 2 = D\nKeypad 3 = E\nKeypad 4 = F\nKeypad 5 = G\nKeypad 6 = A\n"
                                "Keypad 7 = B\nKeypad 8 = Song\n");


    }
    else {
        ui->pushButton_4->setText("Start Piezo");
        piezoThread->stopPiezo();
        ui->textBrowser->append("Piezo Stop");
        delayTimer->start(1000);
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    if (!calculatorThread->isRunning()) {
        ui->pushButton_5->setText("Stop Calculator");
        calculatorThread->startCalculator();
        ui->textBrowser->append("Calculator Started");

    }
    else {
        ui->pushButton_5->setText("Start Calculator");
        calculatorThread->stopCalculator();
        ui->textBrowser->append("Calculator Stop");
        delayTimer->start(1000);
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    if (!elevatorThread->isRunning()) {
        ui->pushButton_6->setText("Stop Elevator");
        elevatorThread->startElevator();
        ui->textBrowser->append("Elevator Started");
    }
    else {
        ui->pushButton_6->setText("Start Elevator");
        elevatorThread->stopElevator();
        ui->textBrowser->append("Elevator Stop");
        delayTimer->start(1000);
    }
}

void MainWindow::on_pushButton_7_clicked()
{
    if(!doorlockThread->isRunning()){
        ui->pushButton_7->setText("Stop DoorLock");
        doorlockThread->startDoorLock();
        ui->textBrowser->append("DoorLock Started");
    }
    else {
        ui->pushButton_7->setText("Start DoorLock");
        doorlockThread->stopDoorLock();
        ui->textBrowser->append("DoorLock Stop");
        delayTimer->start(1000);
    }
}

void MainWindow::handleJoystickValueChanged(int newValue)
{
    ui->lcdNumber->display(newValue);
}

void MainWindow::handleElevatorValueChanged(int floorvalue)
{
    ui->lcdNumber->display(floorvalue);
}

void MainWindow::updateLCD(int floor)
{
    ui->lcdNumber->display(floor);
}

void MainWindow::updateTextKey(const QString &str2)
{
    ui->textBrowser->clear();
    ui->textBrowser->append(str2);
}

void MainWindow::doortext(const QString &str5)
{
    ui->textBrowser->clear();
    ui->textBrowser->append(str5);
}

void MainWindow::handleDelayTimeout()
{
    ui->textBrowser->clear();
}
