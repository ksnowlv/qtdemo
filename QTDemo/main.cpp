#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    int *p = new int[1000];

    for (int i = 0; i < 1000; ++i) {
        p[i] = i;
    }

    p[1001] = 1;

    QString* s = new QString();
    s->setNum(1111);

    return a.exec();
}
