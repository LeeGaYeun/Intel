#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QThread>

class CalculatorThread : public QThread
{
    Q_OBJECT
public:
    CalculatorThread(QObject *parent = nullptr);
    ~CalculatorThread();

    void run() override;

public slots:
    void startCalculator();
    void stopCalculator();
    void keypad3text(char key);
    void calculator(char key);

signals:
    void updateTextKey(const QString &displayText);

private:
    bool calculatorcheck;
    QString str2;
};

#endif // CALCULATOR_H
