#ifndef _PAINTED_WIDGET_H
#define _PAINTED_WIDGET_H

#include <QPaintEvent>
#include <QWidget>

class PaintedWidget : public QWidget {
   public:
    PaintedWidget();

   protected:
    void paintEvent1(QPaintEvent *event);
    void paintEvent2(QPaintEvent *event);
    void paintEvent3(QPaintEvent *event);
    void paintEvent4(QPaintEvent *event);
    void paintEvent5(QPaintEvent *event);
    void paintEvent6(QPaintEvent *event);
    void paintEvent7(QPaintEvent *event);
    void paintEvent8(QPaintEvent *event);
    void paintEvent(QPaintEvent *event);
};

#endif  //_PAINTED_WIDGET_H
