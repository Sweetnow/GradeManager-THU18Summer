#pragma once
#include<string>
#include<iostream>
#include<iomanip>
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
    ACCOUNT_TYPE GetAccountType()const;
    std::string GetUserName()const;
    std::set<IDTYPE>& GetAccountCourseID();
    //��ʼ�����û��� ���� �˻�����
    void Init(std::string, std::string, ACCOUNT_TYPE);
    //����ӿ�ʵ��
    virtual void SetID();
    virtual void Display()const;
    virtual void Write(std::ofstream&)const;
    virtual void Read(std::ifstream&);
    //�û������
    void SetUserName(std::string);
    //�������
    void SetPwd(std::string);
    bool CheckPwd(std::string)const;
    bool ChangePwd(std::string, std::string);
    void ResetPwd(std::string, const Account& admin);
    //�˻��������
    void SetAccountType(ACCOUNT_TYPE);

    void AddCourseIntoSet(IDTYPE);
    bool IsCourseInSet(IDTYPE)const;
    void DelCourseOutSet(IDTYPE);
    //ID�������
    static IDTYPE sm_iLastID;    //��һ��ʹ�õ�ID
protected:
    std::string m_sUserName;    //�û���
    PWDTYPE m_iPwd;    //�����Hashɢ��
    ACCOUNT_TYPE m_eType;    //�˻�����
    std::set<IDTYPE>m_setCourseID;    //�ɷ��ʵĿγ�ID
private:
    bool isPwdSet;    //�����Ƿ�Ϊ��һ������
};

