#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QJsonParseError>
#include <QJsonObject>
#include <QTime>
#include <iostream>
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

void MainWindow::handleGetRequestEvent() {
    httpGetRequest();
}

void MainWindow::handlePostRequestEvent() {

    httpPostRequest();
}

void MainWindow::httpGetRequest() {
    //构建一个manager对象
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    //manager具有异步API，当http请求完成后，会通过finished信号进行通知
    connect(manager,&QNetworkAccessManager::finished,this,
            [=](QNetworkReply *reply)
            {
                handleResponse(reply);
            });
    //发送异步get请求
    manager->get(QNetworkRequest(QUrl("https://www.baidu.com")));
}

void MainWindow::handleResponse(QNetworkReply *reply) {

    if(reply->error()!=QNetworkReply::NoError)
    {
        //处理中的错误信息
        cout<<"reply error:"<<reply->errorString().toStdString()<<endl;
        return;
    }


    cout<<"请求方式"<<reply->operation()
         <<",status code:"<<reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt()
         <<",url:"<<reply->url().toString().toStdString()
         <<endl;


    //获取响应信息
    const QByteArray replyData = reply->readAll();
    cout<<"replyData"<<replyData.toStdString()<<endl;

    QJsonObject jsonObject = QJsonDocument::fromJson(replyData).object();
    int code = jsonObject.value("code").toInt();
    QString message = jsonObject.value("msg").toString();
    QString data = jsonObject.value("data").toString();
    QString tid = jsonObject.value("tid").toString();
    bool ok = jsonObject.value("ok").toBool();
    std::cout<<"code:"<< code
              <<",message"<<message.toStdString()
              <<",data:"<<data.toStdString()
              <<",tid:"<<tid.toStdString()<<std::endl;
    reply->deleteLater();
}

static const QString ServerUrl = "https://nl-mp-gateway.taohuayuan-cq.com";

void MainWindow::httpPostRequest() {


    QSslConfiguration config ;

    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::TlsV1_2);

    QNetworkRequest request(QUrl::fromUserInput(QString("%1/user/ums/user/sendSms").arg(ServerUrl)));
    request.setSslConfiguration(config);

    request.setRawHeader("content-type","application/json");
    request.setRawHeader("platform","2");
    request.setRawHeader("content-encoding","gzip, deflate, br");
    request.setRawHeader("User-Agent","QT");


    QJsonDocument doc;
    QJsonObject jsonData({{"mobile","15210795182"},
                          {"userType","1"}});
    doc.setObject(jsonData);


    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkReply* reply = manager->post(request, doc.toJson());

    QEventLoop eventLoop;
    connect(manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
    //    connect(manager,&QNetworkAccessManager::finished,this,
    //            [=](QNetworkReply *reply)
    //            {
    //                handleResponse(reply);
    //            });

    eventLoop.exec();
    handleResponse(reply);
}

