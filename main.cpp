#include<iostream>
#include<fstream>
#include<map>
#include<algorithm>
#include"Account.h"
#include"Course.h"
#include"Grade.h"
#include<stdio.h>
#include<iomanip>
#include<vector>


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

//文件
const char* FileName = "alldata.bin";

//选择菜单

void ShowHead(), EnterMainMenu(), EnterAdminMenu(), EnterStuMenu(), EnterTeaMenu();

//管理员菜单功能模块

void CreateAccount();
void DelAccount();
void ResetAccountPwd();
void ShowAllAccount();
void ShowAllTeacher();
bool ShowOneTeacher();
bool ShowAllStudent(bool);
bool ShowOneStudent();
void ShowAllCourse();
void ShowAllCourse(Account&);
bool ShowOneCourse();
bool ShowOneCourse(Account&);
void SortAll();

//选课模块

void ChooseCourse();

//学生菜单功能模块

void ShowStuGrade(Account&);

//教师菜单功能模块

bool CreateCourse();
bool DelCourse();
void EnterCourseMenu(IDTYPE);

//课程菜单功能模块

void ShowAllStuInCourse(IDTYPE);
void InputGrade(IDTYPE);
bool InputOneGrade(Grade&);

void ChangeGrade(IDTYPE);
void DelGrade(IDTYPE);
void SortAndShow(IDTYPE);

//其他功能模块

void Login();    //登陆
void SaveFile(std::ofstream&), LoadFile(std::ifstream&);    //文件操作


int main() {
    std::ios::sync_with_stdio(false);
    std::ifstream iFile(FileName, std::ios_base::binary);
    if (iFile.is_open()) {
        LoadFile(iFile);
    }
    else {
        Account master;
        master.Init("A", "123456", Account_Administrator);
        AccountMap[master.GetID()] = master;
    }
    //登陆
    while (!isExit) {
        Login();
        if (isExit) {
            break;
        }
        //主界面
        EnterMainMenu();
    }
    std::ofstream oFile(FileName, std::ios_base::binary);
    if (oFile.is_open())
        SaveFile(oFile);
    else {
        cout << " Error: 数据文件未能成功打开" << endl;
        system("pause");
        exit(0);
    }
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
            cout << " 请输入所选菜单序号:";
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
                    isBreak = ShowOneTeacher();
                }
                break;
            case 6:
                while (!isBreak) {
                    isBreak = ShowAllStudent(false);
                }
                break;
            case 7:
                while (!isBreak) {
                    ShowAllCourse();
                    isBreak = ShowOneCourse();
                }
                break;
            case 8:
                ChooseCourse();
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

//学生主菜单
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
            cout << " 请输入所选菜单序号:";
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

//教师主菜单
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
            cout << " 请输入所选菜单序号:";
            cin >> N;
            switch (N) {
            case 1:
                ResetAccountPwd();
                break;
            case 2:
                while (!isBreak) {
                    ShowAllCourse(*nowAccount);
                    isBreak = ShowOneCourse(*nowAccount);
                }
                break;
            case 3:
                while (!isBreak) {
                    ShowAllCourse(*nowAccount);
                    isBreak = CreateCourse();
                }
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
        } while (N < 0 || N > 9 || (N > 4 && N < 9));
    }
}

//进入对应菜单
void EnterMainMenu() {
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

//登陆逻辑与界面
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
                cout << " 用户名或密码输入错误!是否重新输入(Y/N):";
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
                cout << " 用户名或密码输入错误!是否重新输入(Y/N):";
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

//创建账户
void CreateAccount() {
    std::string username, pwd, pwdChk;
    //初始化
    system("cls");
    ShowHead();
    cout << " ┄┄┄┄┄┄┄┄┄┄┄创┄┄┄┄┄┄┄┄┄┄建┄┄┄┄┄┄┄┄┄┄┄┄帐┄┄┄┄┄┄┄┄┄┄┄户┄┄┄┄┄┄┄┄┄┄┄┄" << endl;
    //主循环
    while (true) {
        int type;
        bool sameName;
        Account account;
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
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cin >> username;
        if (username == "0")return;
        do {
            sameName = false;
            for (auto it = AccountMap.begin(); it != AccountMap.end(); it++) {
                if (it->second.GetUserName() == username) {
                    sameName = true;
                    break;
                }
            }
            if (sameName) {
                cout << " 该账户名已被占用，请重新输入账户名(0-返回上一级):";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cin >> username;
                if (username == "0")return;
            }
        } while (sameName);

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
                cout << " 两次密码输入不一致!";
            }
        } while (pwdChk != pwd);
        account.Init(username, pwd, (ACCOUNT_TYPE)type);
        AccountMap[account.GetID()] = account;
        cout << " 创建账户成功!\n" << endl;
    }
}

