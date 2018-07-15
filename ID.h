#pragma once
#include<fstream>
#include<cassert>
typedef unsigned long long IDTYPE;
//������,Ψһʶ����ID
class ID {
public:
    ID();
    virtual ~ID();

    //�ӿ�
    virtual void SetID() = 0;    //����ID����Ҫ��������Ĺ��캯���б�����
    virtual void Display()const = 0;    //��ʾ��
    virtual void Write(std::ofstream&)const;    //д��������ļ�
    virtual void Read(std::ifstream&);    //�Ӷ������ļ��ж�ȡ
                                          //Get
    IDTYPE GetID()const;
protected:
    IDTYPE m_iID;
    bool isInit = false;    //���Ƿ񱻳�ʼ����
};


