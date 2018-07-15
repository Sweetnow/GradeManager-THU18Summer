#include<iostream>
#include<fstream>
#include<map>
#include<algorithm>
#include"Account.h"
#include"Course.h"
#include"Grade.h"
#include<stdio.h>
#include<iomanip>

#define _INIT 0

using std::cout;
using std::cin;
using std::endl;

//全局状态量
ACCOUNT_TYPE nowType = Account_None;
Account *nowAccount = nullptr;
std::map<IDTYPE, Account>AccountMap;
std::map<IDTYPE, Course>CourseMap;
std::map<IDTYPE, Grade>GradeMap;
//是否退出整个程序
bool isExit = false;

const char* FileName = "alldata.bin";
const int WINDOWS_MAX_WIDTH = 80;
const int WINDOWS_LEFT_WIDTH = 25;

//选择菜单
void ShowHead(), EnterMainMenu(), EnterAdminMenu(), EnterStuMenu(), EnterTeaMenu();

//管理员菜单功能模块
void CreateAccount();
void DelAccount();
void ResetAccountPwd();
void ShowAllAccount();
void ShowAllTeacher();
bool ShowOneTeacher();
void ShowAllStudent();
bool ShowOneStudent();
void ShowAllCourse();
void ShowAllCourse(Account&);
bool ShowOneCourse();
bool ShowOneCourse(Account&);
void ChooseCourseMenu();
//选课模块
void ChooseCourseOne();
void ChooseCourseFile();
//学生菜单功能模块
void ShowStuGrade(Account&);
//教师菜单功能模块
void CreateCourse();
bool DelCourse();
void EnterCourseMenu();
//课程菜单功能模块


//其他功能模块
void Login();    //登陆
void SaveFile(), LoadFile();    //文件操作


int main() {
#if _INIT
    Account master;
    master.Init("A", "123456", Account_Administrator);
    AccountMap[master.GetID()] = master;
#else
    LoadFile();
#endif
    //登陆
    while (!isExit) {
        Login();
        if (isExit) {
            SaveFile();
            return 0;
        }
        //主界面
        EnterMainMenu();
    }

    SaveFile();
    return 0;
}

void ShowHead() {
    cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
    cout << "┃                                                                ┃\n";
    cout << "┃                   学生成绩管理系统 Version0.3                  ┃\n";
    cout << "┃                                                                ┃\n";
    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
    return;
}

//管理员主菜单
void EnterAdminMenu() {
    int N;
    //菜单循环
    while (!isExit) {
        system("cls");
        ShowHead();
        cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
        cout << "     "; nowAccount->Display(); cout << '\n';
        cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
        cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
        cout << "┃               1. 创建账户                                      ┃\n";
        cout << "┃               2. 删除账户                                      ┃\n";
        cout << "┃               3. 修改账户密码                                  ┃\n";
        cout << "┃               4. 查看所有账户                                  ┃\n";
        cout << "┃               5. 查看教师信息                                  ┃\n";
        cout << "┃               6. 查看学生信息                                  ┃\n";
        cout << "┃               7. 查看课程信息                                  ┃\n";
        cout << "┃               8. 添加选课学生列表                              ┃\n";
        cout << "┃               9. 退出登录(返回上一级)                          ┃\n";
        cout << "┃               0. 退出程序                                      ┃\n";
        cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
        //输入循环
        do {
            bool isBreak = false;
            N = -1;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << " 请输入所选菜单序号：";
            cin >> N;
            switch (N) {
            case 1:
                CreateAccount();
                break;
            case 2:
                DelAccount();
                break;
            case 3:
                ResetAccountPwd();
                break;
            case 4:
                ShowAllAccount();
                cout << "\n 查看详细信息请转到 《查看教师/学生信息》 菜单\n" << endl;
                cout << ' ';
                system("pause");
                break;
            case 5:
                while (!isBreak) {
                    ShowAllTeacher();
                    ShowOneTeacher();
                }
                break;
            case 6:
                while (!isBreak) {
                    ShowAllStudent();
                    isBreak = ShowOneStudent();
                }
                break;
            case 7:
                while (!isBreak) {
                    ShowAllCourse();
                    ShowOneCourse();
                }
                break;
            case 8:
                ChooseCourseMenu();
                break;
            case 9:
                nowType = Account_None;
                nowAccount = nullptr;
                return;
                break;
            case 0:
                isExit = true;
                return;
                break;
            default:
                cout << " 输入有误，请重新输入,";
                break;
            }
        } while (N < 0 || N > 9);
    }
}

