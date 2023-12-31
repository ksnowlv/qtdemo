#include "circlebutton.h"
#include <qpainter>
#include <QMouseEvent>

CircleButton::CircleButton(QWidget *parent)
    : QWidget{parent}
{
    setMinimumSize(80, 80);
}


QSize CircleButton::sizeHint() const {
    return QSize(80, 80);
}

void CircleButton::mousePressEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        emit clicked();
    }
}

void CircleButton::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QPen pen(Qt::black, 2);
    painter.setPen(pen);
    painter.setBrush(Qt::blue);
    painter.drawEllipse(0, 0, width(), height());
}