//删除账户
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
                cout << " 账户" << id << "已被删除\n" << endl;
                break;
            case Account_Teacher:
                if (!AccountMap[id].GetAccountCourseID().empty()) {
                    //删除开设的课程
                    for (auto it = AccountMap[id].GetAccountCourseID().begin(); it != AccountMap[id].GetAccountCourseID().end(); it++) {
                        //查找对应课程中的学生，删除Grade
                        for (auto stu = CourseMap[*it].GetCourseStudentID().begin(); stu != CourseMap[*it].GetCourseStudentID().end(); stu++) {
                            GradeMap.erase(_GET_GRADE_ID(*stu, *it));  //删除对应的成绩
                            AccountMap[*stu].DelCourseOutSet(*it);    //删除学生的set中的记录
                        }
                        CourseMap.erase(*it);   //删除课程中的记录
                    }
                }
                AccountMap.erase(id);
                cout << " 账户" << id << "已被删除\n" << endl;
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

//管理员重置密码，普通用户修改密码
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
                        cout << " 两次密码输入不一致!";
                    }
                } while (pwdChk != pwd);
                AccountMap[id].ResetPwd(pwd, *nowAccount);
                cout << " 账户" << id << "密码修改成功\n" << endl;
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
                cout << " 两次密码输入不一致!";
            }
            else if (nowAccount->ChangePwd(oldpwd, newpwd)) {
                cout << " 密码修改成功\n" << endl;
                isOK = true;
            }
            else {
                cout << " 旧密码输入错误!";
            }
        } while (!isOK);
    }
}

//显示所有账户基本信息
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
    cout << " ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄" << endl;
}

//显示所有教师账户基本信息
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
    cout << " ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄" << endl;
}

//查看某一教师账户详细信息
bool ShowOneTeacher() {
    IDTYPE id;
    while (true) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << " 输入要查看的教师账户ID(0-返回上一级):";
        cin >> id;
        if (id == 0) {
            return true;
        }
        if (AccountMap.find(id) == AccountMap.end() || AccountMap[id].GetAccountType() != Account_Teacher) {
            cout << " 输入有误，请重新输入，";
        }
        else {
            bool isBreak = false;
            while (!isBreak) {
                ShowAllCourse(AccountMap[id]);
                isBreak = ShowOneCourse(AccountMap[id]);
            }
            return false;
        }
    }
}

//显示所有学生账户基本信息
bool ShowAllStudent(bool justShow) {
    //初始化
    system("cls");
    ShowHead();
    cout << " ┄┄┄┄┄┄┄┄┄┄┄学┄┄┄┄┄┄┄┄┄┄生┄┄┄┄┄┄┄┄┄┄┄┄帐┄┄┄┄┄┄┄┄┄┄┄户┄┄┄┄┄┄┄┄┄┄┄┄" << endl;
    //显示基本信息
    for (auto it = AccountMap.begin(); it != AccountMap.end(); it++) {
        if (it->second.GetAccountType() == Account_Student) {
            cout << " 账户ID:" << it->first << "  ";
            it->second.Display();
            cout << endl;
        }
    }
    cout << " ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄" << endl;
    if (!justShow) {
        bool isInputCorrect = false;
        int N;
        do {
            cout << " 选择查看项目(1-所有学生均绩排名 2-单个学生成绩 0-返回上一级):";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cin >> N;
            switch (N) {
            case 1:
                isInputCorrect = true;
                SortAll();
                return false;
                break;
            case 2:
                isInputCorrect = true;
                return ShowOneStudent();
                break;
            case 0:
                return true;
            default:
                break;
            }
        } while (!isInputCorrect);
        return false;
    }
    else
        return false;
}

//查看某一学生账户详细信息
bool ShowOneStudent() {
    IDTYPE id;
    while (true) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << " 输入要查看的学生账户ID(0-返回上一级):";
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
        cout << " 课程ID:" << it->first << "  ";
        it->second.Display();
        cout << endl;
    }
    cout << " ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄" << endl;
}

