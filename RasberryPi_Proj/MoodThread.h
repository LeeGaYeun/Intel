// MyThread.h
#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class MyThread : public QThread
{
    Q_OBJECT

public:
    MyThread(QObject *parent = nullptr);
    ~MyThread();

    void run() override;

public slots:
    void startMoodLamp();
    void stopMoodLamp();

private:
    bool moodcheck;
};

#endif // MYTHREAD_H
