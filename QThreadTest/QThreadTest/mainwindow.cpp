#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "threadcontrolobject.h"
#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    threadControlObject = make_unique<ThreadControlObject>();
    connect(threadControlObject.get(),
            &ThreadControlObject::workerResult,
            this,
            [&](const QString& message) {
        cout<<"****"<<__func__<<this_thread::get_id()<<endl;
        ui->showInfomationLabel->setText(message);
    });
    cout<<"main thread"<<this_thread::get_id()<<endl;
}

MainWindow::~MainWindow()
{
    delete ui;

    if(threadControlObject) {
        threadControlObject->threadStop();
    }
}

void MainWindow::handleStartThread() {

    threadControlObject->threadStart();
}

void MainWindow::handleStopThread() {
    threadControlObject->threadStop();
}

void MainWindow::handleConcurrent() {
    threadControlObject->concurrentStart();
}