//显示教师类tea开设的课程
void ShowAllCourse(Account& tea) {
    assert(tea.GetAccountType() == Account_Teacher);
    //初始化
    system("cls");
    ShowHead();
    cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
    cout << "  当前教师ID:" << tea.GetID() << "  账户名:" << tea.GetUserName() << '\n';
    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
    cout << " ┄┄┄┄┄┄┄┄┄┄┄开┄┄┄┄┄┄┄┄┄┄设┄┄┄┄┄┄┄┄┄┄┄┄课┄┄┄┄┄┄┄┄┄┄┄程┄┄┄┄┄┄┄┄┄┄┄┄" << endl;
    //显示基本信息
    for (auto it = tea.GetAccountCourseID().begin(); it != tea.GetAccountCourseID().end(); it++) {
        cout << " 课程ID:" << *it << "  ";
        CourseMap[*it].Display();
        cout << endl;
    }
    cout << " ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄" << endl;
}

//查看某一课程详细信息
bool ShowOneCourse() {
    IDTYPE id;
    while (true) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << " 输入要查看的课程ID(0-返回上一级):";
        cin >> id;
        if (id == 0) {
            return true;
        }
        if (CourseMap.find(id) == CourseMap.end()) {
            cout << " 输入有误，请重新输入，";
        }
        else {
            EnterCourseMenu(id);
            break;
        }
    }
    return false;
}

//查看tea开设的某一课程详细信息
bool ShowOneCourse(Account& tea) {
    IDTYPE id;
    while (true) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << " 输入要查看的课程ID(0-返回上一级):";
        cin >> id;
        if (id == 0) {
            return true;
        }
        if (CourseMap.find(id) == CourseMap.end() || !tea.IsCourseInSet(id)) {
            cout << " 输入有误，请重新输入，";
        }
        else {
            EnterCourseMenu(id);
            break;
        }
    }
    return false;
}

//排序所有学生的总成绩并显示（降序，转换为GPA，精度未小数点后6位）
void SortAll() {
    int allstuPoint = 0;
    double allstuResult = 0;
    system("cls");
    ShowHead();
    cout << " ┄┄┄┄┄┄┄┄┄┄┄均┄┄┄┄┄┄┄┄┄┄绩┄┄┄┄┄┄┄┄┄┄┄┄排┄┄┄┄┄┄┄┄┄┄┄名┄┄┄┄┄┄┄┄┄┄┄┄" << endl;
    std::vector<RESULT_FOR_SORT>sorted;
    sorted.reserve(AccountMap.size());    //够用就是了
    for (auto stu = AccountMap.begin(); stu != AccountMap.end(); stu++) {
        //计算每个学生的绩点
        if (stu->second.GetAccountType() == Account_Student) {
            double sumResult = 0;    //统一转换为绩点处理
            int allPoint = 0;    //总学分
            for (auto it = stu->second.GetAccountCourseID().begin(); it != stu->second.GetAccountCourseID().end(); it++) {
                if (GradeMap.find(*it + stu->second) == GradeMap.end()) {    //如果没有保存成绩的类，就创建之
                    Grade grade(CourseMap[*it], stu->first);
                    GradeMap[*it + stu->second] = grade;
                }
                const Grade& grade = GradeMap[*it + stu->second];
                sumResult += grade.Result2Pair().second * grade.Result2Pair().first;
                allPoint += grade.Result2Pair().first;
            }
            sorted.push_back(RESULT_FOR_SORT(stu->first, allPoint, sumResult));
        }
    }
    std::sort(sorted.begin(), sorted.end(), CMP_RESULT_FOR_SORT);
    int count = 1;
    for (auto it = sorted.begin(); it != sorted.end(); it++) {
        cout << ' ' << std::setw(3) << count++ << "  学生ID:" << it->stuID << "  账户名:" << std::setw(10) << std::left << AccountMap[it->stuID].GetUserName() << std::right;
        if (it->allPoint == 0)
            cout << " 平均绩点为: NaN" << endl;
        else {
            cout << " 平均绩点为:" << it->sumResult / it->allPoint << endl;
            allstuPoint += it->allPoint;
            allstuResult += it->sumResult;
        }
    }
    cout << " ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄" << endl;
    if (allstuPoint == 0)
        cout << " 所有学生平均绩点为: NaN" << endl;
    else
        cout << " 所有学生平均绩点为:" << allstuResult / allstuPoint << '\n' << endl;
    cout << ' '; system("pause");
}


