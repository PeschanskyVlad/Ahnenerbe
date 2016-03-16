#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    carState=false;
    electromagnetState=false;
    ui->setupUi(this);
    QObject::connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(carStatus()));
    QObject::connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(electromagnetStatus()));
    QObject::connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(exit()));
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

    ui->verticalSlider->setValue(50);


}

Widget::~Widget()
{
    delete ui;
}

void Widget::carStatus()
{
    if(carState){
     ui->textEdit->setText("Online");

    }
    else {
        ui->textEdit->setText("Offline");

    }
    carState = !carState;
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




