#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QThread>

class ElevatorThread : public QThread
{
    Q_OBJECT
public:
    ElevatorThread(QObject *parent = nullptr);
    ~ElevatorThread();

    void run() override;

signals:
    void floorChanged(int floorvalue);
    void updateLCD(int floor);

public slots:
    void startElevator();
    void stopElevator();
    void moveloop2(int tnum);
    void floornum2(char key);
private:
    bool elevatorcheck;
};

#endif // ELEVATOR_H