//为学生选课(逐一添加)
void ChooseCourse() {
    //主循环
    while (true) {
        //确定学生
        bool isStuSelect = false, isCourseSelect = false;
        IDTYPE StuID, CourseID;
        ShowAllStudent(true);
        cout << " ┄┄┄┄┄┄┄┄┄┄┄开┄┄┄┄┄┄┄┄┄┄始┄┄┄┄┄┄┄┄┄┄┄┄选┄┄┄┄┄┄┄┄┄┄┄课┄┄┄┄┄┄┄┄┄┄┄┄" << endl;
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
        //确定课程
        bool isBreak = false;
        while (!isBreak) {
            //初始化
            system("cls");

            cout << " ┄┄┄┄┄┄┄┄┄┄┄开┄┄┄┄┄┄┄┄┄┄始┄┄┄┄┄┄┄┄┄┄┄┄选┄┄┄┄┄┄┄┄┄┄┄课┄┄┄┄┄┄┄┄┄┄┄┄" << endl;
            //显示基本信息
            for (auto it = CourseMap.begin(); it != CourseMap.end(); it++) {
                if (!nowStu->IsCourseInSet(it->first)) {
                    cout << " 课程ID:" << it->first << "  ";
                    it->second.Display();
                    cout << endl;
                }
            }
            cout << " ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄" << endl;
            cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
            cout << "  当前选中学生ID:" << StuID << "  账户名:" << nowStu->GetUserName() << '\n';
            cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;

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
            cout << " 选课成功\n" << endl;
            cout << ' '; system("pause");
        }
    }
}

//显示学生stu成绩信息
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
        if (GradeMap.find(*it + stu) == GradeMap.end()) {    //如果没有保存成绩的类，就创建之
            Grade grade(CourseMap[*it], stu.GetID());
            GradeMap[*it + stu] = grade;
        }
        const Grade& grade = GradeMap[*it + stu];
        cout << ' '; grade.Display(); cout << endl;
        sumResult += grade.Result2Pair().second * grade.Result2Pair().first;
        allPoint += grade.Result2Pair().first;
    }
    cout << " ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄" << endl;
    if (allPoint == 0)
        cout << " 平均绩点为: NaN" << endl;
    else
        cout << " 平均绩点为:" << sumResult / allPoint << endl;
    cout << "\n "; system("pause");
}

//教师创建课程
bool CreateCourse() {

    Course course;
    std::string coursename;
    int point;
    int type;
    //课程名
    cout << " 请输入开设课程名称(0-返回上一级):";
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    cin >> coursename;
    if (coursename == "0")return true;
    //学分
    cout << " 请输入该课程学分(0-返回上一级):";
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    cin >> point;
    if (point == 0)return true;
    while (point <= 0) {
        cout << " 学分数必须大于0，请重新输入(0-返回上一级):";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cin >> point;
        if (point == 0)return true;
    }
    //计分方式
    cout << " 请输入课程评价方式(1-百分制 2-等级制 3-P/F 0-返回上一级):";
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    cin >> type;
    if (type == 0)return true;
    while (type < 0 || type>3) {
        cout << " 输入有误，请重新输入课程评价方式(1-百分制 2-等级制 3-P/F 0-返回上一级):";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cin >> type;
        if (type == 0)return true;
    }
    course.Init(coursename, point, (RESULT_TYPE)type);
    CourseMap[course.GetID()] = course;
    nowAccount->AddCourseIntoSet(course.GetID());
    cout << " 课程创建成功!\n" << endl;
    cout << ' '; system("pause");
    return false;
}

//教师删除课程
bool DelCourse() {
    IDTYPE id;
    while (true) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << " 输入要删除的课程ID(输入0返回上一级):";
        cin >> id;
        if (id == 0) {
            return true;
        }
        if (CourseMap.find(id) == CourseMap.end() || !nowAccount->IsCourseInSet(id)) {
            cout << " 输入有误，请重新输入，";
        }
        else {
            //查找对应课程中的学生，删除Grade
            for (auto stu = CourseMap[id].GetCourseStudentID().begin(); stu != CourseMap[id].GetCourseStudentID().end(); stu++) {
                GradeMap.erase(_GET_GRADE_ID(*stu, id));  //删除对应的成绩
                AccountMap[*stu].DelCourseOutSet(id);    //删除学生set中的记录
            }
            //删除开设的课程
            CourseMap.erase(id);   //删除课程中的记录
            nowAccount->DelCourseOutSet(id);    //删除教师中课程的记录
            cout << " 删除课程成功!\n" << endl;
            cout << ' '; system("pause");
            break;
        }
    }
    return false;
}

