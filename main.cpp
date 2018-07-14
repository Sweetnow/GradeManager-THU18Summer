#include<iostream>
#include<fstream>
#include<map>
#include<algorithm>
#include"Account.h"
#include"Course.h"
#include"Grade.h"
#include<stdio.h>
#include<iomanip>

#define _INIT 1

using std::cout;
using std::cin;
using std::endl;

//ȫ��״̬��
ACCOUNT_TYPE nowType;
Account *nowAccount = nullptr;
std::map<IDTYPE, Account>AccountMap;
std::map<IDTYPE, Course>CourseMap;
std::map<IDTYPE, Grade>GradeMap;

bool isExit = false;

const char* FileName = "alldata.bin";
const int WINDOWS_MAX_WIDTH = 80;
const int WINDOWS_LEFT_WIDTH = 25;

//menu
void ShowHead(), EnterMainMenu(), EnterAccountMenu();

//module
void Login();    //��½

void CreateAccount(ACCOUNT_TYPE);
void SaveFile(), LoadFile();    //�ļ�����
void CreateCourse();
void test();


int main() {
#if _INIT
    Account master;
    master.Init("A", "123456", Account_Administrator);
    AccountMap[master.GetID()] = master;
#else
    LoadFile();
#endif
    //��½
    Login();
    if (isExit) {
        SaveFile(); return 0;
    }
    //������
    EnterMainMenu();


    SaveFile();
    system("pause");
    return 0;
}

void ShowHead() {
    cout.fill('=');
    cout << std::setw(WINDOWS_MAX_WIDTH) << "" << endl;
    cout.fill('*');
    cout << std::setw(WINDOWS_LEFT_WIDTH) << "" << std::left << std::setw(WINDOWS_MAX_WIDTH - WINDOWS_LEFT_WIDTH) << "ѧ���ɼ�����ϵͳV0.2(alpha)" << endl;
    cout.fill('=');
    cout << std::setw(WINDOWS_MAX_WIDTH) << "" << endl;
    //�ָ�Ĭ��
    cout.fill(' ');
    cout << std::right;
}

void EnterAccountMenu() {

}

void EnterMainMenu() {
    int N;
    //��ʼ��
    system("cls");
    ShowHead();
    cin.clear();
    cin.sync();
    nowAccount->Display();
    //
    switch (nowType) {
    case Account_None:
        assert(nowType != Account_None);
        break;
    case Account_Student:    //ѧ���˵�




        break;
    case Account_Teacher:    //��ʦ�˵�
        while (!isExit) {
            cout.fill('*');
            cout << std::setw(WINDOWS_LEFT_WIDTH) << "" << std::left << std::setw(WINDOWS_MAX_WIDTH - WINDOWS_LEFT_WIDTH) << "1.�����γ�" << std::right << endl;
            cout << std::setw(WINDOWS_LEFT_WIDTH) << "" << std::left << std::setw(WINDOWS_MAX_WIDTH - WINDOWS_LEFT_WIDTH) << "2.�˳�" << std::right << endl;
            cout.fill('=');
            cout << std::setw(WINDOWS_MAX_WIDTH) << "" << endl;
            //�ָ�Ĭ��
            cout.fill(' ');
            switch (cin >> N, N) {
            case 1:
                CreateCourse();
                break;
            case 2:
                isExit = true;
                break;
            }
        }
        break;
    case Account_Administrator:    //����Ա�˵�

        while (!isExit) {
            cout.fill('*');
            cout << std::setw(WINDOWS_LEFT_WIDTH) << "" << std::left << std::setw(WINDOWS_MAX_WIDTH - WINDOWS_LEFT_WIDTH) << "1.������ʦ�˻�" << std::right << endl;
            cout << std::setw(WINDOWS_LEFT_WIDTH) << "" << std::left << std::setw(WINDOWS_MAX_WIDTH - WINDOWS_LEFT_WIDTH) << "2.����ѧ���˻�" << std::right << endl;

            cout << std::setw(WINDOWS_LEFT_WIDTH) << "" << std::left << std::setw(WINDOWS_MAX_WIDTH - WINDOWS_LEFT_WIDTH) << "3.�˳�" << std::right << endl;
            cout << std::setw(WINDOWS_LEFT_WIDTH) << "" << std::left << std::setw(WINDOWS_MAX_WIDTH - WINDOWS_LEFT_WIDTH) << "test 0.Ϊѧ��ѡ��" << std::right << endl;
            cout.fill('=');
            cout << std::setw(WINDOWS_MAX_WIDTH) << "" << endl;
            //�ָ�Ĭ��
            cout.fill(' ');
            switch (cin >> N, N) {
            case 1:
                CreateAccount(Account_Teacher);
                break;
            case 2:
                CreateAccount(Account_Student);
                break;
            case 3:
                isExit = true;
                break;
            case 0:
                test();
                break;
            }
        }
        break;
    }
}

