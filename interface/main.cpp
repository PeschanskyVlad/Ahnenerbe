#include <QApplication>
#include "widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

  // while(1){
   //Sleep(10);
   //}
    puts(QSerialPortInfo::availablePorts());
    Widget w;
    w.show();

    return a.exec();
}
