#include "opcodes.h"

#include "widget.h"
#include "time.h"
#include "ui_widget.h"
#include <cstdlib>
#include <iostream>
#include "serialwaiterdialog.h"
#include<windows.h>

#include <QtSerialPort/QSerialPortInfo>

#include <Qt>

//TODO: remove
void Widget::setupStyles(){
    ui->pushButton->setStyleSheet("QPushButton{background-color: lightgrey; border-style: outset; border-width: 5px; border-color: gray; }"
"QPushButton:hover{background-color: lightgrey; border-style: outset; border-width: 5px; border-color: red;}");

    ui->pushButton_2->setStyleSheet("QPushButton{background-color: lightgrey; border-style: outset; border-width: 5px; border-color: gray; }"
"QPushButton:hover{background-color: lightgrey; border-style: outset; border-width: 5px; border-color: red;}");
    ui->pushButton_3->setStyleSheet("QPushButton{background-color: lightgrey; border-style: outset; border-width: 5px; border-color: gray; }"
"QPushButton:hover{background-color: lightgrey; border-style: outset; border-width: 5px; border-color: red;}");
    ui->pushButton_4->setStyleSheet("QPushButton{background-color: lightgrey; border-style: outset; border-width: 5px; border-color: gray; }"
"QPushButton:hover{background-color: lightgrey; border-style: outset; border-width: 5px; border-color: red;}");

    ui->pushButton_5->setStyleSheet("QPushButton{background-color: lightgrey; border-style: outset; border-width: 5px; border-color: gray; }"
"QPushButton:hover{background-color: lightgrey; border-style: outset; border-width: 5px; border-color: red;}");


    ui->pushButton_7->setStyleSheet("QPushButton{background-color: lightgrey; border-style: outset; border-width: 5px; border-color: gray; }"
"QPushButton:hover{background-color: lightgrey; border-style: outset; border-width: 5px; border-color: red;}");

    ui->play_button->setStyleSheet("QPushButton{background-color: lightgrey; border-style: outset; border-width: 5px; border-color: gray; }"
"QPushButton:hover{background-color: lightgrey; border-style: outset; border-width: 5px; border-color: red;}");

    ui->refresh_button->setStyleSheet("QPushButton{background-color: lightgrey; border-style: outset; border-width: 5px; border-color: gray; }"
"QPushButton:hover{background-color: lightgrey; border-style: outset; border-width: 5px; border-color: red;}");
}

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
    programCarSpeed_motor1=50;
    programCarSpeed_motor2=50;
    motor1_direction=1;
    motor2_direction=1;

    ui->verticalSlider->setValue(programCarSpeed_motor1);
    ui->verticalSlider_2->setValue(programCarSpeed_motor2);
    ui->verticalSlider->setRange(0,100);
    ui->verticalSlider_2->setRange(0,100);

    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(carAcceleration()));
    QObject::connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(carBraking()));
    QObject::connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(carTurnRight()));
    QObject::connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(carTurnLeft()));
    QObject::connect(ui->verticalSlider,
       	             SIGNAL(valueChanged(int)),
       	             this, 
		     SLOT(cangeCarProgramSpeed1()));
    QObject::connect(ui->verticalSlider_2,
       	             SIGNAL(valueChanged(int)),
		     this,
		     SLOT(cangeCarProgramSpeed2()));
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
    electromagnetState=false;
    QObject::connect(ui->checkBox_2,
	             SIGNAL(stateChanged(int)),
		     this,
		     SLOT(electromagnetOnOff()));
}

void Widget::setupLight(){
    lightState=false;
    QObject::connect(ui->checkBox,SIGNAL(stateChanged(int)),this,SLOT(lightOnOff()));
}

void Widget::setupMusic(){
    QObject::connect(ui->melody_list,
	             SIGNAL(activated(QString)),
		     this,
		     SLOT(SelectMusic()));
    QObject::connect(ui->refresh_button,
         	     SIGNAL(clicked()),
		     this,
		     SLOT(fillMusicList()));
    QObject::connect(ui->play_button,SIGNAL(clicked()),this,SLOT(PlayMusic()));
    fillMusicList();
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    carState(false)
{
    setupSerial();
    ui->setupUi(this);
    setupStyles();
    setupLight();
    //TODO: rename carState, lightState to carEnabled, lightEnabled
    setupEngines();
    setupElectromagnet();

    //TODO: move to setup..() methods
    QObject::connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(carStatus()));
    QObject::connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(exit()));
}

Widget::~Widget()
{
    delete ui;
}


//TODO: Rename, refactor
void Widget::carStatus()
{
    carState = !carState;
    if(carState){
        programCarSpeed_motor1=50;
        programCarSpeed_motor2=50;
        ui->verticalSlider->setValue(programCarSpeed_motor1);
         ui->verticalSlider_2->setValue(programCarSpeed_motor2);
         ui->lcdNumber->display((programCarSpeed_motor1-50)*2);
         ui->lcdNumber_2->display((programCarSpeed_motor2-50)*2);
     ui->textEdit->setText("Reset");

    }
    else {
        programCarSpeed_motor1=50;
        programCarSpeed_motor2=50;
        ui->verticalSlider->setValue(programCarSpeed_motor1);
         ui->verticalSlider_2->setValue(programCarSpeed_motor2);
         ui->lcdNumber->display((programCarSpeed_motor1-50)*2);
         ui->lcdNumber_2->display((programCarSpeed_motor2-50)*2);
        ui->textEdit->setText("Reset");

    }
ArduinoOut();
}
/*
void Widget::electromagnetStatus()
{
    electromagnetState = !electromagnetState;
    if(electromagnetState){
     ui->textEdit_5->setText("On");

    }
    else {
        ui->textEdit_5->setText("Off");

    }

}
*/
void Widget::exit()
{
    QApplication::exit();

}

