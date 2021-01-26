#include "mainwindow.h"

#include <QMenu>
#include <QMenuBar>
#include <QAction>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //openAction = new QAction(tr("Open"),this);  //初始化动作
    //fileMenu = new QMenu;  //创建一个菜单
    //fileMenu = menuBar()->addMenu(tr("File"));  //将菜单添加到菜单栏上
    //fileMenu->addAction(openAction);  //将动作添加到菜单上
}

MainWindow::~MainWindow()
{

}
