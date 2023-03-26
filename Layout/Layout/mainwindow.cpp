#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <qpushbutton.h>
#include <qlabel.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <qcheckbox.h>
#include <qlistwidget.h>
#include <iostream>
#include <qformlayout.h>
#include <qstackedlayout.h>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    QVBoxLayout* vBoxLayout = new QVBoxLayout();

    QHBoxLayout* hBoxLayout = new QHBoxLayout();

    for (int i = 0; i < 5; ++i) {
        QString buttonName = "Button " + QString::number(i + 1);
        QPushButton* button = new QPushButton(buttonName);
        hBoxLayout->addWidget(button);
        button->setFixedSize(80, 40);
    }

    vBoxLayout->addLayout(hBoxLayout);

    QVBoxLayout* labelsVBoxLayout = new QVBoxLayout();

    for (int i = 0; i < 6; ++i) {
        QString labelName = "Label " + QString::number(i + 1);
        QLabel* label = new QLabel();
        label->setText(labelName);
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet("background-color:#00ff00;");
        labelsVBoxLayout->addWidget(label,Qt::AlignCenter);
    }
    labelsVBoxLayout->setSpacing(10);

    vBoxLayout->addLayout(labelsVBoxLayout);

    QHBoxLayout* okCancelHBoxLayout = new QHBoxLayout();
//    okCancelHBoxLayout->addStretch();
    QPushButton* okButton = new QPushButton();
    okButton->setText(tr("同意"));
    okButton->setFixedSize(200, 40);
    QPushButton* cancelButton = new QPushButton();
    cancelButton->setText(tr("取消"));
    cancelButton->setFixedSize(200, 40);
    okCancelHBoxLayout->addWidget(okButton);
    okCancelHBoxLayout->addWidget(cancelButton);

    connect(okButton, &QPushButton::clicked,[&]() {
       on_ButtonClick();
    });


    vBoxLayout->addLayout(okCancelHBoxLayout);

    QHBoxLayout* bottomLabelsHBoxLayout = new QHBoxLayout();
    QLabel* labels[4];
    for (int i = 0; i < 4; ++i) {
        QString labelName = "Label " + QString::number(i + 1);
        QLabel* label = new QLabel();
        label->setText(labelName);
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet("background-color:#ff0000;");
        labels[i] = label;
        labels[i]->setMinimumHeight(50);
        bottomLabelsHBoxLayout->addWidget(label);
    }

    for (int i = 0; i < 4; ++i) {
        bottomLabelsHBoxLayout->setStretchFactor(labels[i],i + 1);
    }

    vBoxLayout->addLayout(bottomLabelsHBoxLayout);

    //grid layout
    QGridLayout* gridLayout = new QGridLayout();

    QLabel* logoLabel = new QLabel();
    logoLabel->setFixedSize(100,100);

    QImage image(tr(":/image/logo/1.png"));

    QImage resImage=image.scaled(logoLabel->size(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);//重新调整图像大小以适应窗口
    logoLabel->setPixmap(QPixmap::fromImage(resImage));

//    logoLabel->setPixmap(QPixmap::fromImage(image).scaled(logoLabel->width(),
//                                                                            logoLabel->height(),
//                                                                            Qt::KeepAspectRatio,
//                                                                            Qt::SmoothTransformation));

    QLineEdit* userEdit = new QLineEdit();
    userEdit->setPlaceholderText(tr("请输入手机号"));
    userEdit->setMinimumWidth(300);

    QLineEdit* passwordEdit = new QLineEdit();
    passwordEdit->setPlaceholderText(tr("请输入密码"));
    passwordEdit->setMinimumWidth(300);

    QCheckBox* rememberPasswordCheckBox = new QCheckBox();
    rememberPasswordCheckBox->setText(tr("记住密码"));
    QCheckBox* autoLoginCheckBox = new QCheckBox();
    autoLoginCheckBox->setText(tr("自动登陆"));

    QPushButton* loginButton = new QPushButton();
    loginButton->setText(tr("登陆"));
    loginButton->setMinimumWidth(300);

    gridLayout->addWidget(logoLabel,0,0,3,1);
    gridLayout->addWidget(userEdit, 0, 1, 1, 3, Qt::AlignLeft|Qt::AlignCenter);
    gridLayout->addWidget(passwordEdit, 1, 1, 1, 3, Qt::AlignLeft|Qt::AlignCenter);
    gridLayout->addWidget(rememberPasswordCheckBox, 2, 1, 1, 1, Qt::AlignLeft|Qt::AlignCenter);
    gridLayout->addWidget(autoLoginCheckBox, 2, 2, 1, 1);
    gridLayout->addWidget(loginButton,3, 1, 1, 3, Qt::AlignLeft|Qt::AlignCenter);

    vBoxLayout->addLayout(gridLayout);


    //QFormLayout
    QFormLayout* formLayout = new QFormLayout();
    formLayout->setRowWrapPolicy(QFormLayout::DontWrapRows);
    formLayout->setAlignment(Qt::AlignLeft);
    formLayout->setHorizontalSpacing(10);
    formLayout->setVerticalSpacing(5);

    QVector<QString> nameVector{"姓名:","年龄:","手机号码:", "邮箱:", "地址"};

    for(int i = 0; i < nameVector.count(); ++i) {
        QLineEdit* edit = new QLineEdit();
        edit->setMinimumWidth(300);
        edit->setMinimumHeight(30);
        formLayout->addRow(nameVector[i], edit);
    }

    vBoxLayout->addLayout(formLayout);

    //QStackedLayout
    QHBoxLayout* myStackHBoxLayout = new QHBoxLayout();

    QListWidget* listWidget = new QListWidget();
    QStackedLayout* stackedLayout = new QStackedLayout();

    QVector<QString> cityVector{"北京","上海","天津","重庆","深圳","厦门"};

    foreach (const QString item, cityVector) {
        listWidget->addItem(item);
        QWidget* containerWidget = new QWidget();
        containerWidget->setMinimumSize(200,100);
        containerWidget->setStyleSheet("background-color:#ffff00;");

        QVBoxLayout *vBoxLayout = new QVBoxLayout();
        containerWidget->setLayout(vBoxLayout);

        QLabel* label = new QLabel();
        label->setText(item);
        label->setMinimumSize(80,40);
        vBoxLayout->addWidget(label);

        QPushButton* button = new QPushButton();
        button->setText(item);
        button->setMinimumSize(60,40);
        button->setStyleSheet("background-color:#ff00ff;");
        vBoxLayout->addWidget(button);

        stackedLayout->addWidget(containerWidget);
    }

    myStackHBoxLayout->addWidget(listWidget,1);
    myStackHBoxLayout->addLayout(stackedLayout,4);

    vBoxLayout->addLayout(myStackHBoxLayout);

    QObject::connect(listWidget, &QListWidget::currentRowChanged, stackedLayout, &QStackedLayout::setCurrentIndex);

    ui->centralwidget->setLayout(vBoxLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ButtonClick() {
    cout<<"button click"<<endl;
}