void EnterStuMenu() {
    int N;
    //菜单循环
    while (!isExit) {
        system("cls");
        ShowHead();
        cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
        cout << "     "; nowAccount->Display(); cout << '\n';
        cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
        cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
        cout << "┃               1. 修改账户密码                                  ┃\n";
        cout << "┃               2. 查看课程与成绩                                ┃\n";
        cout << "┃               9. 退出登录(返回上一级)                          ┃\n";
        cout << "┃               0. 退出程序                                      ┃\n";
        cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
        //输入循环
        do {
            N = -1;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << " 请输入所选菜单序号：";
            cin >> N;
            switch (N) {
            case 1:
                ResetAccountPwd();
                break;
            case 2:
                ShowStuGrade(*nowAccount);
                break;
            case 9:
                nowType = Account_None;
                nowAccount = nullptr;
                return;
                break;
            case 0:
                isExit = true;
                return;
                break;
            default:
                cout << " 输入有误，请重新输入,";
                break;
            }
        } while (N < 0 || N > 9 || (N > 2 && N < 9));
    }
}
void EnterTeaMenu() {
    int N;
    //菜单循环
    while (!isExit) {
        system("cls");
        ShowHead();
        cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
        cout << "     "; nowAccount->Display(); cout << '\n';
        cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
        cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
        cout << "┃               1. 修改账户密码                                  ┃\n";
        cout << "┃               2. 查看课程与登记成绩                            ┃\n";
        cout << "┃               3. 开设课程                                      ┃\n";
        cout << "┃               4. 删除课程                                      ┃\n";
        cout << "┃               9. 退出登录(返回上一级)                          ┃\n";
        cout << "┃               0. 退出程序                                      ┃\n";
        cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
        //输入循环
        do {
            bool isBreak = false;
            N = -1;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << " 请输入所选菜单序号：";
            cin >> N;
            switch (N) {
            case 1:
                ResetAccountPwd();
                break;
            case 2:
                EnterCourseMenu();
                break;
            case 3:
                CreateCourse();
                break;
            case 4:
                while (!isBreak) {
                    ShowAllCourse(*nowAccount);
                    isBreak = DelCourse();
                }
                break;
            case 9:
                nowType = Account_None;
                nowAccount = nullptr;
                return;
                break;
            case 0:
                isExit = true;
                return;
                break;
            default:
                cout << " 输入有误，请重新输入,";
                break;
            }
        } while (N < 0 || N > 9 || (N > 2 && N < 9));
    }
}

void EnterMainMenu() {
    //进入对应菜单
    switch (nowType) {
    case Account_None:
        assert(nowType != Account_None);
        break;
    case Account_Student:    //学生菜单
        EnterStuMenu();
        break;
    case Account_Teacher:    //教师菜单
        EnterTeaMenu();
        break;
    case Account_Administrator:    //管理员菜单
        EnterAdminMenu();
        break;
    }
}

