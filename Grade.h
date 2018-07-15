#pragma once
#include<iostream>
#include "ID.h"
#include"Course.h" 
#pragma warning(disable:4584)    //�رն�̳д����ľ���
#define GET_GRADE_ID(stuID,courseID) (((courseID) % 10000000) * 10000000 + stuID % 10000000)

const char* const RESULT_GRADE_TO_STR[12] =
{ "A_PLUS","A","A_MINUS","B_PLUS","B","B_MINUS","C_PLUS","C","C_MINUS","D_PLUS","D","F" };
const double GRADE_TO_GPA[12] =
{ 4.0,  4.0,  3.7,      3.3,   3.0,   2.7,      2.3,  2.0,    1.7,      1.3,  1,  0 };

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
    //set
    void SetGradeResult(RESULT);
    //�ӿ�
    virtual void SetID();    //�ɼ���IDΪ ���γ���IDȥ����λ��+��ѧ����IDȥ����λ��
    virtual void Display()const;
    virtual void Write(std::ofstream&)const;
    virtual void Read(std::ifstream&);
protected:
    RESULT m_Result;
    IDTYPE m_iStuID;
};

