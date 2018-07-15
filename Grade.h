#pragma once
#include<iostream>
#include "ID.h"
#include"Course.h" 
#include"Account.h"
#pragma warning(disable:4584)    //�رն�̳д����ľ���
#define _GET_GRADE_ID(stuID,courseID) (((courseID) % 10000000) * 10000000 + stuID % 10000000)
#define PASS (true)
#define FAIL (false)

const char* const RESULT_GRADE_TO_STR[12] =
{ "A+","A ","A-","B+","B ","B-","C+","C ","C-","D+","D ","F " };
const double GRADE_TO_GPA[12] =
{ 4.0,  4.0,  3.7,      3.3,   3.0,   2.7,      2.3,  2.0,    1.7,      1.3,  1,  0 };
const int PERCENT_TO_GRADE[13] =
{ 101,100,95,90,85,80,77,73,70,67,63,60,-1 };
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
        m_uResult.Percent = result;    //���о�������˸�ֵ
    }
};


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
    //�ӿ�
    virtual void SetID();    //�ɼ���IDΪ ���γ���IDȥ����λ��+��ѧ����IDȥ����λ��
    virtual void Display()const;
    virtual void Write(std::ofstream&)const;
    virtual void Read(std::ifstream&);
    //ֻ��ʾ�ɼ�
    void DisplayGradeOnly()const;
    friend bool operator>(const Grade&, const Grade&);
protected:
    RESULT m_Result;
    IDTYPE m_iStuID;
};

//�������Grade��ID
//class+class
IDTYPE operator+(const Course& course, const Account& stu);
IDTYPE operator+(const Account& stu, const Course& course);
//class+ID
IDTYPE operator+(IDTYPE courseID, const Account& stu);
IDTYPE operator+(const Account& stu, IDTYPE courseID);
IDTYPE operator+(const Course& course, IDTYPE stuID);
IDTYPE operator+(IDTYPE stuID, const Course& course);

bool operator>(const Grade& left, const Grade& right);