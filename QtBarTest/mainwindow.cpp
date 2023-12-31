#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QToolBar>
#include <QFileDialog>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setMinimumSize(800, 600);

    // 创建菜单栏
    // QMenuBar *menuBar = new QMenuBar(this);

     QMenuBar *menuBar = ui->menubar;

    QMenu *fileMenu1 = menuBar->addMenu(tr("file"));
    // 创建文件菜单
    QMenu *fileMenu = menuBar->addMenu("文件");
    QAction *openAction = fileMenu->addAction("打开");
    QAction *saveAction = fileMenu->addAction("保存");
    QAction *saveAllAction = fileMenu->addAction("全部保存");

    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveFile);
    connect(saveAllAction, &QAction::triggered, this, &MainWindow::saveAllFile);

    // 创建编辑菜单
    QMenu *editMenu = menuBar->addMenu("编辑");
    QAction *cutAction = editMenu->addAction("剪切");
    QAction *copyAction = editMenu->addAction("复制");
    QAction *pasteAction = editMenu->addAction("粘贴");

    // 创建关于菜单
    QMenu *aboutMenu = menuBar->addMenu("关于");
    QAction *versionAction = aboutMenu->addAction("版本");
    QAction *aboutAction = aboutMenu->addAction("关于");

    // 添加版本子菜单
    QMenu *versionSubMenu = new QMenu("菜单2.0", this);
    versionAction->setMenu(versionSubMenu);

    // 添加子菜单项
    QAction *subAction1 = versionSubMenu->addAction("当前版本为1.0");
    QAction *subAction2 = versionSubMenu->addAction("版本历史");



    // 创建工具栏
    QToolBar *toolBar = new QToolBar(this);
    addToolBar(toolBar);

    // 添加工具栏按钮
    toolBar->addAction(openAction);
    toolBar->addAction(saveAction);
    toolBar->addAction(saveAllAction);
    toolBar->addAction(cutAction);
    toolBar->addAction(copyAction);
    toolBar->addAction(pasteAction);

    // 创建状态栏
    QStatusBar *statusBar = ui->statusbar;
    statusBar->showMessage("Ready");


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "打开文件", QDir::homePath(), "所有文件 (*.*)");

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly)) {
            // 在这里可以读取文件内容并进行处理
            QTextStream in(&file);
            QString fileContent = in.readAll();
            file.close();

            // 处理文件内容
            // ...
            qDebug()<<fileContent;
        }
        else {
            qDebug() << "无法打开文件：" << file.errorString();
        }
    }
}

void MainWindow::saveFile() {
    qDebug()<<"saveFile";
}

void MainWindow::saveAllFile() {
    qDebug()<<"saveAllFile";
}

