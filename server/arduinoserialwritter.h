#ifndef CORE_H
#define CORE_H
#include <unistd.h>
#include <QDebug>
#include <QtSerialPort/QtSerialPort>
#include "sys/types.h"


class ArduinoSerialWritter
{
public:
    ArduinoSerialWritter();

    void startLoop();
    bool connect();

private:
    QSerialPort *arduino;
    QString runProcces(QString command);
    QString runProcces(QString command, QStringList arguments);

    void updateCpu();
    void updateRam();
    void sendBytes(const char identifier, const char data);
    QByteArray mergeBytes(const char identifier, const char data);
};

#endif // CORE_H
