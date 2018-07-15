#pragma once
#include "ID.h"
#include<string>
#include<iostream>
#include<iomanip>
#include<set>
#include<algorithm>
const char* const RESULT_TYPE_TO_STR[4] = { "δ����","�ٷ���","�ȼ���","P/F", };

enum RESULT_TYPE {
    Result_None,    //δ����
    Result_Percent,    //�ٷ���
    Result_Grade,    //�ȼ���
    Result_PF,    //ͨ���벻ͨ��
};
class Course :
    public ID {
public:
    Course();
    virtual ~Course();
    //��ʼ�� �γ��� ѧ�� ���۷�ʽ
    void Init(std::string, int, RESULT_TYPE);
    //����ӿ�ʵ��
    virtual void SetID();
    virtual void Display()const;
    virtual void Write(std::ofstream&)const;
    virtual void Read(std::ifstream&);
    //Get
    std::string GetCourseName()const;
    int GetCoursePoint()const;
    RESULT_TYPE GetCourseResultType()const;
    std::set<IDTYPE>& GetCourseStudentID();

    //set
    void SetCourseName(std::string);
    void SetCoursePoint(int);
    void SetCourseResultType(RESULT_TYPE);

    //StudentID���
    void AddStudentIntoSet(IDTYPE);
    bool IsStudentInSet(IDTYPE)const;
    void DelStudentOutSet(IDTYPE);
    //ID�������
    static IDTYPE sm_iLastID;    //��һ��ʹ�õ�ID
protected:
    std::string m_sCourseName;    //�γ���
    int m_iPoint;    //ѧ��
    RESULT_TYPE m_eType;
    std::set<IDTYPE>m_setStudentID;    //ѡ�ε�ѧ��ID
};

