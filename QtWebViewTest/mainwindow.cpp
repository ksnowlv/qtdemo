#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "myobject.h"
#include <QFile>
#include <QDir>
#include <QTextStream>

#include <QWebEngineView>
#include <QWebChannel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 加载图片并设置为按钮的图标
    // QPixmap pixmap(":/images/main.png");
    QPixmap pixmap(":/images/overview.jpg");
    ui->label->setPixmap(pixmap);

    webEngineView = new QWebEngineView(this);
    webEngineView->setGeometry(QRect(10, 20, 300, 250));

    // 创建一个QWebChannel对象，并将其绑定到QWebEngineView页面
    webChannel = std::make_unique<QWebChannel>();
    //创建要暴露给JavaScript的C++对象，并将其注册到QWebChannel对象中
    myObject =  std::make_unique<MyObject>();
    webChannel->registerObject(QStringLiteral("myObject"), myObject.get());
    webEngineView->page()->setWebChannel(webChannel.get());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleNativeCallWebPushButtonClicked()
{
    qDebug()<<"handlNativeCallWebPushButtonClicked";
    //注意路径，不然找不到对应资源文件
    QString htmlPath =  ":/resource/index.html";

    QFile file(htmlPath);
    if (file.exists()) {
        qDebug() << htmlPath<<",this file exists";
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Failed to open file";
            return;
        }

        // 创建文本流，并设置编码为UTF-8
        QTextStream in(&file);
        in.setLocale(QLocale(QLocale::C)); // 设置为"C"语言环境来确保编码为UTF-8

        // 读取并输出文件内容
        QString fileContent = in.readAll();
        qDebug() << fileContent;
        qDebug() << "-----------------------";
        // 关闭文件
        file.close();

        const QUrl& url = QUrl("qrc" + htmlPath);// QUrl::fromLocalFile(htmlPath);
        webEngineView->load(url);
        webEngineView->resize(300, 250);
        webEngineView->show();
    } else {
        qDebug() << "File does not exist";
    }
}


void MainWindow::handleWebCallNativePushButtonClicked()
{
    qDebug()<<"handleWebCallNativePushButtonClicked";
}

