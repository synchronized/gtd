#include "hello.h"

#include <QPushButton>
#include <QMessageBox>

#include <iostream>

hello::hello(QWidget *parent)
    : QWidget(parent){

    //创建一个PushButton
    QPushButton * btn = new QPushButton("点击我^-^",this);
    //连接信号和槽
    connect(btn,SIGNAL(clicked()),this,SLOT(btn_click()));

}

hello::~hello() {
    std::cout << "hello::!hello()" <<std::endl;
}

void hello::btn_click()
{
    QMessageBox::information(NULL, "单击了button",
                             "hello world", QMessageBox::Yes);
}
