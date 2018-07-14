#include "Course.h"


IDTYPE Course::sm_iLastID = 30000000;

Course::Course() {
}


Course::~Course() {
}

void Course::Init(std::string coursename, int point, RESULT_TYPE type) {
    assert(!isInit);
    isInit = true;
    SetID();
    SetCourseName(coursename);
    SetCoursePoint(point);
    SetCourseResultType(type);
}


void Course::SetID() {
    m_iID = ++sm_iLastID;
}

void Course::Display() {
    assert(isInit);
    std::cout << "课程名：" << m_sCourseName << "  学分：" << m_iPoint << "  成绩记录方式:" << RESULT_TYPE_TO_STR[m_eType] << std::endl;
}

void Course::Write(std::ofstream& file) {
    assert(isInit);
    ID::Write(file);
    assert(file.is_open() && file.good());
    //存入用户名
    size_t len = m_sCourseName.length();
    file.write((char*)&len, sizeof(len));
    file.write(m_sCourseName.data(), sizeof(char)*len);
    //存入其他内容
    file.write((char*)&m_iPoint, sizeof(m_iPoint));
    file.write((char*)&m_eType, sizeof(m_eType));
    //存入set
    size_t setSize = m_setStudentID.size();
    file.write((char*)&setSize, sizeof(setSize));
    std::for_each(m_setStudentID.begin(), m_setStudentID.end(), [&](const IDTYPE& data)->void {file.write((char*)&data, sizeof(data)); });
}

void Course::Read(std::ifstream& file) {
    ID::Read(file);
    assert(file.is_open() && file.good());
    //读入用户名
    size_t len;
    file.read((char*)&len, sizeof(len));
    char *tmpCourseName = new char[len + 1];
    file.read(tmpCourseName, sizeof(char)*len);
    tmpCourseName[len] = 0;
    m_sCourseName = tmpCourseName;
    delete[] tmpCourseName;
    //读入其他内容
    file.read((char*)&m_iPoint, sizeof(m_iPoint));
    file.read((char*)&m_eType, sizeof(m_eType));
    //存入set
    size_t setSize;
    IDTYPE tmpID;
    m_setStudentID.clear();
    file.read((char*)&setSize, sizeof(setSize));
    for (size_t i = 0; i < setSize; i++) {
        file.read((char*)&tmpID, sizeof(tmpID));
        m_setStudentID.insert(tmpID);
    }
}

std::string Course::GetCourseName() {
    assert(isInit);
    return m_sCourseName;
}

int Course::GetCoursePoint() {
    assert(isInit);
    return m_iPoint;
}

RESULT_TYPE Course::GetCourseResultType() {
    assert(isInit);
    return m_eType;
}

std::set<IDTYPE> Course::GetCourseStudentID() {
    assert(isInit);
    return m_setStudentID;
}

void Course::SetCourseName(std::string name) {
    assert(isInit);
    m_sCourseName = name;
}

void Course::SetCoursePoint(int point) {
    assert(isInit);
    m_iPoint = point;
}

void Course::SetCourseResultType(RESULT_TYPE type) {
    assert(isInit);
    m_eType = type;
}

void Course::AddStudentIntoSet(IDTYPE StudentID) {
    assert(isInit);
    m_setStudentID.insert(StudentID);
}

bool Course::IsStudentInSet(IDTYPE StudentID) {
    assert(isInit);
    return std::find(m_setStudentID.begin(), m_setStudentID.end(), StudentID) != m_setStudentID.end();
}

void Course::DelStudentOutSet(IDTYPE StudentID) {
    assert(isInit);
    m_setStudentID.erase(StudentID);
}
