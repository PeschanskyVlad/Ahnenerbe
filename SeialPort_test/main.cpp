#include <QtSerialPort/QSerialPort>
#include <QSerialPortInfo>

#include <QTextStream>
#include <QCoreApplication>
#include <QStringList>

QT_USE_NAMESPACE


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QSerialPort port(QSerialPortInfo::availablePorts()[0]);
    port.setBaudRate(9600);
    port.open(QIODevice::ReadOnly);

    QTextStream so(stdout);
    while (port.waitForReadyRead(1000)){
        QByteArray readData = port.readAll();
        so<<readData;
        so.flush();
    }


    return app.exec();
}
