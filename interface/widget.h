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
    virtual void keyPressEvent(QKeyEvent * event);
    //virtual void sliderMoved();
    Ui::Widget *ui;
    QSerialPort carPort;
    QString user_music;
    QString tempStr;
    //fstream F;
    bool carState;
    bool electromagnetState;
    int programCarSpeed_motor1;
    int motor1_direction;

    int programCarSpeed_motor2;
    int motor2_direction;

    int TempSpeed;
    bool select;

    char OutMessage[1024];

public slots:
    void carStatus();
public slots:
 //   void electromagnetStatus();
public slots:
    void exit();
public slots:
    void carAcceleration();
public slots:
    void carBraking();
public slots:
    void cangeCarProgramSpeed1();
public slots:
    void cangeCarProgramSpeed2();
public slots:
    void carTurnLeft();
public slots:
    void carTurnRight();
public slots:
    void ArduinoOut();
public slots:
    void fillMusicList();
public slots:
    void SelectMusic();
public slots:
    void PlayMusic();

};


#endif // WIDGET_H
