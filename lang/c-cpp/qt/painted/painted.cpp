#include "painted.h"
#include <QPainter>
#include <QPixmap>
#include <QBitmap>
#include <QPicture>
#include <QPen>

PaintedWidget::PaintedWidget() {
    // resize(800, 600);
    // setWindowTitle(tr("painted"));
}

void PaintedWidget::paintEvent2(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawLine(80, 100, 650, 500);
    painter.setPen(Qt::red);
    painter.drawRect(10, 10, 100, 400);
    painter.setPen(QPen(Qt::green, 5));
    painter.setBrush(Qt::blue);
    painter.drawEllipse(50, 150, 400, 200);
}

void PaintedWidget::paintEvent1(QPaintEvent *event) {
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 5, Qt::DashDotLine, Qt::RoundCap));
    painter.setBrush(Qt::yellow);
    painter.drawEllipse(50, 150, 200, 150);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::black, 5, Qt::DashDotLine, Qt::RoundCap));
    painter.setBrush(Qt::blue);
    painter.drawEllipse(300, 150, 200, 150);
}

void PaintedWidget::paintEvent3(QPaintEvent *event) {
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);
    QLinearGradient linearGradient(60, 50, 200, 50);
    linearGradient.setColorAt(0.2, Qt::white);
    linearGradient.setColorAt(0.6, Qt::green);
    linearGradient.setColorAt(1.0, Qt::black);
    painter.setBrush(QBrush(linearGradient));
    painter.drawEllipse(50, 50, 200, 150);

    painter.setPen(Qt::red);
    painter.drawPoint(60, 50);
    painter.drawPoint(200, 200);
    painter.setPen(Qt::blue);
    painter.drawPoint(50, 50);
    painter.drawPoint(250, 200);
}

void PaintedWidget::paintEvent4(QPaintEvent *event) {
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);
    QLinearGradient linearGradient(60, 50, 200, 200);
    linearGradient.setColorAt(0.2, Qt::white);
    linearGradient.setColorAt(0.6, Qt::green);
    linearGradient.setColorAt(1.0, Qt::black);
    painter.setPen(QPen(QBrush(linearGradient), 5));
    painter.drawLine(50, 50, 200, 200);

    painter.drawEllipse(50, 50, 200, 150);
}

void PaintedWidget::paintEvent5(QPaintEvent *event) {
    QPainter painter(this);
    QPen pen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap);
    painter.setPen(pen);

    painter.setBrush(Qt::blue);
    painter.setWindow(-50, -50, 100, 100);
    painter.drawRect(-50, -50, 100, 100);
}

void PaintedWidget::paintEvent6(QPaintEvent *event) {
    QPainter painter(this);

    QFont font("Courier", 24);
    painter.setFont(font);
    painter.drawText(50, 50, "Hello, world!");
    QTransform transform;
    transform.rotate(+45.0);
    painter.setWorldTransform(transform);
    painter.drawText(60, 60, "Hello, world!");
}

void PaintedWidget::paintEvent7(QPaintEvent *event) {
  QPainter painter(this);

  QPixmap pixmap("1.png");
  QBitmap bitmap("1.png");
  painter.drawPixmap(10, 10, 255, 255, pixmap);
  painter.drawPixmap(270, 10, 255, 255, bitmap);
}

void PaintedWidget::paintEvent8(QPaintEvent *event) {
  QPainter painter;

  QPicture picture;
  painter.begin(&picture);
  painter.drawEllipse(10, 20, 80, 70);
  painter.end();
  picture.save("drawing.pic");

}

void PaintedWidget::paintEvent(QPaintEvent *event) {
  QPainter painter(this);

  QPicture picture;
  picture.load("drawing.pic");
  painter.begin(&picture);
  painter.drawPicture(0, 0, picture);
  painter.end();
}
