#include "serialwaiterdialog.h"
#include <QtSerialPort/QSerialPortInfo>
#include <QLabel>

QString SerialWaiterDialog::get_selection(){
    if(selected)
        return this->user_selection;
    else return QString::null;
}

void SerialWaiterDialog::selectPort(int index){
    this->user_selection = port_list->currentData().toString();
    selected = true;
    confirm_button->setEnabled(true);
}

void SerialWaiterDialog::refreshPortList(){
    selected = false;
    confirm_button->setEnabled(false);

    port_list->clear();
    for(QSerialPortInfo& info : QSerialPortInfo::availablePorts()){
        port_list->addItem(info.portName()+" "+info.description(),info.portName());
    }

    if(port_list->count() == 1){
        port_list->setCurrentIndex(0);
        selectPort(0);
    }
}


SerialWaiterDialog::SerialWaiterDialog(QWidget* parent)
    : QDialog(parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint), selected(false),logo(":/images/logo.jpg")
{
    setWindowTitle("Select Arduino port");

    buttonLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);

    port_list = new QComboBox(this);

    QLabel* image_holder = new QLabel(this);
    image_holder->setPixmap(logo);

    refresh_button = new QPushButton("Refresh port list");
    confirm_button = new QPushButton("Confirm");
    confirm_button->setEnabled(false);

    buttonLayout->addWidget(port_list);
    buttonLayout->addWidget(refresh_button);
    buttonLayout->addWidget(confirm_button);
    buttonLayout->addWidget(image_holder);


    layout()->setSizeConstraint(QLayout::SetFixedSize);

    connect(refresh_button,&QPushButton::clicked,this, &SerialWaiterDialog::refreshPortList);
    connect(port_list,static_cast<void (QComboBox::*)(int n)>(&QComboBox::activated),
            this,&SerialWaiterDialog::selectPort);
    connect(confirm_button,&QPushButton::clicked,this,[=](){this->accept();});

    refreshPortList();
}
