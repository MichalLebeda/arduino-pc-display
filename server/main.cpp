#include <QCoreApplication>
#include "arduinoserialwritter.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ArduinoSerialWritter arduino;

    if(arduino.connect()){
        arduino.startLoop();
    }

    return a.exec();
}
