#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtGui>
#include <QtSerialPort>

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
    void setupMusic();

    virtual void keyPressEvent(QKeyEvent * event);
    Ui::Widget *ui;
    QSerialPort carPort;
    QString user_music;
    //bool carState; //TODO:WTF: что делает эта переменная?
    bool electromagnet_enabled;
    bool light_enabled;

    int left_motor_speed;
    int left_motor_forward;
    int right_motor_speed;
    int right_motor_forward;

    bool music_selected;

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
    void SelectMusic(int selection_index);
    void PlayMusic();
    void lightOnOff();
    void electromagnetOnOff();
};


#endif // WIDGET_H
