#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

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
    Ui::Widget *ui;
    bool carState;
    bool electromagnetState;
public slots:
    void carStatus();
public slots:
    void electromagnetStatus();
public slots:
    void exit();
};

#endif // WIDGET_H
