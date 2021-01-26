#include <QApplication>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "mainwindow.h"
#include "hello.h"

int main(int argc, char *argv[]) {
    // QApplication a(argc, argv);
    // hello w;
    // w.show();

    // return a.exec();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QGraphicsScene scene;
    scene.addRect(0, 0, 150, 150);
    scene.setBackgroundBrush(QBrush(Qt::gray));

    QGraphicsView view(&scene);
    view.rotate(30);
    view.setWindowTitle("Graphics View");
    view.resize(200, 200);
    view.show();
    return a.exec();
}