void Widget::carAcceleration()
{

        programCarSpeed_motor1+=5;
        programCarSpeed_motor2+=5;

        if(programCarSpeed_motor1>100){
            programCarSpeed_motor1=100;
        }
        if(programCarSpeed_motor2>100){
          programCarSpeed_motor2=100;
       }

        ui->verticalSlider->setValue(programCarSpeed_motor1);
         ui->verticalSlider_2->setValue(programCarSpeed_motor2);
    ui->lcdNumber->display((programCarSpeed_motor1-50)*2);
    ui->lcdNumber_2->display((programCarSpeed_motor2-50)*2);


    ArduinoOut();

   // ui->label_10->setText(QString("%1").arg(programCarSpeed));
}

void Widget::carBraking()
{

    programCarSpeed_motor1-=5;
    programCarSpeed_motor2-=5;

        if(programCarSpeed_motor1<0){
            programCarSpeed_motor1=0;
        }
        if(programCarSpeed_motor2<0){
            programCarSpeed_motor2=0;
        }

        ui->verticalSlider->setValue(programCarSpeed_motor1);
         ui->verticalSlider_2->setValue(programCarSpeed_motor2);
     ui->lcdNumber->display((programCarSpeed_motor1-50)*2);
     ui->lcdNumber_2->display((programCarSpeed_motor2-50)*2);

ArduinoOut();

}

void Widget::cangeCarProgramSpeed1()
{
    programCarSpeed_motor1 = ui->verticalSlider->value();
     ui->lcdNumber->display((programCarSpeed_motor1-50)*2);
     ArduinoOut();
    // programCarSpeed_motor2 = ui->verticalSlider_2->value();
}

void Widget::carTurnLeft()
{
     programCarSpeed_motor2+=5;
     programCarSpeed_motor1-=5;

     if(programCarSpeed_motor2>100){
     programCarSpeed_motor2=100;
     }
     if(programCarSpeed_motor1<0){
     programCarSpeed_motor1=0;
     }
     ui->verticalSlider->setValue(programCarSpeed_motor1);
      ui->verticalSlider_2->setValue(programCarSpeed_motor2);
  ui->lcdNumber->display((programCarSpeed_motor1-50)*2);
  ui->lcdNumber_2->display((programCarSpeed_motor2-50)*2);
  ArduinoOut();
     }


void Widget::carTurnRight()
{
    programCarSpeed_motor2-=5;
    programCarSpeed_motor1+=5;

    if(programCarSpeed_motor1>100){
    programCarSpeed_motor1=100;
    }
    if(programCarSpeed_motor2<0){
    programCarSpeed_motor2=0;
    }
    ui->verticalSlider->setValue(programCarSpeed_motor1);
     ui->verticalSlider_2->setValue(programCarSpeed_motor2);
 ui->lcdNumber->display((programCarSpeed_motor1-50)*2);
 ui->lcdNumber_2->display((programCarSpeed_motor2-50)*2);
 ArduinoOut();
}

//TODO: Rename
void Widget::ArduinoOut()
{
    if(programCarSpeed_motor1>=50){
        motor1_direction=1;
    }
    else{
        motor1_direction=0;
    }

    if(programCarSpeed_motor2>=50){
        motor2_direction=1;
    }
    else{
        motor2_direction=0;
    }

    TempSpeed=abs(programCarSpeed_motor1-50)*5;
    OutMessage[0]=OP_MOVE;
    OutMessage[1]=TempSpeed;
    OutMessage[2]=motor1_direction;
    TempSpeed=abs(programCarSpeed_motor2-50)*5;
    OutMessage[3]=TempSpeed;
    OutMessage[4]=motor2_direction;
    //OutMessage[4]=;

    carPort.write(OutMessage,5);
}

void Widget::fillMusicList()
{

    ui->melody_list->clear();
    QDir dir(QDir::currentPath()+"/Melodies");

    QStringList files = dir.entryList(QStringList() << "*.txt", QDir::Files);

    for(int i = 0; i < files.size(); ++i){
        QString curr_file = files.at(i);
        tempStr=curr_file.left(curr_file.indexOf('.'));
         ui->melody_list->addItem(tempStr,curr_file);

    }
    select=false;
    ui->play_button->setEnabled(false);
}

void Widget::SelectMusic()
{
    this->user_music = ui->melody_list->currentData().toString();
    select = true;
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
     OutMessage[i] = OP_PLAY_MUSIC; //PLAY_MUSIC
     F.close();

     carPort.write(OutMessage,i+1);
}

void Widget::lightOnOff()
{
    if(lightState){
        OutMessage[0]=OP_LED_OFF;
        OutMessage[1]=0;//TODO: not need
        lightState=false;
        carPort.write(OutMessage,2);

    }else{
        lightState=true;
        OutMessage[0]=OP_LED_ON;
        OutMessage[1]=1;//TODO: not need
        carPort.write(OutMessage,2);
    }
}

void Widget::electromagnetOnOff()
{
    if(electromagnetState){
        OutMessage[0]=OP_CARGO_ON;
        OutMessage[1]=0;//TODO: this not need
        electromagnetState=false;
        carPort.write(OutMessage,2);

    }else{
        electromagnetState=true;
        OutMessage[0]=OP_CARGO_OFF;
        OutMessage[1]=1;//TODO: Don't need to send status
        carPort.write(OutMessage,2);
    }

}

void Widget::cangeCarProgramSpeed2()
{
     programCarSpeed_motor2 = ui->verticalSlider_2->value();
     ui->lcdNumber_2->display((programCarSpeed_motor2-50)*2);
     ArduinoOut();
}
