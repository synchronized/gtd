#include <QApplication>
#include "painted.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    PaintedWidget painted;
    painted.show();
    return app.exec();
}
