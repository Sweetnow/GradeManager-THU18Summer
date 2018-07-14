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

//全局状态量
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
void Login();    //登陆

void CreateAccount(ACCOUNT_TYPE);
void SaveFile(), LoadFile();    //文件操作
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
    //登陆
    Login();
    if (isExit) {
        SaveFile(); return 0;
    }
    //主界面
    EnterMainMenu();


    SaveFile();
    system("pause");
    return 0;
}

void ShowHead() {
    cout.fill('=');
    cout << std::setw(WINDOWS_MAX_WIDTH) << "" << endl;
    cout.fill('*');
    cout << std::setw(WINDOWS_LEFT_WIDTH) << "" << std::left << std::setw(WINDOWS_MAX_WIDTH - WINDOWS_LEFT_WIDTH) << "学生成绩管理系统V0.2(alpha)" << endl;
    cout.fill('=');
    cout << std::setw(WINDOWS_MAX_WIDTH) << "" << endl;
    //恢复默认
    cout.fill(' ');
    cout << std::right;
}

void EnterAccountMenu() {

}

void EnterMainMenu() {
    int N;
    //初始化
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
    case Account_Student:    //学生菜单




        break;
    case Account_Teacher:    //教师菜单
        while (!isExit) {
            cout.fill('*');
            cout << std::setw(WINDOWS_LEFT_WIDTH) << "" << std::left << std::setw(WINDOWS_MAX_WIDTH - WINDOWS_LEFT_WIDTH) << "1.创建课程" << std::right << endl;
            cout << std::setw(WINDOWS_LEFT_WIDTH) << "" << std::left << std::setw(WINDOWS_MAX_WIDTH - WINDOWS_LEFT_WIDTH) << "2.退出" << std::right << endl;
            cout.fill('=');
            cout << std::setw(WINDOWS_MAX_WIDTH) << "" << endl;
            //恢复默认
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
    case Account_Administrator:    //管理员菜单

        while (!isExit) {
            cout.fill('*');
            cout << std::setw(WINDOWS_LEFT_WIDTH) << "" << std::left << std::setw(WINDOWS_MAX_WIDTH - WINDOWS_LEFT_WIDTH) << "1.创建教师账户" << std::right << endl;
            cout << std::setw(WINDOWS_LEFT_WIDTH) << "" << std::left << std::setw(WINDOWS_MAX_WIDTH - WINDOWS_LEFT_WIDTH) << "2.创建学生账户" << std::right << endl;

            cout << std::setw(WINDOWS_LEFT_WIDTH) << "" << std::left << std::setw(WINDOWS_MAX_WIDTH - WINDOWS_LEFT_WIDTH) << "3.退出" << std::right << endl;
            cout << std::setw(WINDOWS_LEFT_WIDTH) << "" << std::left << std::setw(WINDOWS_MAX_WIDTH - WINDOWS_LEFT_WIDTH) << "test 0.为学生选课" << std::right << endl;
            cout.fill('=');
            cout << std::setw(WINDOWS_MAX_WIDTH) << "" << endl;
            //恢复默认
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
    //输入部分
    while (!isOK) {
        system("cls");
        ShowHead();
        cout.fill('*');
        cout << std::setw(WINDOWS_LEFT_WIDTH) << "" << std::left << std::setw(WINDOWS_MAX_WIDTH - WINDOWS_LEFT_WIDTH) << "登 陆 界 面" << std::right << endl;
        cout << "请输入用户名:";
        cin >> username;
        cout << "请输入密码:";
        cin >> pwd;
        cin.clear();
        cin.sync();
        //检查
        auto it = std::find_if(AccountMap.begin(), AccountMap.end(), [&](std::pair<IDTYPE, Account> account)->bool {return username == account.second.GetUserName(); });
        if (it == AccountMap.end()) {
            bool isInputCorrect = false;    //是否正确输入
            do {
                cout << "用户名或密码输入错误！是否重新输入(Y/N)" << endl;
                cin.clear();
                cin.sync();
                cin >> ch;
                switch (ch) {
                case 'Y': case 'y':
                    isInputCorrect = true;
                    break;
                case 'N':case'n':
                    isInputCorrect = true;
                    isExit = true;    //退出程序
                    isOK = true;
                    break;
                default:
                    break;
                }
            } while (!isInputCorrect);
        }
        else if (it->second.CheckPwd(pwd)) {
            cout << "登陆成功!" << endl;
            nowAccount = &(it->second);
            nowType = nowAccount->GetAccountType();
            isOK = true;
        }
        else {
            bool isInputCorrect = false;    //是否正确输入
            do {
                cout << "用户名或密码输入错误！是否重新输入(Y/N)" << endl;
                cin.clear();
                cin.sync();
                cin >> ch;
                switch (ch) {
                case 'Y': case 'y':
                    isInputCorrect = true;
                    break;
                case 'N':case'n':
                    isInputCorrect = true;
                    isExit = true;    //退出程序
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
    cout << "请输入账户名与初始密码：";
    cin >> username >> pwd;
    account.Init(username, pwd, type);
    AccountMap[account.GetID()] = account;
}
void CreateCourse() {
    Course course;
    std::string coursename;
    int point;
    int type;
    cout << "请输入开设课程名称与学分：";
    cin >> coursename >> point;
    while (point <= 0) {
        cout << "输入的学分数必须大于0，请重新输入：";
        cin >> point;
    }
    do {
        cout << "请输入课程评价方式（输入1-3中一个数字，对应关系为：1-百分制  2-等级制  3-P/F）";
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
    cout << "以下是学生名单" << endl;
    for (auto& account : AccountMap) {
        if (account.second.GetAccountType() == Account_Student) {
            cout << account.first << "  ";
            account.second.Display();
        }
    }
    cout << "请输入你要选择的学生ID:";
    cin >> StuID;
    while (AccountMap.find(StuID) == AccountMap.end()) {
        cout << "输入有误，请重新输入你要选择的学生ID:";
        cin >> StuID;
    }
    auto *nowStu = &AccountMap[StuID];
    system("cls");
    cout << "以下是课程列表" << endl;
    for (auto& course : CourseMap) {
        cout << course.first << "  ";
        course.second.Display();
    }
    cout << "请输入你要选择的课程ID:";
    cin >> CourseID;
    while (CourseMap.find(CourseID) == CourseMap.end()) {
        cout << "输入有误，请重新输入你要选择的学生ID:";
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
        //写入AccountMap
        size_t accountSize = AccountMap.size();
        File.write((char*)&accountSize, sizeof(accountSize));
        for (auto it = AccountMap.begin(); it != AccountMap.end(); it++) {
            File.write((char*)&(it->first), sizeof(it->first));
            it->second.Write(File);
        }
        File.write((char*)&Account::sm_iLastID, sizeof(Account::sm_iLastID));
        //写入CourseMap
        size_t courseSize = CourseMap.size();
        File.write((char*)&courseSize, sizeof(courseSize));
        for (auto it = CourseMap.begin(); it != CourseMap.end(); it++) {
            File.write((char*)&(it->first), sizeof(it->first));
            it->second.Write(File);
        }
        File.write((char*)&Course::sm_iLastID, sizeof(Course::sm_iLastID));
        //写入GradeMap
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
        cout << "数据文件未能成功打开" << endl;
        system("pause");
        exit(0);
    }
}

void LoadFile() {
    std::ifstream File(FileName, std::ios_base::binary);
    if (File.is_open()) {
        //读取AccountMap
        size_t accountSize;
        File.read((char*)&accountSize, sizeof(accountSize));
        for (size_t i = 0; i < accountSize; i++) {
            std::pair<IDTYPE, Account>tmpAccount;
            File.read((char*)&(tmpAccount.first), sizeof(tmpAccount.first));
            tmpAccount.second.Read(File);
            AccountMap.insert(tmpAccount);
        }
        File.read((char*)&Account::sm_iLastID, sizeof(Account::sm_iLastID));
        //读取CourseMap
        size_t courseSize;
        File.read((char*)&courseSize, sizeof(courseSize));
        for (size_t i = 0; i < courseSize; i++) {
            std::pair<IDTYPE, Course>tmpCourse;
            File.read((char*)&(tmpCourse.first), sizeof(tmpCourse.first));
            tmpCourse.second.Read(File);
            CourseMap.insert(tmpCourse);
        }
        File.read((char*)&Course::sm_iLastID, sizeof(Course::sm_iLastID));
        //读取GradeMap
        size_t gradeSize;
        File.read((char*)&gradeSize, sizeof(gradeSize));
        for (size_t i = 0; i < gradeSize; i++) {
            std::pair<IDTYPE, Grade>tmpGrade;
            File.read((char*)&(tmpGrade.first), sizeof(tmpGrade.first));
            tmpGrade.second.Read(File);
            GradeMap.insert(tmpGrade);
        }
        File.read((char*)&Grade::sm_iLastID, sizeof(Grade::sm_iLastID));
        //关闭文件
        File.close();
    }
    else {
        cout << "数据文件未能成功打开" << endl;
        system("pause");
        exit(0);
    }
}


