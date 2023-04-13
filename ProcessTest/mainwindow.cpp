#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "processdemo.h"
#include <QProcess>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("QT Process Test");

    processDemo = make_unique<ProcessDemo>();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleStartProcess() {
    processDemo->start();
}

