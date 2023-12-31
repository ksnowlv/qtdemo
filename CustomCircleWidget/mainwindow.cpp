#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QtWidgets/qpushbutton.h"
#include "circlebutton.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    CircleButton *circleButton = new CircleButton(this);
    circleButton->move(QPoint(50,50));
    connect(circleButton, &CircleButton::clicked, []() {
        qDebug()<<"circle button clicked!!!";
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
