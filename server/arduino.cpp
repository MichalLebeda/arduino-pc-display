#include "arduino.h"
#include <QSerialPortInfo>

ArduinoBoard::ArduinoBoard()
{

}

void ArduinoBoard::startLoop(){
    while(true){
        updateCpu();
        sleep(1);
        updateRam();
        sleep(1);
    }
}

void ArduinoBoard::updateCpu(){
    QString output = runProcces("cat /sys/class/thermal/thermal_zone0/temp");
    output.remove("\n");

    const char data = (int)output.toFloat()/1000;
    sendBytes('C',data);
}

void ArduinoBoard::updateRam(){
    QString output = runProcces("/bin/sh", QStringList()<< "-c"<< "free | grep Mem | awk '{print $3/$2 * 100}'");
    output.remove("\n");

    const char data = (int)output.toFloat();
    sendBytes('M',data);
}

QString ArduinoBoard::runProcces(QString command){
    QProcess process;
    process.start(command);
    process.waitForFinished(-1);
    QString output = process.readAllStandardOutput();
    return output;
}

QString ArduinoBoard::runProcces(QString command, QStringList arguments){
    QProcess process;
    process.start(command, arguments);
    process.waitForFinished(-1);
    QString output = process.readAllStandardOutput();
    return output;
}

void ArduinoBoard::sendBytes(const char identifier, const char data)
{
    if (arduino->isOpen() && arduino->isWritable())
    {
        arduino->write(&identifier);
        arduino->write(&data);
        arduino->flush();
        qDebug() << "data has been send:"<<identifier<<int(data);
    }else{
        qDebug() << "couldn't write to serial";
    }
}

bool ArduinoBoard::connect(){
    QString arduinoPort;
    bool foundPort = false;

    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        if(info.manufacturer().contains(QString("Arduino"),Qt::CaseInsensitive)){
            arduinoPort = info.portName();
            foundPort = true;
            break;
        }
    }

    if(foundPort){
        arduino = new QSerialPort(arduinoPort);
        arduino->setBaudRate(QSerialPort::Baud4800);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
        arduino->open(QIODevice::ReadWrite);

        qWarning()<<"connected successfully"<<endl;
        return true;
    }

    qWarning()<<"connection failed"<<endl;
    return false;
}

