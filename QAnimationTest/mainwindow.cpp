#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QLayout>



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

void MainWindow::handlePropertyAnimationEvent() {

    // 创建一个属性动画，对按钮的位置进行动画化处理

    // 创建一个按钮并添加到MainWindow
    QPushButton *button = new QPushButton("你看看，我是动态按钮", this);
    button->setStyleSheet("QPushButton {  background-color: yellow; }");
    button->setGeometry(50, 220, 200, 30);
    button->show();

    qDebug()<<"button parent:"<<button->parent();

    // 获取所有的子控件
    const QList<QWidget *> children = ui->centralwidget->findChildren<QWidget *>();

    // 遍历所有子控件，并显示它们的对象名称
    for (QWidget *child : children) {
        qDebug() << "Object name: " << child->objectName();
    }

    QPropertyAnimation *animation = new QPropertyAnimation(button, "geometry");
    animation->setDuration(1000); // 动画时长（以毫秒为单位）
    animation->setStartValue(QRect(50, 220, 200, 30)); // 动画起始位置和大小
    animation->setEndValue(QRect(50, 350, 200, 30)); // 动画结束位置和大小
    animation->setEasingCurve(QEasingCurve::InOutQuad); // 缓动曲线

    QObject::connect(animation, &QPropertyAnimation::finished, this, [=]() {
        qDebug() << "Animation finished!";
        // 在这里添加您希望执行的后续处理代码，例如：
        button->move(50, 220);
    });

    animation->start();
}

void MainWindow::handleParallelAnimationGroupEvent() {

    QPushButton* button = ui->testpushButton;
    // 创建两个属性动画，对按钮的位置和透明度进行动画化处理
    QPropertyAnimation *posAnimation = new QPropertyAnimation(button, "geometry");
    posAnimation->setDuration(1000);
    posAnimation->setStartValue(QRect(50, 50, 100, 30));
    posAnimation->setEndValue(QRect(100, 100, 100, 30));

    QPropertyAnimation *opacityAnimation = new QPropertyAnimation(button, "windowOpacity");
    opacityAnimation->setDuration(1000);
    opacityAnimation->setStartValue(1.0);
    opacityAnimation->setEndValue(0.0);


    // 创建一个并行动画组，同时播放按钮的位置和透明度动画
    QParallelAnimationGroup *group = new QParallelAnimationGroup(this);
    group->addAnimation(posAnimation);
    group->addAnimation(opacityAnimation);

    QObject::connect(group, &QParallelAnimationGroup::finished, this, [=]() {
        qDebug()<<"QParallelAnimationGroup finish!!!";
        button->move(50, 50);
        button->setStyleSheet("QPushButton { background-color: rgba(0, 255, 255, 100);font-size: 10px;   background-color: yellow; }");
    });

    group->start();

}

void MainWindow::handleSequentialAnimationGroupEvent() {
    // 创建两个按钮
    QPushButton *button1 = ui->testpushButton;
    QPushButton *button2 = ui->testpushButton_2;

    // 创建两个属性动画
    QPropertyAnimation *animation1 = new QPropertyAnimation(ui->testpushButton, "geometry");
    animation1->setDuration(1000); // 动画时长
    animation1->setStartValue(QRect(50, 50, 150, 30)); // 动画起始位置和大小
    animation1->setEndValue(QRect(250, 50, 150, 30)); // 动画结束位置和大小

    QPropertyAnimation *animation2 = new QPropertyAnimation(ui->testpushButton_2, "geometry");
    animation2->setDuration(1000); // 动画时长
    animation2->setStartValue(QRect(50, 100, 150, 30)); // 动画起始位置和大小
    animation2->setEndValue(QRect(250, 100, 150, 30)); // 动画结束位置和大小

    // 创建一个顺序动画组，并添加两个动画
    QSequentialAnimationGroup *animationGroup = new QSequentialAnimationGroup();
    animationGroup->addAnimation(animation1);
    animationGroup->addAnimation(animation2);
    QObject::connect(animationGroup, &QSequentialAnimationGroup::finished, this, [=]() {
        qDebug()<<"QSequentialAnimationGroup finish!!!";
        button1->move(50, 50);
        button2->move(50, 100);
    });
    animationGroup->start();
}


