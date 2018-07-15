#include "Grade.h"


Grade::Grade() {
}

Grade::Grade(Course& course, IDTYPE stuID) :
    Course(course), m_iStuID(stuID), m_Result(0, Result_None) {
    assert(Course::isInit && !ID::isInit);
    assert(course.GetCourseResultType() != Result_None);
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

const std::pair<int, double> Grade::Result2Pair() const {
    switch (m_Result.m_eType) {
    case Result_Percent:
        for (int i = 0; i < 12; i++) {
            if (m_Result.m_uResult.Percent < PERCENT_TO_GRADE[i] && m_Result.m_uResult.Percent >= PERCENT_TO_GRADE[i + 1]) {
                return std::make_pair(m_iPoint, GRADE_TO_GPA[i]);
            }
        }
        assert(false);
        return std::make_pair(0, 0.0);
        break;
    case Result_Grade:
        return std::make_pair(m_iPoint, GRADE_TO_GPA[m_Result.m_uResult.GPA]);
        break;
    case Result_PF:
        return std::make_pair(0, 0.0);
        break;
    default:
        assert(m_eType!=Account_None);
        return std::make_pair(0, 0.0);
        break;
    }
}

IDTYPE Grade::GetStuID() const {
    return m_iStuID;
}


void Grade::SetGradeResult(RESULT result) {
    assert(Course::isInit && ID::isInit);
    m_Result = result;
}

void Grade::SetID() {
    //debug
    IDTYPE test = _GET_GRADE_ID(m_iStuID, Course::m_iID);
    ID::m_iID = (Course::m_iID % 10000000) * 10000000 + m_iStuID % 10000000;
    assert(test == ID::m_iID);
}

void Grade::Display()const {
    assert(Course::isInit && ID::isInit);
    Course::Display();
    std::cout << "  成绩：";
    switch (m_Result.m_eType) {
    case Result_None:
        std::cout << "未录入";
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

void Grade::DisplayGradeOnly() const {
    assert(Course::isInit && ID::isInit);
    std::cout << "成绩：";
    switch (m_Result.m_eType) {
    case Result_None:
        std::cout << "未录入";
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
}

//方便计算Grade的ID
//class+class
IDTYPE operator+(const Course& course, const Account& stu) {
    assert(stu.GetAccountType() == Account_Student);
    return _GET_GRADE_ID(stu.GetID(), course.GetID());
}
IDTYPE operator+(const Account& stu, const Course& course) {
    return course + stu;
}
//class+ID
IDTYPE operator+(IDTYPE courseID, const Account& stu) {
    assert(stu.GetAccountType() == Account_Student);
    return _GET_GRADE_ID(stu.GetID(), courseID);
}
IDTYPE operator+(const Account& stu, IDTYPE courseID) {
    return courseID + stu;
}
IDTYPE operator+(const Course& course, IDTYPE stuID) {
    return _GET_GRADE_ID(stuID, course.GetID());
}
IDTYPE operator+(IDTYPE stuID, const Course& course) {
    return course + stuID;
}

bool operator>(const Grade& left, const Grade& right) {
    assert(left.m_Result.m_eType == right.m_Result.m_eType || left.m_Result.m_eType == Result_None || right.m_Result.m_eType == Result_None);
    if (left.m_Result.m_eType == Result_None && right.m_Result.m_eType == Result_None)
        return left.m_iStuID < right.m_iStuID;
    else if (left.m_Result.m_eType == Result_None)
        return false;
    else if (right.m_Result.m_eType == Result_None)
        return true;
    else {
        switch (left.m_Result.m_eType) {
        case Result_Percent:
            return left.m_Result.m_uResult.Percent > right.m_Result.m_uResult.Percent || (left.m_Result.m_uResult.Percent == right.m_Result.m_uResult.Percent && left.m_iStuID < right.m_iStuID);
            break;
        case Result_Grade:
            return left.m_Result.m_uResult.Percent < right.m_Result.m_uResult.Percent || (left.m_Result.m_uResult.Percent == right.m_Result.m_uResult.Percent && left.m_iStuID < right.m_iStuID);
            break;
        case Result_PF:
            return left.m_Result.m_uResult.isPass > right.m_Result.m_uResult.isPass || (left.m_Result.m_uResult.Percent == right.m_Result.m_uResult.Percent && left.m_iStuID < right.m_iStuID);
            break;
        }
    }
    return false;
}