#include "Grade.h"


Grade::Grade() {
}

Grade::Grade(Course& course, IDTYPE stuID) :
    Course(course), m_iStuID(stuID), m_Result(0, course.GetCourseResultType()) {
    assert(Course::isInit && !ID::isInit);
    SetID();
    ID::isInit = true;
    Course::m_setStudentID.clear();    //删除set中的信息
}


Grade::~Grade() {
}


RESULT Grade::GetGradeResult()const {
    assert(Course::isInit && ID::isInit);
    return m_Result;
}

IDTYPE Grade::GetGradeID()const {
    assert(Course::isInit && ID::isInit);
    return ID::m_iID;
}


void Grade::SetGradeResult(RESULT result) {
    assert(Course::isInit && ID::isInit);
    assert(result.m_eType == m_Result.m_eType);
    m_Result.m_uResult = result.m_uResult;
}

void Grade::SetID() {
    //debug
    IDTYPE test = GET_GRADE_ID(m_iStuID, Course::m_iID);
    ID::m_iID = (Course::m_iID % 10000000) * 10000000 + m_iStuID % 10000000;
    assert(test == ID::m_iID);
}

void Grade::Display()const {
    assert(Course::isInit && ID::isInit);
    Course::Display();
    std::cout << "成绩类型:" << RESULT_TYPE_TO_STR[m_Result.m_eType] << "  成绩：";
    switch (m_Result.m_eType) {
    case Result_None:
        break;
    case Result_Percent:
        std::cout << m_Result.m_uResult.Percent;
        break;
    case Result_Grade:
        std::cout << RESULT_GRADE_TO_STR[m_Result.m_uResult.GPA];
        break;
    case Result_PF:
        std::cout << (m_Result.m_uResult.isPass ? "通过" : "不通过");
        break;
    }
    std::cout << std::endl;
}

void Grade::Write(std::ofstream &file)const {
    assert(Course::isInit && ID::isInit);
    ID::Write(file);
    Course::Write(file);
    assert(file.is_open() && file.good());
    file.write((char*)&m_Result, sizeof(m_Result));
    file.write((char*)&m_iStuID, sizeof(m_iStuID));
}

void Grade::Read(std::ifstream &file) {
    ID::Read(file);
    Course::Read(file);
    assert(file.is_open() && file.good());
    file.read((char*)&m_Result, sizeof(m_Result));
    file.read((char*)&m_iStuID, sizeof(m_iStuID));
}
