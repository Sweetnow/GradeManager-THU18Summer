#pragma once
#include<string>
#include<iostream>
#include<algorithm>
#include<set>
#include"Hash.h"
#include"ID.h"

const char* const ACCOUNT_TYPE_TO_STR[4] = { "δ����","ѧ��","��ʦ","����Ա", };

//�˻�����
enum ACCOUNT_TYPE {
    Account_None,
    Account_Student,
    Account_Teacher,
    Account_Administrator,
};

class Account :
    public ID {
public:
    Account();
    virtual ~Account();
    //Get
    ACCOUNT_TYPE GetAccountType();
    std::string GetUserName();
    std::set<IDTYPE> GetAccountCourseID();
    //��ʼ�����û��� ���� �˻�����
    void Init(std::string, std::string, ACCOUNT_TYPE);
    //����ӿ�ʵ��
    virtual void SetID();
    virtual void Display();
    virtual void Write(std::ofstream&);
    virtual void Read(std::ifstream&);
    //�û������
    void SetUserName(std::string);
    //�������
    void SetPwd(std::string);
    bool CheckPwd(std::string);
    bool ChangePwd(std::string, std::string);
    //�˻��������
    void SetAccountType(ACCOUNT_TYPE);
    //CourseID���
    //StudentID���
    void AddCourseIntoSet(IDTYPE);
    bool IsCourseInSet(IDTYPE);
    void DelCourseOutSet(IDTYPE);
    //ID�������
    static IDTYPE sm_iLastID;    //��һ��ʹ�õ�ID
protected:
    std::string m_sUserName;    //�û���
    PWDTYPE m_iPwd;    //�����Hashɢ��
    ACCOUNT_TYPE m_eType;    //�˻�����
    std::set<IDTYPE>m_setCourseID;    //�ɷ��ʵĿγ�ID
private:
    bool isPwdSet = false;    //�����Ƿ�Ϊ��һ������
};

