#include <QCoreApplication>
#include "arduinoserialwriter.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ArduinoSerialWriter arduino;

    if(arduino.connect()){
        arduino.startLoop();
    }else{
        exit(0);
    }

    return a.exec();
}
