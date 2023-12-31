#include "myobject.h"

MyObject::MyObject(QObject *parent)
    : QObject{parent}
{

}

void MyObject::showMessage(const QString &message) {
    // 在原生代码中处理来自WebView的消息
    qDebug() << "Message from WebView:" << message;
}

void MyObject::callNativeMethod(const QString &message)
{   //JS Call NativeMethod
    qDebug() << "Native method called from JavaScript:" << message;
    emit nativeMethodCalled("Message from native method");
}