void Login() {
    std::string username, pwd;
    char ch;
    bool isOK = false;
    //���벿��
    while (!isOK) {
        system("cls");
        ShowHead();
        cout.fill('*');
        cout << std::setw(WINDOWS_LEFT_WIDTH) << "" << std::left << std::setw(WINDOWS_MAX_WIDTH - WINDOWS_LEFT_WIDTH) << "�� ½ �� ��" << std::right << endl;
        cout << "�������û���:";
        cin >> username;
        cout << "����������:";
        cin >> pwd;
        cin.clear();
        cin.sync();
        //���
        auto it = std::find_if(AccountMap.begin(), AccountMap.end(), [&](std::pair<IDTYPE, Account> account)->bool {return username == account.second.GetUserName(); });
        if (it == AccountMap.end()) {
            bool isInputCorrect = false;    //�Ƿ���ȷ����
            do {
                cout << "�û�����������������Ƿ���������(Y/N)" << endl;
                cin.clear();
                cin.sync();
                cin >> ch;
                switch (ch) {
                case 'Y': case 'y':
                    isInputCorrect = true;
                    break;
                case 'N':case'n':
                    isInputCorrect = true;
                    isExit = true;    //�˳�����
                    isOK = true;
                    break;
                default:
                    break;
                }
            } while (!isInputCorrect);
        }
        else if (it->second.CheckPwd(pwd)) {
            cout << "��½�ɹ�!" << endl;
            nowAccount = &(it->second);
            nowType = nowAccount->GetAccountType();
            isOK = true;
        }
        else {
            bool isInputCorrect = false;    //�Ƿ���ȷ����
            do {
                cout << "�û�����������������Ƿ���������(Y/N)" << endl;
                cin.clear();
                cin.sync();
                cin >> ch;
                switch (ch) {
                case 'Y': case 'y':
                    isInputCorrect = true;
                    break;
                case 'N':case'n':
                    isInputCorrect = true;
                    isExit = true;    //�˳�����
                    isOK = true;
                    break;
                default:
                    break;
                }
            } while (!isInputCorrect);
        }
    }
}

void CreateAccount(ACCOUNT_TYPE type) {
    assert(type == Account_Student || type == Account_Teacher);
    Account account;
    std::string username, pwd;
    cout << "�������˻������ʼ���룺";
    cin >> username >> pwd;
    account.Init(username, pwd, type);
    AccountMap[account.GetID()] = account;
}
void CreateCourse() {
    Course course;
    std::string coursename;
    int point;
    int type;
    cout << "�����뿪��γ�������ѧ�֣�";
    cin >> coursename >> point;
    while (point <= 0) {
        cout << "�����ѧ�����������0�����������룺";
        cin >> point;
    }
    do {
        cout << "������γ����۷�ʽ������1-3��һ�����֣���Ӧ��ϵΪ��1-�ٷ���  2-�ȼ���  3-P/F��";
        cin >> type;
    } while (type < 0 || type>3);
    course.Init(coursename, point, (RESULT_TYPE)type);
    CourseMap[course.GetID()] = course;
    nowAccount->AddCourseIntoSet(course.GetID());
}

