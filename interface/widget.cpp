#include "opcodes.h"

#include "widget.h"
#include "time.h"
#include "ui_widget.h"
#include <cstdlib>
#include <iostream>
#include "serialwaiterdialog.h"

#include <QtSerialPort/QSerialPortInfo>

#include <Qt>

void Widget::keyPressEvent(QKeyEvent * event){

    switch(event->key()){
    case Qt::Key_W:
        carAcceleration();
        break;
    case Qt::Key_A:
        carTurnLeft();
        break;
    case Qt::Key_S:
        carBraking();
        break;
    case Qt::Key_D:
        carTurnRight();
        break;

    case Qt::Key_Escape:
    carStatus();
    break;
    }
}

void Widget::setupEngines(){
    left_motor_speed=50;
    right_motor_speed=50;
    left_motor_forward=1;
    right_motor_forward=1;

    ui->left_speed_slider->setValue(left_motor_speed);
    ui->right_speed_slider->setValue(right_motor_speed);
    ui->left_speed_slider->setRange(0,100);
    ui->right_speed_slider->setRange(0,100);

    connect(ui->acceleration_btn,&QPushButton::clicked, this, &Widget::carAcceleration);
    connect(ui->breaking_btn, &QPushButton::clicked, this, &Widget::carBraking);
    connect(ui->turn_left_btn,&QPushButton::clicked, this, &Widget::carTurnLeft);
    connect(ui->turn_right_btn, &QPushButton::clicked, this, &Widget::carTurnRight);

    connect(ui->left_speed_slider, &QSlider::valueChanged, this, &Widget::cangeCarProgramSpeed1);
    connect(ui->right_speed_slider, &QSlider::valueChanged, this, &Widget::cangeCarProgramSpeed2);
}

void Widget::setupSerial(){
    SerialWaiterDialog swd(this);

    swd.exec();
    QString port_name = swd.get_selection();

    if(port_name.isNull()) std::exit(1);

    carPort.setPortName(port_name);
    carPort.setBaudRate(QSerialPort::Baud9600);
    carPort.open(QIODevice::ReadWrite);
}

void Widget::setupElectromagnet(){
    electromagnet_enabled=false;
    connect(ui->electromagnet_chbox, QCheckBox::stateChanged, this, &Widget::electromagnetOnOff);
}

void Widget::setupLight(){
    light_enabled=false;
    connect(ui->headlight_chbox, QCheckBox::stateChanged, this, &Widget::lightOnOff);
}

void Widget::setupMusic(){
    connect(ui->melody_list,SIGNAL(activated(int)),this,SLOT(SelectMusic(int)));
    connect(ui->refresh_button, &QPushButton::clicked,this, &Widget::fillMusicList);
    connect(ui->play_button, &QPushButton::clicked,this,&Widget::PlayMusic);
    fillMusicList();
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)//,
    //carState(false)
{
    setupSerial();
    ui->setupUi(this);
    setupLight();
    //TODO: rename carState, lightState to carEnabled, lightEnabled
    setupEngines();
    setupElectromagnet();

    //TODO: move to setup..() methods
    connect(ui->reset_btn,&QPushButton::clicked,this,&Widget::carStatus);
    QObject::connect(ui->reset_btn,SIGNAL(clicked()),this,SLOT(carStatus()));
    QObject::connect(ui->exit_button, SIGNAL(clicked()), this, SLOT(exit()));
}

Widget::~Widget()
{
    delete ui;
}


//TODO: Rename, refactor
void Widget::carStatus()
{
    //carState = !carState; //FIXME: WTF? В чём разница между этими 2 ветками?
    //if(carState){
        left_motor_speed=50;
        right_motor_speed=50;
        ui->left_speed_slider->setValue(left_motor_speed);
         ui->right_speed_slider->setValue(right_motor_speed);
         ui->left_speed_lcd->display((left_motor_speed-50)*2);
         ui->right_speed_lcd->display((right_motor_speed-50)*2);
    //}
    /*else {
        programCarSpeed_motor1=50;
        programCarSpeed_motor2=50;
        ui->left_speed_slider->setValue(programCarSpeed_motor1);
         ui->right_speed_slider->setValue(programCarSpeed_motor2);
         ui->left_speed_lcd->display((programCarSpeed_motor1-50)*2);
         ui->right_speed_lcd->display((programCarSpeed_motor2-50)*2);
    }*/
ArduinoOut();
}

void Widget::exit()
{
    QApplication::exit();

}

//TODO:Refactor
void Widget::carAcceleration()
{

        left_motor_speed+=5;
        right_motor_speed+=5;

        if(left_motor_speed>100){
            left_motor_speed=100;
        }
        if(right_motor_speed>100){
          right_motor_speed=100;
       }

        ui->left_speed_slider->setValue(left_motor_speed);
         ui->right_speed_slider->setValue(right_motor_speed);
    ui->left_speed_lcd->display((left_motor_speed-50)*2);
    ui->right_speed_lcd->display((right_motor_speed-50)*2);

    ArduinoOut();
}

