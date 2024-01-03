#ifndef JOYSTICKTHREAD_H
#define JOYSTICKTHREAD_H

#include <QThread>

class JoyStickThread : public QThread
{
    Q_OBJECT

public:
    JoyStickThread(QObject *parent = nullptr);
    ~JoyStickThread();

    void run() override;
signals:
    void valueChanged(int newValue);

public slots:
    void startJoyStick();
    void stopJoyStick();

private:
    bool joycheck;
};

#endif // JOYSTICKTHREAD_H