//课程成绩操作菜单
void EnterCourseMenu(IDTYPE courseID) {
    int N;
    //初始化
    while (true) {
        system("cls");
        ShowHead();
        cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
        cout << "  当前课程ID:" << courseID << " "; CourseMap[courseID].Display(); cout << '\n';
        cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
        //菜单循环
        cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
        cout << "┃               1. 查看所有学生成绩                              ┃\n";
        cout << "┃               2. 按序录入成绩                                  ┃\n";
        cout << "┃               3. 修改成绩                                      ┃\n";
        cout << "┃               4. 删除成绩                                      ┃\n";
        cout << "┃               5. 成绩排序                                      ┃\n";
        cout << "┃               0. 返回上一级                                    ┃\n";
        cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
        //输入循环
        do {
            bool isBreak = false;
            N = -1;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << " 请输入所选菜单序号:";
            cin >> N;
            switch (N) {
            case 1:
                ShowAllStuInCourse(courseID);
                break;
            case 2:
                InputGrade(courseID);
                break;
            case 3:
                ChangeGrade(courseID);
                break;
            case 4:
                DelGrade(courseID);
                break;
            case 5:
                SortAndShow(courseID);
                break;
            case 0:
                return;
                break;
            default:
                cout << " 输入有误，请重新输入,";
                break;
            }
        } while (N < 0 || N > 9 || (N > 5 && N < 9));
    }
}

//显示所有学生成绩
void ShowAllStuInCourse(IDTYPE courseID) {
    double sumResult = 0;
    int count = 0;
    double maxResult = -1;
    double minResult = INT_MAX;
    bool hasGrade[12] = { false,false,false,false,false,false,false,false,false,false,false,false };
    //初始化
    system("cls");
    ShowHead();
    cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
    cout << "  当前课程ID:" << courseID << " "; CourseMap[courseID].Display(); cout << '\n';
    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
    cout << " ┄┄┄┄┄┄┄┄┄┄┄学┄┄┄┄┄┄┄┄┄┄生┄┄┄┄┄┄┄┄┄┄┄┄成┄┄┄┄┄┄┄┄┄┄┄绩┄┄┄┄┄┄┄┄┄┄┄┄" << endl;
    //按序号排列学生
    for (auto it = CourseMap[courseID].GetCourseStudentID().begin(); it != CourseMap[courseID].GetCourseStudentID().end(); it++) {
        IDTYPE gradeID = _GET_GRADE_ID(*it, courseID);
        if (GradeMap.find(gradeID) == GradeMap.end()) {    //如果没有保存成绩的类，就创建之
            Grade grade(CourseMap[courseID], *it);
            GradeMap[gradeID] = grade;
        }
        const Grade& grade = GradeMap[gradeID];
        cout << " 学生ID:" << *it << "  账户名:" << std::setw(10) << std::left << AccountMap[*it].GetUserName() << std::right;
        cout << ' '; grade.DisplayGradeOnly(); cout << endl;
        assert(grade.GetGradeResult().m_eType == Result_None || CourseMap[courseID].GetCourseResultType() == grade.GetGradeResult().m_eType);
        switch (CourseMap[courseID].GetCourseResultType()) {
        case Result_None:
            break;
        case Result_Percent:
            if (grade.GetGradeResult().m_eType == Result_Percent) {
                sumResult += grade.GetGradeResult().m_uResult.Percent;
                count++;
                maxResult = (grade.GetGradeResult().m_uResult.Percent > maxResult ? grade.GetGradeResult().m_uResult.Percent : maxResult);
                minResult = (grade.GetGradeResult().m_uResult.Percent < minResult ? grade.GetGradeResult().m_uResult.Percent : minResult);
            }
            break;
        case Result_Grade:
            if (grade.GetGradeResult().m_eType == Result_Grade) {
                sumResult += GRADE_TO_GPA[grade.GetGradeResult().m_uResult.GPA];
                count++;
                hasGrade[grade.GetGradeResult().m_uResult.GPA] = true;
            }
            break;
        case Result_PF:
            break;
        }
    }
    cout << " ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄" << endl;
    if (count > 0) {    //有已录入的学生
        if (CourseMap[courseID].GetCourseResultType() == Result_Percent) {    //百分制
            cout << " 平均分:" << sumResult / count << "  最高分:" << maxResult << "  最低分:" << minResult << endl;
        }
        else if (CourseMap[courseID].GetCourseResultType() == Result_Grade) {
            int maxGrade = -1, minGrade = 12;
            for (int i = 0; i < 12; i++) {
                if (hasGrade[i])
                    maxGrade = i;
            }
            for (int i = 12 - 1; i >= 0; i--) {
                if (hasGrade[i])
                    minGrade = i;
            }
            cout << " 平均绩点:" << sumResult / count << "  最高绩点:" << GRADE_TO_GPA[maxGrade] << "  最低绩点:" << GRADE_TO_GPA[minGrade] << endl;
        }
    }
    cout << "\n "; system("pause");
}

