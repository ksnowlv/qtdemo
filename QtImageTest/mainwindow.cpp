#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMovie>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QPixmap pngImage(":/images/test@2x.png");
    ui->pngLabel->setPixmap(pngImage);
    ui->pngLabel->setScaledContents(true);
    ui->pngLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);  // 设置大小策略为扩展


    QPixmap jpgImage(":/images/test.jpg");
    ui->jpgLabel->setPixmap(jpgImage);
    ui->jpgLabel->setScaledContents(true);
    ui->jpgLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);  // 设置大小策略为扩展


    QPixmap webpImage(":/images/test.webp");
    ui->webpLabel->setPixmap(webpImage);
    ui->webpLabel->setScaledContents(true);
    ui->webpLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);  // 设置大小策略为扩展

    movie = new QMovie(this);
    movie->setFileName(":/images/test.gif");
    ui->gifLabel->setMovie(movie);
    movie->start();
    ui->gifLabel->setScaledContents(true);
    ui->gifLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);  // 设置大小策略为扩展
}

MainWindow::~MainWindow()
{
    delete ui;
}
