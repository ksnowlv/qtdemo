#include "person.h"
#include <stdio.h>
#include <iostream>
using namespace std;

Person::Person(QObject *parent)
    : QObject{parent}
{
    m_pName = nullptr;
    m_pAddress = nullptr;
    m_age = 0;
}

Person::~Person() {
    clear();
}

//get

const char* Person::getName() const {
    return m_pName;
}

const int Person::getAge() const {
    return m_age;
}

const char* Person::getAddress() const {
    return m_pAddress;
}

//set

void Person::setName(const char* name) {

    if(name == nullptr || strcmp(name, "") == 0) {
        if (m_pName != nullptr) {
            delete [] m_pName;
            m_pName = nullptr;
        }
    } else {
        if (m_pName != nullptr) {
            delete [] m_pName;
            m_pName = nullptr;
        }
        const int len = strlen(name);

        if(m_pName != nullptr) {
            delete []m_pName;
        }

        m_pName = new char[len + 1];
        memset(m_pName,0, len + 1);
        strncpy(m_pName, name, len);
    }

}

void Person::setAge(const int age) {
    m_age = age;
}

void Person::setAddress(const char* address) {
    if(address == nullptr || strcmp(address, "") == 0 ){
        if (m_pAddress != nullptr) {
            delete [] m_pAddress;
            m_pAddress = nullptr;
        }
    } else {
        const int len = strlen(address);

        if(m_pAddress != nullptr) {
            delete []m_pAddress;
        }

        m_pAddress = new char[len + 1];
        memset(m_pAddress,0, len + 1);
        strncpy(m_pAddress, address, len);
    }
}

void Person::showPersonMessage() {

    if (m_pName != nullptr && m_pAddress != nullptr) {
        std::cout<<"name:"<<m_pName<<",age:"<<m_age<<",address:"<<m_pAddress<<endl;
    }else if(m_pName != nullptr ) {
         std::cout<<"name:"<<m_pName<<",age:"<<m_age<<",address为空"<<endl;
    }else if(m_pAddress != nullptr ) {
        std::cout<<"name为空"<<",age:"<<m_age<<",address:"<<m_pAddress<<endl;
   }
}

void Person::clear() {
    if(m_pName != nullptr) {
        delete[] m_pName;
        m_pName = nullptr;
    }

    m_age = 0;

    if(m_pAddress != nullptr) {
        delete [] m_pAddress;
        m_pAddress = nullptr;
    }
}
