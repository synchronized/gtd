#include <QApplication>

#include "dialogfind.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    DialogFind *dialog = new DialogFind;
    dialog->show();
    return app.exec();
}
