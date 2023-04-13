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

    const QString documentPath = "/Users/lvwei/Documents";

    selectedFilePath = QFileDialog::getOpenFileName(this,"打开文件", documentPath);
    cout<<"you selected"<<selectedFilePath.toStdString()<<endl;

    //c++异步读取
    future<QByteArray> result = async(launch::async, [&]() {
        cout<<"threadid:"<<this_thread::get_id()<<endl;
        QFile  file(selectedFilePath);
        file.open(QIODevice::ReadOnly);
        QByteArray fileByteArray = file.readAll();
        cout<<"file size:"<<QString::number(fileByteArray.size()).toStdString()<<endl;
        file.close();
        return fileByteArray;
    });

    cout<<"main threadid:"<<this_thread::get_id()<<endl;
    QByteArray fileByteArray = result.get();
    cout<<fileByteArray.size()<<endl;
}

void MainWindow::handleViewFileInfo() {

    QFile file(selectedFilePath);
    QFileInfo  info(file);

    QString resInfo = "绝对路径:" + info.absoluteFilePath()
            + ",文件名:" + info.fileName()
            + ",后缀名:" + info.suffix()
            + ",创建时间" + info.birthTime().toString()
            + ",修改时间" + info.lastModified().toString()
            + ",文件大小:" + QString::number(info.size());
    cout<<"fileInfo:"<<resInfo.toStdString()<<endl;
}

void MainWindow::handleStreamWriteFile() {

    const QString fileFullPath = "/Users/lvwei/Documents/1.txt";

    QFile file(fileFullPath);
    file.open(QIODevice::WriteOnly);

    QDataStream  dataStream(&file);
    dataStream<<QString("abcdefj")<<(qint32)100<<QString("ksnowlv");
    file.close();

    file.open(QIODevice::ReadOnly);
    QDataStream  outDataStream(&file);

    QString str1;
    qint32 num = -1;
    QString str2;

    outDataStream>>str1>>num>>str2;
    QString outRes = "str1:" + str1 + ",num:" + QString::number(num) + ",str2:" + str2;

    cout<<outRes.toStdString()<<endl;
    file.close();
}

void MainWindow::handleTextWriteFile() {

    const QString fileFullPath = "/Users/lvwei/Documents/2.txt";

    QFile file(fileFullPath);
    bool open = file.open(QIODevice::WriteOnly | QIODevice::Text);
    if(!open) {
        cout<<fileFullPath.toStdString()<<"can not openned!!!"<<endl;
        file.close();
    }

    QTextStream  textStream(&file);
    textStream<<QString("abcdefj")<<(qint32)100<<QString("ksnowlv");
    file.close();

    open = file.open(QIODevice::ReadOnly | QIODevice::Text);
    if(!open) {
        cout<<fileFullPath.toStdString()<<"can not openned!!!"<<endl;
        file.close();
    }

    QTextStream  outTextStream(&file);

    QString str1;
    qint32 num = -1;
    QString str2;

    outTextStream>>str1>>num>>str2;
    QString outRes = "str1:" + str1 + ",num:" + QString::number(num) + ",str2:" + str2;

    cout<<outRes.toStdString()<<endl;
    file.close();

    open = file.open(QIODevice::Append | QIODevice::Text);
    if(!open) {
        cout<<fileFullPath.toStdString()<<"can not openned!!!"<<endl;
        file.close();
    }

    QTextStream  appendTextStream(&file);
    appendTextStream<<"您好，我是新追回的数据!";
    file.close();
}