//TODO:Refactor
void Widget::carBraking()
{

    left_motor_speed-=5;
    right_motor_speed-=5;

        if(left_motor_speed<0){
            left_motor_speed=0;
        }
        if(right_motor_speed<0){
            right_motor_speed=0;
        }

        ui->left_speed_slider->setValue(left_motor_speed);
         ui->right_speed_slider->setValue(right_motor_speed);
     ui->left_speed_lcd->display((left_motor_speed-50)*2);
     ui->right_speed_lcd->display((right_motor_speed-50)*2);

ArduinoOut();

}

void Widget::cangeCarProgramSpeed1()
{
    left_motor_speed = ui->left_speed_slider->value();
     ui->left_speed_lcd->display((left_motor_speed-50)*2);
     ArduinoOut();
    // programCarSpeed_motor2 = ui->right_speed_slider->value();
}

//TODO:Refactor
void Widget::carTurnLeft()
{
     right_motor_speed+=5;
     left_motor_speed-=5;

     if(right_motor_speed>100){
     right_motor_speed=100;
     }
     if(left_motor_speed<0){
     left_motor_speed=0;
     }
     ui->left_speed_slider->setValue(left_motor_speed);
      ui->right_speed_slider->setValue(right_motor_speed);
  ui->left_speed_lcd->display((left_motor_speed-50)*2);
  ui->right_speed_lcd->display((right_motor_speed-50)*2);
  ArduinoOut();
     }

//TODO:Refactor
void Widget::carTurnRight()
{
    right_motor_speed-=5;
    left_motor_speed+=5;

    if(left_motor_speed>100){
    left_motor_speed=100;
    }
    if(right_motor_speed<0){
    right_motor_speed=0;
    }
    ui->left_speed_slider->setValue(left_motor_speed);
     ui->right_speed_slider->setValue(right_motor_speed);
 ui->left_speed_lcd->display((left_motor_speed-50)*2);
 ui->right_speed_lcd->display((right_motor_speed-50)*2);
 ArduinoOut();
}

//TODO: Rename, refactor
void Widget::ArduinoOut()
{
    if(left_motor_speed>=50){
        left_motor_forward=1;
    }
    else{
        left_motor_forward=0;
    }

    if(right_motor_speed>=50){
        right_motor_forward=1;
    }
    else{
        right_motor_forward=0;
    }

    int TempSpeed=abs(left_motor_speed-50)*5;
    OutMessage[0]=OP_MOVE;
    OutMessage[1]=TempSpeed;
    OutMessage[2]=left_motor_forward;
    TempSpeed=abs(right_motor_speed-50)*5;
    OutMessage[3]=TempSpeed;
    OutMessage[4]=right_motor_forward;

    carPort.write(OutMessage,5);
}

void Widget::fillMusicList()
{
    ui->melody_list->clear();
    QDir dir(QDir::currentPath()+"/Melodies");

    QStringList files = dir.entryList(QStringList() << "*.txt", QDir::Files);

    for(int i = 0; i < files.size(); ++i){
        QString curr_file = files.at(i);
        QString tempStr = curr_file.left(curr_file.indexOf('.'));
        ui->melody_list->addItem(tempStr,curr_file);

    }
    music_selected=false;
    ui->play_button->setEnabled(false);
}

void Widget::SelectMusic(int selection)
{
    this->user_music = ui->melody_list->currentData().toString();
    music_selected = true;
    ui->play_button->setEnabled(true);
}


void Widget::PlayMusic()
{
    QFile F(QDir::currentPath()+"/Melodies/"+user_music);
    if(!F.open(QIODevice::ReadOnly)){
      //TODO:WTF
    }
    QTextStream in(&F);
    OutMessage[0]=OP_LOAD_MUSIC;
    int i=1;
        while (!in.atEnd())
        {
            OutMessage[i]=in.readLine().toInt();
            ++i;
        }
     OutMessage[i] = OP_PLAY_MUSIC;
     F.close();

     carPort.write(OutMessage,i+1);
}

void Widget::lightOnOff()
{
    if(light_enabled){
        OutMessage[0]=OP_LED_OFF;
        OutMessage[1]=0;//TODO: not need
        light_enabled=false;
        carPort.write(OutMessage,2);

    }else{
        light_enabled=true;
        OutMessage[0]=OP_LED_ON;
        OutMessage[1]=1;//TODO: not need
        carPort.write(OutMessage,2);
    }
}

void Widget::electromagnetOnOff()
{
    if(electromagnet_enabled){
        OutMessage[0]=OP_CARGO_ON;
        OutMessage[1]=0;//TODO: this not need
        electromagnet_enabled=false;
        carPort.write(OutMessage,2);

    }else{
        electromagnet_enabled=true;
        OutMessage[0]=OP_CARGO_OFF;
        OutMessage[1]=1;//TODO: Don't need to send status
        carPort.write(OutMessage,2);
    }

}

void Widget::cangeCarProgramSpeed2()
{
     right_motor_speed = ui->right_speed_slider->value();
     ui->right_speed_lcd->display((right_motor_speed-50)*2);
     ArduinoOut();
}