//按照序号顺序录入成绩
void InputGrade(IDTYPE courseID) {
    bool isBreak = false;
    //初始化
    for (auto it = CourseMap[courseID].GetCourseStudentID().begin(); it != CourseMap[courseID].GetCourseStudentID().end() && !isBreak; it++) {
        system("cls");
        cout << " ┄┄┄┄┄┄┄┄┄┄┄开┄┄┄┄┄┄┄┄┄┄始┄┄┄┄┄┄┄┄┄┄┄┄录┄┄┄┄┄┄┄┄┄┄┄入┄┄┄┄┄┄┄┄┄┄┄┄" << endl;
        cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
        cout << "  当前课程ID:" << courseID << " "; CourseMap[courseID].Display(); cout << '\n';
        cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
        IDTYPE gradeID = _GET_GRADE_ID(*it, courseID);
        if (GradeMap.find(gradeID) == GradeMap.end()) {    //如果没有保存成绩的类，就创建之
            Grade grade(CourseMap[courseID], *it);
            GradeMap[gradeID] = grade;
        }
        Grade& grade = GradeMap[gradeID];
        isBreak = InputOneGrade(grade);
    }
    cout << " ┄┄┄┄┄┄┄┄┄┄┄完┄┄┄┄┄┄┄┄┄┄成┄┄┄┄┄┄┄┄┄┄┄┄录┄┄┄┄┄┄┄┄┄┄┄入┄┄┄┄┄┄┄┄┄┄┄┄" << endl;

}

//为一个grade录入成绩
bool InputOneGrade(Grade & grade) {
    cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
    cout << "  当前学生ID:" << grade.GetStuID() << "  账户名:" << std::setw(10) << std::left << AccountMap[grade.GetStuID()].GetUserName() << std::right << '\n';
    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
    bool isInput = true;
    if (grade.GetCourseResultType() == grade.GetGradeResult().m_eType) {    //已经被设置过成绩
        char ch;
        bool isInputCorrect = false;    //是否正确输入
        isInput = false;
        cout << ' ';
        grade.DisplayGradeOnly();
        do {
            cout << " 该学生已经录入过成绩，是否重新录入(Y/N):";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cin >> ch;
            switch (ch) {
            case 'Y': case 'y':
                isInputCorrect = true;
                isInput = true;
                break;
            case 'N':case'n':
                isInputCorrect = true;
                isInput = false;
                break;
            default:
                break;
            }
        } while (!isInputCorrect);
    }
    if (isInput) {    //录入成绩
        bool isInputCorrect = false;    //是否正确输入
        switch (grade.GetCourseResultType()) {
        case Result_Percent:    //百分制
            int percent;
            cout << ' ';
            do {
                cout << "输入百分制成绩(成绩范围0-100 -1-返回上一级):";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cin >> percent;
                if (percent == -1)return true;
                if (percent >= 0 && percent <= 100) {
                    isInputCorrect = true;
                    grade.SetGradeResult(RESULT(percent, Result_Percent));
                }
                else {
                    cout << " 输入有误，请重新输入，";
                }
            } while (!isInputCorrect);
            break;
        case Result_Grade:    //等级制
            int GRADE;
            cout << ' ';
            do {
                cout << "输入等级制成绩(-1-返回上一级)\n 0-A+ 1-A 2-A- 3-B+ 4-B 5-B- 6-C+ 7-C 8-C- 9-D+ 10-D 11-F\n:";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cin >> GRADE;
                if (GRADE == -1)return true;
                if (GRADE >= 0 && GRADE < 12) {
                    isInputCorrect = true;
                    grade.SetGradeResult(RESULT(GRADE, Result_Grade));
                }
                else {
                    cout << " 输入有误，请重新输入，";
                }
            } while (!isInputCorrect);
            break;
        case Result_PF:    //通过与不通过
            char ch;
            cout << ' ';
            do {
                cout << "通过/不通过(P-通过 F-不通过 0-返回上一级):";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cin >> ch;
                if (ch == '0')return true;
                switch (ch) {
                case 'P': case 'p':
                    isInputCorrect = true;
                    grade.SetGradeResult(RESULT(PASS, Result_PF));
                    break;
                case 'F':case'f':
                    isInputCorrect = true;
                    grade.SetGradeResult(RESULT(FAIL, Result_PF));
                    break;
                default:
                    cout << " 输入有误，请重新输入，";
                    break;
                }
            } while (!isInputCorrect);
            break;
        }
        cout << " 录入成功!\n" << endl;
    }
    cout << ' '; system("pause");
    return false;
}

