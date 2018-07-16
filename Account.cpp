#include "Account.h"

IDTYPE Account::sm_iLastID = 10000000;

Account::Account():isPwdSet(false) {
}


Account::~Account() {
}

ACCOUNT_TYPE Account::GetAccountType()const {
    assert(isInit);
    return m_eType;
}

std::string Account::GetUserName()const {
    assert(isInit);
    return m_sUserName;
}

std::set<IDTYPE>& Account::GetAccountCourseID() {
    assert(isInit);
    return m_setCourseID;
}

void Account::Init(std::string username, std::string pwd, ACCOUNT_TYPE type) {
    assert(!isInit);
    isInit = true;
    SetUserName(username);
    SetPwd(pwd);
    SetAccountType(type);
    SetID();
}

void Account::SetID() {
    m_iID = ++sm_iLastID;
}

void Account::Display()const {
    assert(isInit);
    std::cout << "�˻���:" << std::setw(10) << std::left << m_sUserName << std::right << "  �˻�����:" << ACCOUNT_TYPE_TO_STR[m_eType];
}

void Account::Write(std::ofstream& file)const {
    assert(isInit);
    ID::Write(file);
    assert(file.is_open() && file.good());
    //�����û���
    size_t len = m_sUserName.length();
    file.write((char*)&len, sizeof(len));
    file.write(m_sUserName.data(), sizeof(char)*len);
    //������������
    file.write((char*)&m_iPwd, sizeof(m_iPwd));
    file.write((char*)&m_eType, sizeof(m_eType));
    file.write((char*)&isPwdSet, sizeof(isPwdSet));
    //����set
    size_t setSize = m_setCourseID.size();
    file.write((char*)&setSize, sizeof(setSize));
    std::for_each(m_setCourseID.begin(), m_setCourseID.end(), [&](const IDTYPE& data)->void {file.write((char*)&data, sizeof(data)); });
}

void Account::Read(std::ifstream& file) {
    ID::Read(file);
    assert(file.is_open() && file.good());
    //�����û���
    size_t len;
    file.read((char*)&len, sizeof(len));
    char *tmpUserName = new char[len + 1];
    file.read(tmpUserName, sizeof(char)*len);
    tmpUserName[len] = 0;
    m_sUserName = tmpUserName;
    delete[] tmpUserName;
    //������������
    file.read((char*)&m_iPwd, sizeof(m_iPwd));
    file.read((char*)&m_eType, sizeof(m_eType));
    file.read((char*)&isPwdSet, sizeof(isPwdSet));
    //����set
    size_t setSize;
    IDTYPE tmpID;
    m_setCourseID.clear();
    file.read((char*)&setSize, sizeof(setSize));
    for (size_t i = 0; i < setSize; i++) {
        file.read((char*)&tmpID, sizeof(tmpID));
        m_setCourseID.insert(tmpID);
    }
}

void Account::SetUserName(std::string username) {
    assert(isInit);
    m_sUserName = username;
}

void Account::SetPwd(std::string RawPwd) {
    assert(isInit);
    assert(!isPwdSet);
    if (!isPwdSet) {     //�������û�����ù�
        PWDTYPE salt = BKDRHash(m_sUserName);
        std::string Pwd = std::to_string(salt) + RawPwd;
        m_iPwd = BKDRHash(Pwd);
        isPwdSet = true;
    }
}

bool Account::CheckPwd(std::string RawPwd)const {
    assert(isInit);
    if (isPwdSet) {     //������뱻���ù���������
        PWDTYPE salt = BKDRHash(m_sUserName);
        std::string Pwd = std::to_string(salt) + RawPwd;
        return m_iPwd == BKDRHash(Pwd);
    }
    else {
        assert(isPwdSet);
        return false;
    }
}

bool Account::ChangePwd(std::string oldPwd, std::string newPwd) {
    assert(isInit);
    if (CheckPwd(oldPwd)) {    //���ԭ������ȷ
        isPwdSet = false;
        SetPwd(newPwd);
        return true;
    }
    else {
        return false;
    }
}

void Account::ResetPwd(std::string RawPwd, const Account & admin) {
    assert(isInit);
    assert(isPwdSet);
    if (isPwdSet && admin.GetAccountType() == Account_Administrator) {     //������뱻���ù�
        PWDTYPE salt = BKDRHash(m_sUserName);
        std::string Pwd = std::to_string(salt) + RawPwd;
        m_iPwd = BKDRHash(Pwd);
    }
}

void Account::SetAccountType(ACCOUNT_TYPE type) {
    assert(isInit);
    m_eType = type;
}


void Account::AddCourseIntoSet(IDTYPE courseID) {
    assert(isInit);
    m_setCourseID.insert(courseID);
}

bool Account::IsCourseInSet(IDTYPE courseID)const {
    assert(isInit);
    return m_setCourseID.find(courseID) != m_setCourseID.end();
}

void Account::DelCourseOutSet(IDTYPE courseID) {
    assert(isInit);
    m_setCourseID.erase(courseID);
}
