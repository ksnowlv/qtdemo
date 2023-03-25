#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <string>
#include <iostream>
#include <memory>
#include <QLabel>
#include "loginwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    m_GridLayout = new QGridLayout();
//    ui->centralwidget->setLayout(m_GridLayout);


//    QLabel *label = new QLabel();
//    label->setText("测试验证111111111");
//    m_GridLayout->addWidget(label);

    ui->mInfoLabel->setText("你要去哪里呀!");
    ui->mShowPushButton->setText("---测试验证按钮!!!");
    connect(ui->mShowPushButton, SIGNAL(clicked()), this, SLOT(on_HelloQTClick()));


//    unique_ptr<Person> p(new Person());
//    p->setName("ksnowlv");
//    p->setAge(10);
//    p->setAddress("北京海淀区唐家岭新城");
//    p->showPersonMessage();

}

MainWindow::~MainWindow()
{

}

void MainWindow::on_HelloQTClick() {
    //ui->mInfoLabel->setText("测试按钮被点击了！！！");
    cout<<"---on_HelloQTClick"<<endl;
    loginWindow = make_unique<LoginWindow>();
    loginWindow->show();
}

