#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtGui>
#include <string>
#include <QtSerialPort>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <iomanip>

namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    void setupSerial();
    void setupEngines();
    void setupLight();
    void setupElectromagnet();
    void setupStyles();
    void setupMusic();

    virtual void keyPressEvent(QKeyEvent * event);
    Ui::Widget *ui;
    QSerialPort carPort;
    QString user_music;
    QString tempStr;
    bool carState;
    bool electromagnetState;
    bool lightState;
    int programCarSpeed_motor1;
    int motor1_direction;

    int programCarSpeed_motor2;
    int motor2_direction;

    int TempSpeed;
    bool select;

    char OutMessage[1024];

public slots:
    void carStatus();
    void exit();
    void carAcceleration();
    void carBraking();
    void cangeCarProgramSpeed1();
    void cangeCarProgramSpeed2();
    void carTurnLeft();
    void carTurnRight();
    void ArduinoOut();
    void fillMusicList();
    void SelectMusic();
    void PlayMusic();
    void lightOnOff();
    void electromagnetOnOff();
};


#endif // WIDGET_H
