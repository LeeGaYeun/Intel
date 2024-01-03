#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextBrowser>
#include "menu.h"
#include "MoodThread.h"
#include "joystickthread.h"
#include "piezo.h"
#include "calculator.h"
#include "elevator.h"
#include "doorlock.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void handleJoystickValueChanged(int newValue);

    void handleElevatorValueChanged(int floorvalue);

    void updateTextKey(const QString &displayText);

    void updateLCD(int floor);

    void doortext(const QString &str5);

    void handleDelayTimeout();
private:
    Ui::MainWindow *ui;
    QTimer *delayTimer;
    QTextBrowser *textBrowser;
    Menu *ptrmenu;
    MyThread *myThread;
    JoyStickThread *joyStickThread;
    PiezoThread *piezoThread;
    CalculatorThread *calculatorThread;
    ElevatorThread *elevatorThread;
    DoorLockThread *doorlockThread;
};
#endif // MAINWINDOW_H
