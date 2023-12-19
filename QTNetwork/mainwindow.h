#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void handleGetRequestEvent();
    void handlePostRequestEvent();

    void handleCurlGetRequestEvent();
    void handleCurPostRequestEvent();


private:
    void httpGetRequest();
    void handleResponse(QNetworkReply *reply);
    void httpPostRequest();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
