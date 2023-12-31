#ifndef CURLTEST_H
#define CURLTEST_H

#include <QObject>
#include <string>
using namespace std;

class CurlTest : public QObject
{
    Q_OBJECT
public:
    explicit CurlTest(QObject *parent = nullptr);

public:
    void testCurlhttpGet();
    void handleCurlGetJsonParse(std::string& jsonData);
    void testCurlHttpPost();
    void handleCurlPostJsonParse(const std::string& json);

signals:
};

#endif // CURLTEST_H
