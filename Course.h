#pragma once
#include "ID.h"
#include<string>
#include<iostream>
#include<set>
#include<algorithm>
const char* const RESULT_TYPE_TO_STR[4] = { "未设置","百分制","等级制","P/F", };

enum RESULT_TYPE {
    Result_None,    //未设置
    Result_Percent,    //百分制
    Result_Grade,    //等级制
    Result_PF,    //通过与不通过
};
class Course :
    public ID {
public:
    Course();
    virtual ~Course();
    //初始化 课程名 学分 评价方式
    void Init(std::string, int, RESULT_TYPE);
    //基类接口实现
    virtual void SetID();
    virtual void Display();
    virtual void Write(std::ofstream&);
    virtual void Read(std::ifstream&);
    //Get
    std::string GetCourseName();
    int GetCoursePoint();
    RESULT_TYPE GetCourseResultType();
    std::set<IDTYPE> GetCourseStudentID();

    //set
    void SetCourseName(std::string);
    void SetCoursePoint(int);
    void SetCourseResultType(RESULT_TYPE);

    //StudentID相关
    void AddStudentIntoSet(IDTYPE);
    bool IsStudentInSet(IDTYPE);
    void DelStudentOutSet(IDTYPE);

    //ID设置相关
    static IDTYPE sm_iLastID;    //上一个使用的ID
protected:
    std::string m_sCourseName;    //课程名
    int m_iPoint;    //学分
    RESULT_TYPE m_eType;
    std::set<IDTYPE>m_setStudentID;    //选课的学生ID
};

