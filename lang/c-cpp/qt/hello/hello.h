#ifndef __HELLO_H_
#define __HELLO_H_

#include <QWidget>

class hello:public QWidget{
    Q_OBJECT
public:
    explicit hello(QWidget *parent = 0);
    ~hello();

public slots:
    //槽函数，处理button单击
    void btn_click();
private:
};


#endif
