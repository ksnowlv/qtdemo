#ifndef PERSON_H
#define PERSON_H

#include <QObject>

class Person : public QObject
{
    Q_OBJECT
public:
    explicit Person(QObject *parent = nullptr);
    ~ Person();

public:
    const char* getName() const;
    const int getAge() const;
    const char* getAddress() const;

    void setName(const char* name);
    void setAge(const int age);
    void setAddress(const char* address);

    void showPersonMessage();

public:
    void clear();


signals:

private:
    char *m_pName;
    int m_age;
    char *m_pAddress;

};

#endif // PERSON_H
