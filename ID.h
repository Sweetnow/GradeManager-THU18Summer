#pragma once
#include<fstream>
#include<cassert>
typedef unsigned long long IDTYPE;
//抽象类,唯一识别码ID
class ID {
public:
    ID();
    virtual ~ID();

    //接口
    virtual void SetID() = 0;    //设置ID，需要在派生类的构造函数中被调用
    virtual void Display()const = 0;    //显示类
    virtual void Write(std::ofstream&)const;    //写入二进制文件
    virtual void Read(std::ifstream&);    //从二进制文件中读取

    //Get
    IDTYPE GetID()const;
protected:
    IDTYPE m_iID;
    bool isInit;    //类是否被初始化过
    mutable bool hasWritten;    //类是否被存入文件中
private:
    static IDTYPE sm_iFirstID;    //起始ID
};