void Login() {
    std::string username, pwd;
    char ch;
    bool isOK = false;
    //输入部分
    system("cls");
    ShowHead();
    cout << " ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄登┄┄┄┄┄┄┄┄┄┄┄┄┄陆┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄" << endl;
    while (!isOK) {
        cout << " 请输入用户名:";
        cin >> username;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << " 请输入密码:";
        cin >> pwd;
        //检查
        auto it = std::find_if(AccountMap.begin(), AccountMap.end(), [&](std::pair<IDTYPE, Account> account)->bool {return username == account.second.GetUserName(); });
        if (it == AccountMap.end()) {
            bool isInputCorrect = false;    //是否正确输入
            do {
                cout << " 用户名或密码输入错误！是否重新输入(Y/N):";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
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
            cout << " 登陆成功!" << endl;
            nowAccount = &(it->second);
            nowType = nowAccount->GetAccountType();
            isOK = true;
        }
        else {
            bool isInputCorrect = false;    //是否正确输入
            do {
                cout << " 用户名或密码输入错误！是否重新输入(Y/N):";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
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

void CreateAccount() {
    Account account;
    std::string username, pwd, pwdChk;
    int type;
    //初始化
    system("cls");
    ShowHead();
    cout << " ┄┄┄┄┄┄┄┄┄┄┄创┄┄┄┄┄┄┄┄┄┄建┄┄┄┄┄┄┄┄┄┄┄┄帐┄┄┄┄┄┄┄┄┄┄┄户┄┄┄┄┄┄┄┄┄┄┄┄" << endl;
    //主循环
    while (true) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << " 请输入要创建的账户类型(1-学生 2-教师 0-返回上一级):";
        cin >> type;
        if (type == 0)return;
        while (type != 1 && type != 2) {
            cout << " 输入有误，请重新输入(1-学生 2-教师 0-返回上一级):";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cin >> type;
            if (type == 0)return;
        }
        cout << " 请输入账户名(0-返回上一级):";
        cin >> username;
        if (username == "0")return;
        do {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << " 请输入初始密码(0-返回上一级):";
            cin >> pwd;
            if (pwd == "0")return;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << " 请再次输入初始密码:";
            cin >> pwdChk;
            if (pwdChk != pwd) {
                cout << " 两次密码输入不一致！";
            }
        } while (pwdChk != pwd);
        account.Init(username, pwd, (ACCOUNT_TYPE)type);
        AccountMap[account.GetID()] = account;
    }
}
void DelAccount() {
    IDTYPE id;
    //初始化
    system("cls");
    ShowAllAccount();
    cout << " ┄┄┄┄┄┄┄┄┄┄┄删┄┄┄┄┄┄┄┄┄┄除┄┄┄┄┄┄┄┄┄┄┄┄帐┄┄┄┄┄┄┄┄┄┄┄户┄┄┄┄┄┄┄┄┄┄┄┄" << endl;
    //主循环
    while (true) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << " 输入要删除的账户ID(输入0返回上一级):";
        cin >> id;
        if (id == 0) {
            return;
        }
        if (AccountMap.find(id) == AccountMap.end()) {
            cout << " 输入有误，请重新输入，";
        }
        else {
            switch (AccountMap[id].GetAccountType()) {
            case Account_Student:
                if (!AccountMap[id].GetAccountCourseID().empty()) {
                    for (auto it = AccountMap[id].GetAccountCourseID().begin(); it != AccountMap[id].GetAccountCourseID().end(); it++) {
                        GradeMap.erase(AccountMap[id] + *it);  //删除对应的成绩
                        CourseMap[*it].DelStudentOutSet(AccountMap[id].GetID());   //删除课程中的记录
                    }
                }
                AccountMap.erase(id);
                cout << " 账户" << id << "已被删除" << endl;
                break;
            case Account_Teacher:
                if (!AccountMap[id].GetAccountCourseID().empty()) {
                    //删除开设的课程
                    for (auto it = AccountMap[id].GetAccountCourseID().begin(); it != AccountMap[id].GetAccountCourseID().end(); it++) {
                        //查找对应课程中的学生，删除Grade
                        for (auto stu = CourseMap[*it].GetCourseStudentID().begin(); stu != CourseMap[*it].GetCourseStudentID().end(); stu++) {
                            GradeMap.erase(_GET_GRADE_ID(*stu, *it));  //删除对应的成绩
                        }
                        CourseMap.erase(*it);   //删除课程中的记录
                    }
                }
                AccountMap.erase(id);
                cout << " 账户" << id << "已被删除" << endl;
                break;
            case Account_Administrator:
                cout << " 禁止删除管理员账户，请重新输入，";
                break;
            default:
                assert(false);
                break;
            }
        }
    }
}
void ResetAccountPwd() {
    IDTYPE id;
    //初始化
    system("cls");
    ShowHead();
    //管理员重置密码
    if (nowType == Account_Administrator) {
        cout << " ┄┄┄┄┄┄┄┄┄┄┄密┄┄┄┄┄┄┄┄┄┄码┄┄┄┄┄┄┄┄┄┄┄┄重┄┄┄┄┄┄┄┄┄┄┄置┄┄┄┄┄┄┄┄┄┄┄┄\n" << endl;
        ShowAllAccount();
        //主循环
        while (true) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << " 输入要重置密码的账户ID(输入0返回上一级):";
            cin >> id;
            if (id == 0)return;
            if (AccountMap.find(id) == AccountMap.end()) {
                cout << " 输入有误，请重新输入，";
            }
            else {
                std::string pwd, pwdChk;
                do {
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    cout << " 请输入新密码(输入0返回上一级):";
                    cin >> pwd;
                    if (pwd == "0")return;
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    cout << " 请再次输入新密码:";
                    cin >> pwdChk;
                    if (pwdChk != pwd) {
                        cout << " 两次密码输入不一致！";
                    }
                } while (pwdChk != pwd);
                AccountMap[id].ResetPwd(pwd, *nowAccount);
                cout << " 账户" << id << "密码修改成功" << endl;
            }
        }
    }
    //普通账户修改密码
    else {
        bool isOK = false;
        assert(nowType != Account_None);
        cout << " ┄┄┄┄┄┄┄┄┄┄┄密┄┄┄┄┄┄┄┄┄┄码┄┄┄┄┄┄┄┄┄┄┄┄修┄┄┄┄┄┄┄┄┄┄┄改┄┄┄┄┄┄┄┄┄┄┄┄\n" << endl;
        std::string oldpwd, newpwd, pwdChk;
        do {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << " 请输入旧密码(输入0返回上一级):";
            cin >> oldpwd;
            if (oldpwd == "0")return;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << " 请输入新密码(输入0返回上一级):";
            cin >> newpwd;
            if (newpwd == "0")return;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << " 请再次输入新密码:";
            cin >> pwdChk;
            if (pwdChk != newpwd) {
                cout << " 两次密码输入不一致！";
            }
            else if (nowAccount->ChangePwd(oldpwd, newpwd)) {
                cout << " 密码修改成功" << endl;
                isOK = true;
            }
            else {
                cout << " 旧密码输入错误！";
            }
        } while (!isOK);
    }
}
void ShowAllAccount() {
    //初始化
    system("cls");
    ShowHead();
    cout << " ┄┄┄┄┄┄┄┄┄┄┄所┄┄┄┄┄┄┄┄┄┄有┄┄┄┄┄┄┄┄┄┄┄┄帐┄┄┄┄┄┄┄┄┄┄┄户┄┄┄┄┄┄┄┄┄┄┄┄" << endl;
    //主循环
    for (auto it = AccountMap.begin(); it != AccountMap.end(); it++) {
        cout << " 账户ID " << it->first << "  ";
        it->second.Display();
        cout << endl;
    }
}
void ShowAllTeacher() {
    //初始化
    system("cls");
    ShowHead();
    cout << " ┄┄┄┄┄┄┄┄┄┄┄教┄┄┄┄┄┄┄┄┄┄师┄┄┄┄┄┄┄┄┄┄┄┄帐┄┄┄┄┄┄┄┄┄┄┄户┄┄┄┄┄┄┄┄┄┄┄┄" << endl;
    //显示基本信息
    for (auto it = AccountMap.begin(); it != AccountMap.end(); it++) {
        if (it->second.GetAccountType() == Account_Teacher) {
            cout << " 账户ID " << it->first << "  ";
            it->second.Display();
            cout << endl;
        }
    }
}
bool ShowOneTeacher() {
    return false;
}
void ShowAllStudent() {
    //初始化
    system("cls");
    ShowHead();
    cout << " ┄┄┄┄┄┄┄┄┄┄┄学┄┄┄┄┄┄┄┄┄┄生┄┄┄┄┄┄┄┄┄┄┄┄帐┄┄┄┄┄┄┄┄┄┄┄户┄┄┄┄┄┄┄┄┄┄┄┄" << endl;
    //显示基本信息
    for (auto it = AccountMap.begin(); it != AccountMap.end(); it++) {
        if (it->second.GetAccountType() == Account_Student) {
            cout << " 账户ID " << it->first << "  ";
            it->second.Display();
            cout << endl;
        }
    }
}
bool ShowOneStudent() {
    IDTYPE id;
    while (true) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << " 输入要查看的学生账户ID(输入0返回上一级):";
        cin >> id;
        if (id == 0) {
            return true;
        }
        if (AccountMap.find(id) == AccountMap.end() || AccountMap[id].GetAccountType() != Account_Student) {
            cout << " 输入有误，请重新输入，";
        }
        else {
            ShowStuGrade(AccountMap[id]);
            break;
        }
    }
    return false;
}
//显示全部课程
void ShowAllCourse() {
    //初始化
    system("cls");
    ShowHead();
    cout << " ┄┄┄┄┄┄┄┄┄┄┄所┄┄┄┄┄┄┄┄┄┄有┄┄┄┄┄┄┄┄┄┄┄┄课┄┄┄┄┄┄┄┄┄┄┄程┄┄┄┄┄┄┄┄┄┄┄┄" << endl;
    //显示基本信息
    for (auto it = CourseMap.begin(); it != CourseMap.end(); it++) {
        cout << " 课程ID " << it->first << "  ";
        it->second.Display();
        cout << endl;
    }
}
//显示教师类tea开设的课程
void ShowAllCourse(Account& tea) {
    assert(tea.GetAccountType() == Account_Teacher);
    //初始化
    system("cls");
    ShowHead();
    cout << " ┄┄┄┄┄┄┄┄┄┄┄开┄┄┄┄┄┄┄┄┄┄设┄┄┄┄┄┄┄┄┄┄┄┄课┄┄┄┄┄┄┄┄┄┄┄程┄┄┄┄┄┄┄┄┄┄┄┄" << endl;
    //显示基本信息
    for (auto it = tea.GetAccountCourseID().begin(); it != tea.GetAccountCourseID().end(); it++) {
        cout << " 课程ID " << *it << "  ";
        CourseMap[*it].Display();
        cout << endl;
    }
}
bool ShowOneCourse() {
    return false;
}
bool ShowOneCourse(Account& tea) {
    return false;
}
void ChooseCourseMenu() {
    int N;
    //菜单循环
    while (true) {
        bool isInputError;
        system("cls");
        ShowHead();
        cout << " ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄选┄┄┄┄┄┄┄┄┄┄┄┄┄课┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄" << endl;
        cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
        cout << "┃               1. 手动添加                                      ┃\n";
        cout << "┃               2. 文件导入                                      ┃\n";
        cout << "┃               0. 返回上一级                                    ┃\n";
        cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
        //输入循环
        do {
            isInputError = false;
            N = -1;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << " 请输入所选菜单序号：";
            cin >> N;
            switch (N) {
            case 1:
                ChooseCourseOne();
                break;
            case 2:
                ChooseCourseFile();
                break;
            case 0:
                return;
                break;
            default:
                isInputError = true;
                cout << " 输入有误，请重新输入,";
                break;
            }
        } while (isInputError);
    }
}
void ChooseCourseOne() {
    while (true) {
        bool isStuSelect = false, isCourseSelect = false;
        IDTYPE StuID, CourseID;
        ShowAllStudent();
        cout << " 请输入你要选择的学生ID(0-返回上一级):";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cin >> StuID;
        if (StuID == 0)return;
        while (AccountMap.find(StuID) == AccountMap.end()) {
            cout << " 输入有误，请重新输入你要选择的学生ID(0-返回上一级):";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cin >> StuID;
            if (StuID == 0)return;
        }
        auto *nowStu = &AccountMap[StuID];
        bool isBreak = false;
        while (!isBreak) {
            ShowAllCourse();
            cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
            cout << "  当前选中学生ID:" << StuID << "  账户名:" << nowStu->GetUserName() << '\n';
            cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
            do {
                cout << " 请输入你要选择的课程ID(0-返回上一级):";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cin >> CourseID;
                if (CourseID == 0) {
                    isBreak = true;
                    break;
                }
                while (CourseMap.find(CourseID) == CourseMap.end()) {
                    cout << " 输入有误，请重新输入你要选择的课程ID(0-返回上一级):";
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    cin >> CourseID;
                    if (CourseID == 0) {
                        isBreak = true;
                        break;
                    }
                }
                if (isBreak)break;
                auto *nowCourse = &CourseMap[CourseID];
                nowStu->AddCourseIntoSet(CourseID);
                nowCourse->AddStudentIntoSet(StuID);
                Grade grade(*nowCourse, StuID);
                GradeMap[grade.GetGradeID()] = grade;
                cout << "选课成功" << endl;
            } while (!isBreak);
        }
    }
}
void ChooseCourseFile() {
}
void ShowStuGrade(Account& stu) {
    assert(stu.GetAccountType() == Account_Student);
    double sumResult = 0;    //统一转换为绩点处理
    int allPoint = 0;    //总学分
    //初始化
    system("cls");
    ShowHead();
    cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
    cout << "  当前学生ID:" << stu.GetID() << "  账户名:" << stu.GetUserName() << '\n';
    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
    cout << " ┄┄┄┄┄┄┄┄┄┄┄课┄┄┄┄┄┄┄┄┄┄程┄┄┄┄┄┄┄┄┄┄┄┄成┄┄┄┄┄┄┄┄┄┄┄绩┄┄┄┄┄┄┄┄┄┄┄┄" << endl;
    for (auto it = stu.GetAccountCourseID().begin(); it != stu.GetAccountCourseID().end(); it++) {
        assert(GradeMap.find(*it + stu) != GradeMap.end());
        const Grade& grade = GradeMap[*it + stu];
        cout << ' '; grade.Display(); cout << endl;
        sumResult += grade.Result2Pair().second * grade.Result2Pair().first;
        allPoint += grade.Result2Pair().first;
    }
    if (allPoint == 0)
        cout << " 平均绩点为: NaN" << endl;
    else
        cout << " 平均绩点为:" << sumResult / allPoint << endl;
    cout << "\n "; system("pause");
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

bool DelCourse() {

    IDTYPE id;
    while (true) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << " 输入要查看的学生账户ID(输入0返回上一级):";
        cin >> id;
        if (id == 0) {
            return true;
        }
        if (AccountMap.find(id) == AccountMap.end() || AccountMap[id].GetAccountType() != Account_Student) {
            cout << " 输入有误，请重新输入，";
        }
        else {
            ShowStuGrade(AccountMap[id]);
            break;
        }
    }
    return false;
    //删除开设的课程
    for (auto it = AccountMap[id].GetAccountCourseID().begin(); it != AccountMap[id].GetAccountCourseID().end(); it++) {
        //查找对应课程中的学生，删除Grade
        for (auto stu = CourseMap[*it].GetCourseStudentID().begin(); stu != CourseMap[*it].GetCourseStudentID().end(); stu++) {
            GradeMap.erase(_GET_GRADE_ID(*stu, *it));  //删除对应的成绩
        }
        CourseMap.erase(*it);   //删除课程中的记录
    }
}

void EnterCourseMenu() {
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


