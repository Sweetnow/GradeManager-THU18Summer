#pragma once
#include<iostream>
#include "ID.h"
#include"Course.h" 
#include"Account.h"
#pragma warning(disable:4584)    //关闭多继承带来的警告
#define _GET_GRADE_ID(stuID,courseID) (((courseID) % 10000000) * 10000000 + stuID % 10000000)
#define PASS (true)
#define FAIL (false)


enum RESULT_GRAGE {
    A_PLUS,
    A,
    A_MINUS,
    B_PLUS,
    B,
    B_MINUS,
    C_PLUS,
    C,
    C_MINUS,
    D_PLUS,
    D,
    F,
};

//存储成绩的结构体
struct RESULT {
    RESULT_TYPE m_eType;
    union {
        RESULT_GRAGE GPA;
        int Percent;
        bool isPass;
    }m_uResult;
    RESULT(int result = 0, RESULT_TYPE type = Result_None) :
        m_eType(type) {
        assert(result >= 0);
        m_uResult.Percent = result;    //所有均可以如此赋值
    }
};

//只用于排序的成绩结构体
struct RESULT_FOR_SORT {
    IDTYPE stuID;
    int allPoint;
    double sumResult;
    RESULT_FOR_SORT(IDTYPE id, int point, double result) :
        stuID(id), allPoint(point), sumResult(result) {
        assert(allPoint >= 0 && sumResult >= 0);
    }
};

//排序上述结构体的算子

bool CMP_RESULT_FOR_SORT(const RESULT_FOR_SORT& left, const RESULT_FOR_SORT& right);



class Grade :
    public ID, public Course {
public:
    Grade();
    Grade(Course&, IDTYPE);
    virtual ~Grade();
    //Get
    RESULT GetGradeResult()const;
    IDTYPE GetGradeID()const;
    const std::pair<int, double> Result2Pair()const;
    IDTYPE GetStuID()const;
    //set
    void SetGradeResult(RESULT);
    //接口
    virtual void SetID();    //成绩类ID为 “课程类ID去掉首位后”+“学生类ID去掉首位”
    virtual void Display()const;
    virtual void Write(std::ofstream&)const;
    virtual void Read(std::ifstream&);
    //只显示成绩
    void DisplayGradeOnly()const;
    friend bool operator>(const Grade&, const Grade&);
    static const char* const RESULT_GRADE_TO_STR[12]; //用于将等级转换为A+...
    static const double GRADE_TO_GPA[12];  //用于将等级转换为GPA
    static const int PERCENT_TO_GRADE[13];  //用于将百分制转换为GPA
protected:
    RESULT m_Result;
    IDTYPE m_iStuID;
};

//方便计算Grade的ID
//class+class
IDTYPE operator+(const Course& course, const Account& stu);
IDTYPE operator+(const Account& stu, const Course& course);
//class+ID
IDTYPE operator+(IDTYPE courseID, const Account& stu);
IDTYPE operator+(const Account& stu, IDTYPE courseID);
IDTYPE operator+(const Course& course, IDTYPE stuID);
IDTYPE operator+(IDTYPE stuID, const Course& course);

bool operator>(const Grade& left, const Grade& right);