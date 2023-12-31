#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "customclass.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 在窗口类中连接信号和槽
    customClass = new CustomClass(this);
    connect(customClass, &CustomClass::showMessage, [](const QString &message) {
        qDebug() << "Received message:" << message;
    });

    connect(customClass, &CustomClass::showMessage, [](const QString &message) {
        qDebug() << "Received message:" << message;
    });


    // 触发信号
    customClass->handleSendMessage();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if (customClass) {
        customClass->handleSendMessage();
    }
}

