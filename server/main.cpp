#include <QCoreApplication>
#include "arduino.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ArduinoBoard arduino;

    if(arduino.connect()){
        arduino.startLoop();
    }

    return a.exec();
}
