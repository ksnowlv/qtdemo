#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>

#include <qlistwidget.h>
//#include <qtreewidget.h>
#include <QStackedWidget.h>
//#include <qtablewidget.h>
//#include <qgroupbox.h>
#include <qlabel.h>
#include <QHBoxLayout>
#include <qpushbutton.h>
#include <qwidget.h>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , listContainerWidget(nullptr)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::button_stackedwidget_clicked() {
    cout<<"button_stackedwidget_clicked"<<endl;

}

void MainWindow::button_listwidget_clicked() {
    cout<<"button_listwidget_clicked"<<endl;
    showListWidget();
}

void MainWindow::button_treewidget_clicked() {
     cout<<"button_treewidget_clicked"<<endl;
}

void MainWindow::button_tablewidget_clicked() {
     cout<<"button_tablewidget_clicked"<<endl;
}

void MainWindow::button_groupbox_clicked() {
     cout<<"button_groupbox_clicked"<<endl;
}

void MainWindow::initListWidget() {

    QHBoxLayout* hBoxlayout = new QHBoxLayout();

    listContainerWidget = new QWidget();
    listContainerWidget->setLayout(hBoxlayout);
    listContainerWidget->setGeometry(this->geometry());

    QListWidget* listWidget = new QListWidget();
    QStackedWidget* stackedWidget = new QStackedWidget();
    QVector<QString> stringVector{"窗口选项1","窗口选项2", "窗口选项3", "窗口选项4","窗口选项5"};
    QVector<QString> vector{"窗口1","窗口2", "窗口3", "窗口4","窗口5"};

    for (int i = 0; i < stringVector.count(); ++i) {
        listWidget->addItem(stringVector[i]);

        QWidget* subWidget = new QWidget();
        QVBoxLayout* subWidgetMainLayout = new QVBoxLayout();
        subWidget->setLayout(subWidgetMainLayout);

        QHBoxLayout* hBoxLayout = new QHBoxLayout();
        QPushButton* button = new QPushButton();
        button->setText("退出");
        connect(button, &QPushButton::clicked, this,[&]() {
            listContainerWidget->hide();
            this->show();
        });
        hBoxLayout->addWidget(button,1,Qt::AlignRight);
        subWidgetMainLayout->addLayout(hBoxLayout);

        QLabel* label = new QLabel(vector[i]);
        label->setStyleSheet("background-color:#ff00ff;");
        label->setText(vector[i]);
        subWidgetMainLayout->addWidget(label,1, Qt::AlignTop);

        stackedWidget->addWidget(subWidget);
    }

    //设置主窗口布局
    hBoxlayout->addWidget(listWidget);
    hBoxlayout->addWidget(stackedWidget);
    hBoxlayout->setStretchFactor(listWidget,1);
    hBoxlayout->setStretchFactor(stackedWidget, 5);

    connect(listWidget,
            &QListWidget::currentRowChanged,
            stackedWidget,
            &QStackedWidget::setCurrentIndex);
}

void MainWindow::showListWidget() {
    if(nullptr == listContainerWidget) {
        initListWidget();
    }

    listContainerWidget->show();
    this->hide();
}


