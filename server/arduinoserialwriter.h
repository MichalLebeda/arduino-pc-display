#ifndef CORE_H
#define CORE_H
#include <QDebug>
#include <QtSerialPort/QtSerialPort>

class ArduinoSerialWriter
{
public:
    ArduinoSerialWriter();

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
