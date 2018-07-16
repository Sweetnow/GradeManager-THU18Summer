#pragma once
#include<iostream>
#include "ID.h"
#include"Course.h" 
#include"Account.h"
#pragma warning(disable:4584)    //�رն�̳д����ľ���
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

//�洢�ɼ��Ľṹ��
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

//ֻ��������ĳɼ��ṹ��
struct RESULT_FOR_SORT {
    IDTYPE stuID;
    int allPoint;
    double sumResult;
    RESULT_FOR_SORT(IDTYPE id, int point, double result) :
        stuID(id), allPoint(point), sumResult(result) {
        assert(allPoint >= 0 && sumResult >= 0);
    }
};

//���������ṹ�������

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
    //�ӿ�
    virtual void SetID();    //�ɼ���IDΪ ���γ���IDȥ����λ��+��ѧ����IDȥ����λ��
    virtual void Display()const;
    virtual void Write(std::ofstream&)const;
    virtual void Read(std::ifstream&);
    //ֻ��ʾ�ɼ�
    void DisplayGradeOnly()const;
    friend bool operator>(const Grade&, const Grade&);
    static const char* const RESULT_GRADE_TO_STR[12]; //���ڽ��ȼ�ת��ΪA+...
    static const double GRADE_TO_GPA[12];  //���ڽ��ȼ�ת��ΪGPA
    static const int PERCENT_TO_GRADE[13];  //���ڽ��ٷ���ת��ΪGPA
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