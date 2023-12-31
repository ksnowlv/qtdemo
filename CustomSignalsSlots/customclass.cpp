#include "customclass.h"

CustomClass::CustomClass(QObject *parent)
    : QObject{parent}
{

}

void CustomClass::handleSendMessage() {

    // 执行显示信息的操作
    ++count;
    emit showMessage("Something happened!" + QString::number(count));
}
