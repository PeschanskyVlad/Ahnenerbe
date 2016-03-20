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
        //ui->textEdit->setText("a");
        carTurnLeft();
        break;
    case Qt::Key_S:
        //ui->textEdit->setText("s");
        carBraking();
        break;
    case Qt::Key_D:
       // ui->textEdit->setText("d");
        carTurnRight();
        break;
    }

    //ui->textEdit->setText(event->text());

}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    carState=false;
    programCarSpeed_motor1=50;
    programCarSpeed_motor2=50;
    electromagnetState=false;
    ui->setupUi(this);
    QObject::connect(ui->pushButton_5,SIGNAL(clicked()),this,SLOT(carStatus()));
    QObject::connect(ui->pushButton_6,SIGNAL(clicked()),this,SLOT(electromagnetStatus()));
    QObject::connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(exit()));
    QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(carAcceleration()));
    QObject::connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(carBraking()));
    QObject::connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(carTurnRight()));
    QObject::connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(carTurnLeft()));
    QObject::connect(ui->verticalSlider, SIGNAL(valueChanged(int)), this, SLOT(cangeCarProgramSpeed1()));
    QObject::connect(ui->verticalSlider_2, SIGNAL(valueChanged(int)), this, SLOT(cangeCarProgramSpeed2()));

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

    ui->verticalSlider->setValue(programCarSpeed_motor1);
    ui->verticalSlider_2->setValue(programCarSpeed_motor2);
    ui->verticalSlider->setRange(0,100);
    ui->verticalSlider_2->setRange(0,100);


}

Widget::~Widget()
{
    delete ui;
}

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
     ui->textEdit->setText("Online");

    }
    else {
        programCarSpeed_motor1=50;
        programCarSpeed_motor2=50;
        ui->verticalSlider->setValue(programCarSpeed_motor1);
         ui->verticalSlider_2->setValue(programCarSpeed_motor2);
         ui->lcdNumber->display((programCarSpeed_motor1-50)*2);
         ui->lcdNumber_2->display((programCarSpeed_motor2-50)*2);
        ui->textEdit->setText("Offline");

    }

}

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

}

void Widget::cangeCarProgramSpeed1()
{
    programCarSpeed_motor1 = ui->verticalSlider->value();
     ui->lcdNumber->display((programCarSpeed_motor1-50)*2);
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
}

void Widget::cangeCarProgramSpeed2()
{
    programCarSpeed_motor2 = ui->verticalSlider_2->value();
     ui->lcdNumber_2->display((programCarSpeed_motor2-50)*2);
}




