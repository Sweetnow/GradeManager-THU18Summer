#pragma once
#include<string>
#include<iostream>
#include<iomanip>
#include<algorithm>
#include<set>
#include"Hash.h"
#include"ID.h"

const char* const ACCOUNT_TYPE_TO_STR[4] = { "未设置","学生","教师","管理员", };

//账户种类
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
    //初始化，用户名 密码 账户类型
    void Init(std::string, std::string, ACCOUNT_TYPE);
    //基类接口实现
    virtual void SetID();
    virtual void Display()const;
    virtual void Write(std::ofstream&)const;
    virtual void Read(std::ifstream&);
    //用户名相关
    void SetUserName(std::string);
    //密码相关
    void SetPwd(std::string);
    bool CheckPwd(std::string)const;
    bool ChangePwd(std::string, std::string);
    void ResetPwd(std::string, const Account& admin);
    //账户种类相关
    void SetAccountType(ACCOUNT_TYPE);

    void AddCourseIntoSet(IDTYPE);
    bool IsCourseInSet(IDTYPE)const;
    void DelCourseOutSet(IDTYPE);
    //ID设置相关
    static IDTYPE sm_iLastID;    //上一个使用的ID
protected:
    std::string m_sUserName;    //用户名
    PWDTYPE m_iPwd;    //密码的Hash散列
    ACCOUNT_TYPE m_eType;    //账户类型
    std::set<IDTYPE>m_setCourseID;    //可访问的课程ID
private:
    bool isPwdSet;    //密码是否为第一次设置
};

