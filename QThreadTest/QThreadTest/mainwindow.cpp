#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "threadcontrolobject.h"
#include <iostream>
#include <QSemaphore>
#include "consumerthread.h"
#include "producterthread.h"


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


    if(producterThread) {
        producterThread->exit();
    }

    if(consumerThread) {
        consumerThread->exit();
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

void MainWindow::handleConsumerProductor() {


    if(producterThread) {
        producterThread->exit();
    }

    if(consumerThread) {
        consumerThread->exit();
    }



    shared_ptr<QSemaphore> producterSemaphore = make_shared<QSemaphore>(1);
    shared_ptr<QSemaphore> consumerSemaphore = make_shared<QSemaphore>(0);

    producterThread = make_unique<ProducterThread>();
    consumerThread = make_unique<ConsumerThread>();
    producterThread->setSemaphore(producterSemaphore, consumerSemaphore);
    consumerThread->setSemaphore(producterSemaphore, consumerSemaphore);

    connect(producterThread.get(), &QThread::finished, producterThread.get(), &QThread::deleteLater);

    producterThread->start();
    consumerThread->start();
}

