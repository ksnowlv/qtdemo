#include "mainwindow.h"

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // MainWindow w;
    // w.show();

    // 创建一个场景
    QGraphicsScene scene;

    // 在场景中添加一个圆形图形项
    QGraphicsEllipseItem *ellipseItem = scene.addEllipse(50, 50, 100, 100);

    // 允许图形项接受鼠标事件
    ellipseItem->setFlag(QGraphicsItem::ItemIsMovable, true);

    // 创建一个视图并将场景设置到视图中
    QGraphicsView view(&scene);
    view.setSceneRect(QRect(0, 0, 500, 200));

    view.show();

    return a.exec();
}