//修改某一学生成绩
void ChangeGrade(IDTYPE courseID) {
    while (true) {
        system("cls");
        cout << " ┄┄┄┄┄┄┄┄┄┄┄修┄┄┄┄┄┄┄┄┄┄改┄┄┄┄┄┄┄┄┄┄┄┄成┄┄┄┄┄┄┄┄┄┄┄绩┄┄┄┄┄┄┄┄┄┄┄┄" << endl;
        cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
        cout << "  当前课程ID:" << courseID << " "; CourseMap[courseID].Display(); cout << '\n';
        cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
        cout << " ┄┄┄┄┄┄┄┄┄┄┄选┄┄┄┄┄┄┄┄┄┄择┄┄┄┄┄┄┄┄┄┄┄┄学┄┄┄┄┄┄┄┄┄┄┄生┄┄┄┄┄┄┄┄┄┄┄┄" << endl;
        //选择学生
        for (auto it = CourseMap[courseID].GetCourseStudentID().begin(); it != CourseMap[courseID].GetCourseStudentID().end(); it++) {
            cout << " 学生ID：" << *it << "  ";
            AccountMap[*it].Display();
            cout << endl;
        }
        cout << " ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄" << endl;
        IDTYPE stuID;
        while (true) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << " 输入要选择的学生账户ID(0-返回上一级):";
            cin >> stuID;
            if (stuID == 0) {
                return;
            }
            if (AccountMap.find(stuID) == AccountMap.end() || AccountMap[stuID].GetAccountType() != Account_Student || !CourseMap[courseID].IsStudentInSet(stuID)) {
                cout << " 输入有误，请重新输入，";
            }
            else {
                //进入修改
                system("cls");
                cout << " ┄┄┄┄┄┄┄┄┄┄┄修┄┄┄┄┄┄┄┄┄┄改┄┄┄┄┄┄┄┄┄┄┄┄成┄┄┄┄┄┄┄┄┄┄┄绩┄┄┄┄┄┄┄┄┄┄┄┄" << endl;
                cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
                cout << "  当前课程ID:" << courseID << " "; CourseMap[courseID].Display(); cout << '\n';
                cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
                IDTYPE gradeID = _GET_GRADE_ID(stuID, courseID);
                if (GradeMap.find(gradeID) == GradeMap.end()) {    //如果没有保存成绩的类，就创建之
                    Grade grade(CourseMap[courseID], stuID);
                    GradeMap[gradeID] = grade;
                }
                Grade& grade = GradeMap[gradeID];
                InputOneGrade(grade);
                break;
            }
        }
    }
}

//删除/清空学生成绩
void DelGrade(IDTYPE courseID) {
    while (true) {
        //初始化
        system("cls");
        ShowHead();
        cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
        cout << "  当前课程ID:" << courseID << " "; CourseMap[courseID].Display(); cout << '\n';
        cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
        cout << " ┄┄┄┄┄┄┄┄┄┄┄删┄┄┄┄┄┄┄┄┄┄除┄┄┄┄┄┄┄┄┄┄┄┄成┄┄┄┄┄┄┄┄┄┄┄绩┄┄┄┄┄┄┄┄┄┄┄┄" << endl;
        //按序号排列学生
        for (auto it = CourseMap[courseID].GetCourseStudentID().begin(); it != CourseMap[courseID].GetCourseStudentID().end(); it++) {
            IDTYPE gradeID = _GET_GRADE_ID(*it, courseID);
            if (GradeMap.find(gradeID) == GradeMap.end()) {    //如果没有保存成绩的类，就创建之
                Grade grade(CourseMap[courseID], *it);
                GradeMap[gradeID] = grade;
            }
            const Grade& grade = GradeMap[gradeID];
            cout << " 学生ID:" << *it << "  账户名:" << std::setw(10) << std::left << AccountMap[*it].GetUserName() << std::right;
            cout << ' '; grade.DisplayGradeOnly(); cout << endl;
        }
        cout << " ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄" << endl;
        IDTYPE stuID;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << " 输入要选择的学生账户ID(0-返回上一级):";
        cin >> stuID;
        if (stuID == 0) {
            return;
        }
        while (AccountMap.find(stuID) == AccountMap.end() || AccountMap[stuID].GetAccountType() != Account_Student || !CourseMap[courseID].IsStudentInSet(stuID)) {
            cout << " 输入有误，请重新输入，输入要选择的学生账户ID(0-返回上一级):";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cin >> stuID;
            if (stuID == 0) {
                return;
            }
        }
        //删除成绩
        GradeMap.erase(_GET_GRADE_ID(stuID, courseID));
        cout << " 删除成功!\n" << endl;
        cout << ' '; system("pause");
    }
}

