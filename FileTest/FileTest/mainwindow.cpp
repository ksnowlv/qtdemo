#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <qfiledialog.h>
#include <iostream>
#include <qfileinfo.h>
#include <QDateTime>
#include <thread>
#include <future>

using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleSelectedFile() {


    selectedFilePath = QFileDialog::getOpenFileName(this,"打开文件","/Users/lvwei/Documents");
    cout<<"you selected"<<selectedFilePath.toStdString()<<endl;

    future<QByteArray> result = async(launch::async, [&]() {
        QFile  file(selectedFilePath);
        file.open(QIODevice::ReadOnly);
        QByteArray fileByteArray = file.readAll();
        cout<<"file size:"<<QString::number(fileByteArray.size()).toStdString()<<endl;
        file.close();
        return fileByteArray;
    });

    QByteArray fileByteArray = result.get();      //get()会阻塞等待异步任务完成
    cout<<fileByteArray.size()<<endl;

}

