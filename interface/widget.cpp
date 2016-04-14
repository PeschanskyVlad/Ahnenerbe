#include "opcodes.h"

#include "widget.h"
#include "serialwaiterdialog.h"
#include <QtSerialPort/QSerialPortInfo>
#include <Qt>
#include <algorithm>

using std::min;
using std::max;

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
        resetMotors();
        break;
    }
}

void Widget::updateSpeedSliders(){
    ui->left_speed_slider->setValue(left_motor_speed);
    ui->right_speed_slider->setValue(right_motor_speed);
}

void Widget::updateSpeedLCDs(){
    ui->left_speed_lcd->display((left_motor_speed-50)*2);
    ui->right_speed_lcd->display((right_motor_speed-50)*2);
}

void Widget::updateSpeedDisplays(){
    updateSpeedSliders();
    updateSpeedLCDs();
}

void Widget::setupEngines(){
    left_motor_speed=50;
    right_motor_speed=50;
    left_motor_forward=1;
    right_motor_forward=1;

    ui->left_speed_slider->setRange(0,100);
    ui->right_speed_slider->setRange(0,100);

    updateSpeedDisplays();

    connect(ui->acceleration_btn,&QPushButton::clicked, this, &Widget::carAcceleration);
    connect(ui->breaking_btn, &QPushButton::clicked, this, &Widget::carBraking);
    connect(ui->turn_left_btn,&QPushButton::clicked, this, &Widget::carTurnLeft);
    connect(ui->turn_right_btn, &QPushButton::clicked, this, &Widget::carTurnRight);

    connect(ui->left_speed_slider, &QSlider::valueChanged, this, &Widget::change_left_motor_speed);
    connect(ui->right_speed_slider, &QSlider::valueChanged, this, &Widget::change_right_motor_speed);
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
    connect(ui->electromagnet_chbox, &QCheckBox::stateChanged, this, &Widget::electromagnetToggle);
}

void Widget::setupLight(){
    light_enabled=false;
    connect(ui->headlight_chbox, &QCheckBox::stateChanged, this, &Widget::lightToggle);
}

void Widget::setupMusic(){
    connect(ui->melody_list,SIGNAL(activated(int)),this,SLOT(SelectMusic(int)));
    connect(ui->refresh_button, &QPushButton::clicked,this, &Widget::fillMusicList);
    connect(ui->play_button, &QPushButton::clicked,this,&Widget::PlayMusic);
    fillMusicList();
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    setupSerial();
    ui->setupUi(this);
    setupLight();
    setupEngines();
    setupElectromagnet();
    setupMusic();

    //TODO: move to setup..() methods
    connect(ui->reset_btn,&QPushButton::clicked,this,&Widget::resetMotors);
    QObject::connect(ui->exit_button, SIGNAL(clicked()), this, SLOT(exit()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::resetMotors()
{
    left_motor_speed=50;
    right_motor_speed=50;
    updateSpeedDisplays();
    ArduinoOut();
}

void Widget::exit()
{
    QApplication::exit();

}

void Widget::carAcceleration()
{
    left_motor_speed = min(100,left_motor_speed+5);
    right_motor_speed = min(100,right_motor_speed+5);

    updateSpeedDisplays();

    ArduinoOut();
}

void Widget::carBraking()
{
    left_motor_speed = max(0,left_motor_speed-5);
    right_motor_speed = max(0,right_motor_speed-5);

    updateSpeedDisplays();

    ArduinoOut();

}

void Widget::carTurnLeft()
{
    left_motor_speed = max(0,left_motor_speed-5);
    right_motor_speed = min(100,right_motor_speed+5);

    updateSpeedDisplays();

    ArduinoOut();
}

void Widget::carTurnRight()
{
    left_motor_speed = min(100,left_motor_speed+5);
    right_motor_speed = max(0,right_motor_speed-5);

    updateSpeedDisplays();

    ArduinoOut();
}

//TODO: Rename, refactor
void Widget::ArduinoOut()
{
    left_motor_forward = left_motor_speed>=50;
    right_motor_forward = right_motor_speed>=50;

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
        //TODO:WTF add some error handling
    }
    QTextStream in(&F);
    OutMessage[0]=OP_LOAD_MUSIC;
    int i=1;
    while (!in.atEnd())
    {
        OutMessage[i]=in.readLine().toInt();
        ++i;
    }
    F.close();

    carPort.write(OutMessage,i);
}

void Widget::lightToggle()
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

void Widget::electromagnetToggle()
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

void Widget::change_left_motor_speed(int val)
{
    left_motor_speed = val;
    updateSpeedLCDs();
    ArduinoOut();
}

void Widget::change_right_motor_speed(int val)
{
    right_motor_speed = val;
    updateSpeedLCDs();
    ArduinoOut();
}
