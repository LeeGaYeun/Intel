#ifndef DOORLOCK_H
#define DOORLOCK_H

#include <QThread>

class DoorLockThread : public QThread
{
    Q_OBJECT

public:
    DoorLockThread(QObject *parent = nullptr);
    ~DoorLockThread();

    void run() override;

public slots:
    void startDoorLock();
    void stopDoorLock();
    void keypad4text(char key);
    void savekey(char key);
    void unlockDoor();
    void menu();

signals:
    void doortext(const QString &str5);

private:
    bool doorlockcheck;
    QString str5;
};

#endif // DOORLOCK_H
