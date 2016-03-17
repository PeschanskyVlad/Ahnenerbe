#include "widget.h"
#include "time.h"
#include "ui_widget.h"
#include <Windows.h>

#include <Qt>

void Widget::keyPressEvent(QKeyEvent * event){
    switch(event->key()){
    case Qt::Key_W:
       // ui->pushButton->setStyleSheet("QPushButton{background-color: lightgrey; border-style: outset; border-width: 5px; border-color: red; }");
       // Sleep(10);
       // ui->pushButton->setStyleSheet("QPushButton{background-color: lightgrey; border-style: outset; border-width: 5px; border-color: gray; }");
        carAcceleration();
        break;
    case Qt::Key_A:
        ui->textEdit->setText("a");
        break;
    case Qt::Key_S:
        ui->textEdit->setText("s");
        carBraking();
        break;
    case Qt::Key_D:
        ui->textEdit->setText("d");
        break;
    }

    //ui->textEdit->setText(event->text());

}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    carState=false;
    programCarSpeed=50;
    electromagnetState=false;
    ui->setupUi(this);
    QObject::connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(carStatus()));
    QObject::connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(electromagnetStatus()));
    QObject::connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(exit()));
    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(carAcceleration()));
    QObject::connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(carBraking()));
    QObject::connect(ui->verticalSlider, SIGNAL(valueChanged(int)), this, SLOT(cangeCarPrograSpeed()));

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

    ui->pushButton_6->setStyleSheet("QPushButton{background-color: lightgrey; border-style: outset; border-width: 5px; border-color: gray; }"
"QPushButton:hover{background-color: lightgrey; border-style: outset; border-width: 5px; border-color: red;}");

    ui->pushButton_7->setStyleSheet("QPushButton{background-color: lightgrey; border-style: outset; border-width: 5px; border-color: gray; }"
"QPushButton:hover{background-color: lightgrey; border-style: outset; border-width: 5px; border-color: red;}");

    ui->verticalSlider->setValue(programCarSpeed);


}

Widget::~Widget()
{
    delete ui;
}

void Widget::carStatus()
{
    carState = !carState;
    if(carState){
        programCarSpeed=50;
        ui->verticalSlider->setValue(programCarSpeed);
     ui->textEdit->setText("Online");

    }
    else {
        programCarSpeed=50;
        ui->verticalSlider->setValue(programCarSpeed);
        ui->textEdit->setText("Offline");

    }

}

void Widget::electromagnetStatus()
{
    if(electromagnetState){
     ui->textEdit_5->setText("On");

    }
    else {
        ui->textEdit_5->setText("Off");

    }
    electromagnetState = !electromagnetState;
}

void Widget::exit()
{
    QApplication::exit();

}

void Widget::carAcceleration()
{
    if (programCarSpeed<100){
        programCarSpeed=programCarSpeed+10;
    }
    ui->verticalSlider->setValue(programCarSpeed);
   // ui->label_10->setText(QString("%1").arg(programCarSpeed));
}

void Widget::carBraking()
{
    if (programCarSpeed>0){
        programCarSpeed=programCarSpeed-10;
    }
    ui->verticalSlider->setValue(programCarSpeed);
}

void Widget::cangeCarPrograSpeed()
{
    programCarSpeed = ui->verticalSlider->value();
}




