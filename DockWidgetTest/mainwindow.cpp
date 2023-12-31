#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDockWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 创建停靠部件
    dockWidget = new QDockWidget("停靠部件", this);

    // 创建部件内容
    QWidget *widget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(widget);
    QLabel *label = new QLabel("这是一个停靠部件");
    layout->addWidget(label);
    widget->setLayout(layout);

    // 将部件设置为停靠部件的内容
    dockWidget->setWidget(widget);

    // 将停靠部件添加到主窗口
    addDockWidget(Qt::LeftDockWidgetArea, dockWidget);

    QLineEdit *edit = new QLineEdit(this);
    setCentralWidget(edit);

}

MainWindow::~MainWindow()
{
    delete ui;
}