void test() {
    bool isStuSelect = false, isCourseSelect = false;
    IDTYPE StuID, CourseID;
    system("cls");
    cout << "������ѧ������" << endl;
    for (auto& account : AccountMap) {
        if (account.second.GetAccountType() == Account_Student) {
            cout << account.first << "  ";
            account.second.Display();
        }
    }
    cout << "��������Ҫѡ���ѧ��ID:";
    cin >> StuID;
    while (AccountMap.find(StuID) == AccountMap.end()) {
        cout << "��������������������Ҫѡ���ѧ��ID:";
        cin >> StuID;
    }
    auto *nowStu = &AccountMap[StuID];
    system("cls");
    cout << "�����ǿγ��б�" << endl;
    for (auto& course : CourseMap) {
        cout << course.first << "  ";
        course.second.Display();
    }
    cout << "��������Ҫѡ��Ŀγ�ID:";
    cin >> CourseID;
    while (CourseMap.find(CourseID) == CourseMap.end()) {
        cout << "��������������������Ҫѡ���ѧ��ID:";
        cin >> CourseID;
    }
    auto *nowCourse = &CourseMap[CourseID];
    nowStu->AddCourseIntoSet(CourseID);
    nowCourse->AddStudentIntoSet(StuID);
    Grade grade(*nowCourse, StuID);
    GradeMap[grade.GetGradeID()] = grade;
}

void SaveFile() {
    std::ofstream File(FileName, std::ios_base::binary);
    if (File.is_open()) {
        //д��AccountMap
        size_t accountSize = AccountMap.size();
        File.write((char*)&accountSize, sizeof(accountSize));
        for (auto it = AccountMap.begin(); it != AccountMap.end(); it++) {
            File.write((char*)&(it->first), sizeof(it->first));
            it->second.Write(File);
        }
        File.write((char*)&Account::sm_iLastID, sizeof(Account::sm_iLastID));
        //д��CourseMap
        size_t courseSize = CourseMap.size();
        File.write((char*)&courseSize, sizeof(courseSize));
        for (auto it = CourseMap.begin(); it != CourseMap.end(); it++) {
            File.write((char*)&(it->first), sizeof(it->first));
            it->second.Write(File);
        }
        File.write((char*)&Course::sm_iLastID, sizeof(Course::sm_iLastID));
        //д��GradeMap
        size_t gradeSize = GradeMap.size();
        File.write((char*)&gradeSize, sizeof(gradeSize));
        for (auto it = GradeMap.begin(); it != GradeMap.end(); it++) {
            File.write((char*)&(it->first), sizeof(it->first));
            it->second.Write(File);
        }
        File.write((char*)&Grade::sm_iLastID, sizeof(Grade::sm_iLastID));
        File.close();
    }
    else {
        cout << "�����ļ�δ�ܳɹ���" << endl;
        system("pause");
        exit(0);
    }
}

void LoadFile() {
    std::ifstream File(FileName, std::ios_base::binary);
    if (File.is_open()) {
        //��ȡAccountMap
        size_t accountSize;
        File.read((char*)&accountSize, sizeof(accountSize));
        for (size_t i = 0; i < accountSize; i++) {
            std::pair<IDTYPE, Account>tmpAccount;
            File.read((char*)&(tmpAccount.first), sizeof(tmpAccount.first));
            tmpAccount.second.Read(File);
            AccountMap.insert(tmpAccount);
        }
        File.read((char*)&Account::sm_iLastID, sizeof(Account::sm_iLastID));
        //��ȡCourseMap
        size_t courseSize;
        File.read((char*)&courseSize, sizeof(courseSize));
        for (size_t i = 0; i < courseSize; i++) {
            std::pair<IDTYPE, Course>tmpCourse;
            File.read((char*)&(tmpCourse.first), sizeof(tmpCourse.first));
            tmpCourse.second.Read(File);
            CourseMap.insert(tmpCourse);
        }
        File.read((char*)&Course::sm_iLastID, sizeof(Course::sm_iLastID));
        //��ȡGradeMap
        size_t gradeSize;
        File.read((char*)&gradeSize, sizeof(gradeSize));
        for (size_t i = 0; i < gradeSize; i++) {
            std::pair<IDTYPE, Grade>tmpGrade;
            File.read((char*)&(tmpGrade.first), sizeof(tmpGrade.first));
            tmpGrade.second.Read(File);
            GradeMap.insert(tmpGrade);
        }
        File.read((char*)&Grade::sm_iLastID, sizeof(Grade::sm_iLastID));
        //�ر��ļ�
        File.close();
    }
    else {
        cout << "�����ļ�δ�ܳɹ���" << endl;
        system("pause");
        exit(0);
    }
}


