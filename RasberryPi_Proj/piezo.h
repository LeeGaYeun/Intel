#ifndef PIEZO_H
#define PIEZO_H
#include <QThread>

class PiezoThread : public QThread
{
    Q_OBJECT
public:
    PiezoThread(QObject *parent = nullptr);
    ~PiezoThread();

    void run() override;

public slots:
    void startPiezo();
    void stopPiezo();

private:
    bool piezocheck;
};

#endif // PIEZO_H