//将课程中所有学生成绩降序排列，其中未录入的排在最后
void SortAndShow(IDTYPE courseID) {
    std::set<Grade, std::greater<const Grade&>>sorted;
    for (auto it = CourseMap[courseID].GetCourseStudentID().begin(); it != CourseMap[courseID].GetCourseStudentID().end(); it++) {
        IDTYPE gradeID = _GET_GRADE_ID(*it, courseID);
        if (GradeMap.find(gradeID) == GradeMap.end()) {    //如果没有保存成绩的类，就创建之
            Grade grade(CourseMap[courseID], *it);
            GradeMap[gradeID] = grade;
        }
        sorted.insert(GradeMap[gradeID]);
    }
    double sumResult = 0;
    int count = 0;
    double maxResult = -1;
    double minResult = INT_MAX;
    bool hasGrade[12] = { false,false,false,false,false,false,false,false,false,false,false,false };
    //初始化
    system("cls");
    ShowHead();
    cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n";
    cout << "  当前课程ID:" << courseID << " "; CourseMap[courseID].Display(); cout << '\n';
    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
    cout << " ┄┄┄┄┄┄┄┄┄┄┄成┄┄┄┄┄┄┄┄┄┄绩┄┄┄┄┄┄┄┄┄┄┄┄降┄┄┄┄┄┄┄┄┄┄┄序┄┄┄┄┄┄┄┄┄┄┄┄" << endl;
    //按序号排列学生
    for (auto it = sorted.begin(); it != sorted.end(); it++) {

        const Grade& grade = *it;
        cout << " 学生ID:" << it->GetStuID() << "  账户名:" << std::setw(10) << std::left << AccountMap[it->GetStuID()].GetUserName() << std::right;
        cout << ' '; grade.DisplayGradeOnly(); cout << endl;
        assert(grade.GetGradeResult().m_eType == Result_None || CourseMap[courseID].GetCourseResultType() == grade.GetGradeResult().m_eType);
        switch (CourseMap[courseID].GetCourseResultType()) {
        case Result_None:
            break;
        case Result_Percent:
            if (grade.GetGradeResult().m_eType == Result_Percent) {
                sumResult += grade.GetGradeResult().m_uResult.Percent;
                count++;
                maxResult = (grade.GetGradeResult().m_uResult.Percent > maxResult ? grade.GetGradeResult().m_uResult.Percent : maxResult);
                minResult = (grade.GetGradeResult().m_uResult.Percent < minResult ? grade.GetGradeResult().m_uResult.Percent : minResult);
            }
            break;
        case Result_Grade:
            if (grade.GetGradeResult().m_eType == Result_Grade) {
                sumResult += GRADE_TO_GPA[grade.GetGradeResult().m_uResult.GPA];
                count++;
                hasGrade[grade.GetGradeResult().m_uResult.GPA] = true;
            }
            break;
        case Result_PF:
            break;
        }
    }
    cout << " ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄" << endl;
    if (count > 0) {    //有已录入的学生
        if (CourseMap[courseID].GetCourseResultType() == Result_Percent) {    //百分制
            cout << " 平均分:" << sumResult / count << "  最高分:" << maxResult << "  最低分:" << minResult << endl;
        }
        else if (CourseMap[courseID].GetCourseResultType() == Result_Grade) {
            int maxGrade = -1, minGrade = 12;
            for (int i = 0; i < 12; i++) {
                if (hasGrade[i])
                    maxGrade = i;
            }
            for (int i = 12 - 1; i >= 0; i--) {
                if (hasGrade[i])
                    minGrade = i;
            }
            cout << " 平均绩点:" << sumResult / count << "  最高绩点:" << GRADE_TO_GPA[maxGrade] << "  最低绩点:" << GRADE_TO_GPA[minGrade] << endl;
        }
    }
    cout << "\n "; system("pause");
}

//写二进制文件，保存全部信息
void SaveFile(std::ofstream& File) {
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

//读二进制文件，读取全部信息
void LoadFile(std::ifstream& File) {
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
        cout << " Error: 数据文件未能成功打开" << endl;
        system("pause");
        exit(0);
    }
}


