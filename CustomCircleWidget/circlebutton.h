#ifndef CIRCLEBUTTON_H
#define CIRCLEBUTTON_H

#include <QWidget>

class CircleButton : public QWidget
{
    Q_OBJECT
public:
    explicit CircleButton(QWidget *parent = nullptr);
    QSize sizeHint() const override;


signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

};

#endif // CIRCLEBUTTON_H
