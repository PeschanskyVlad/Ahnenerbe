#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtGui>
#include <string>

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
    bool carState;
    bool electromagnetState;
    int programCarSpeed_motor1;
    int programCarSpeed_motor2;

public slots:
    void carStatus();
public slots:
    void electromagnetStatus();
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

};


#endif // WIDGET_H
