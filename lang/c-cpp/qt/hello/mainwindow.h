#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QAction;
class QMenu;

class MainWindow : public QMainWindow
{
    Q_OBJECT
protected:
    QAction *openAction;  //定义一个动作
    QMenu *fileMenu;  //定义一个菜单

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
