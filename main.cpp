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

//ȫ��״̬��
ACCOUNT_TYPE nowType = Account_None;
Account *nowAccount = nullptr;
std::map<IDTYPE, Account>AccountMap;
std::map<IDTYPE, Course>CourseMap;
std::map<IDTYPE, Grade>GradeMap;
//�Ƿ��˳���������
bool isExit = false;

const char* FileName = "alldata.bin";
const int WINDOWS_MAX_WIDTH = 80;
const int WINDOWS_LEFT_WIDTH = 25;

//ѡ��˵�
void ShowHead(), EnterMainMenu(), EnterAdminMenu(), EnterStuMenu(), EnterTeaMenu();

//����Ա�˵�����ģ��
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
//ѡ��ģ��
void ChooseCourseOne();
void ChooseCourseFile();
//ѧ���˵�����ģ��
void ShowStuGrade(Account&);
//��ʦ�˵�����ģ��
void CreateCourse();
bool DelCourse();
void EnterCourseMenu();
//�γ̲˵�����ģ��


//��������ģ��
void Login();    //��½
void SaveFile(), LoadFile();    //�ļ�����


int main() {
#if _INIT
    Account master;
    master.Init("A", "123456", Account_Administrator);
    AccountMap[master.GetID()] = master;
#else
    LoadFile();
#endif
    //��½
    while (!isExit) {
        Login();
        if (isExit) {
            SaveFile();
            return 0;
        }
        //������
        EnterMainMenu();
    }

    SaveFile();
    return 0;
}

void ShowHead() {
    cout << "������������������������������������������������������������������������������������������������������������������������������������\n";
    cout << "��                                                                ��\n";
    cout << "��                   ѧ���ɼ�����ϵͳ Version0.3                  ��\n";
    cout << "��                                                                ��\n";
    cout << "������������������������������������������������������������������������������������������������������������������������������������" << endl;
    return;
}

//����Ա���˵�
void EnterAdminMenu() {
    int N;
    //�˵�ѭ��
    while (!isExit) {
        system("cls");
        ShowHead();
        cout << "������������������������������������������������������������������������������������������������������������������������������������\n";
        cout << "     "; nowAccount->Display(); cout << '\n';
        cout << "������������������������������������������������������������������������������������������������������������������������������������" << endl;
        cout << "������������������������������������������������������������������������������������������������������������������������������������\n";
        cout << "��               1. �����˻�                                      ��\n";
        cout << "��               2. ɾ���˻�                                      ��\n";
        cout << "��               3. �޸��˻�����                                  ��\n";
        cout << "��               4. �鿴�����˻�                                  ��\n";
        cout << "��               5. �鿴��ʦ��Ϣ                                  ��\n";
        cout << "��               6. �鿴ѧ����Ϣ                                  ��\n";
        cout << "��               7. �鿴�γ���Ϣ                                  ��\n";
        cout << "��               8. ���ѡ��ѧ���б�                              ��\n";
        cout << "��               9. �˳���¼(������һ��)                          ��\n";
        cout << "��               0. �˳�����                                      ��\n";
        cout << "������������������������������������������������������������������������������������������������������������������������������������" << endl;
        //����ѭ��
        do {
            bool isBreak = false;
            N = -1;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << " ��������ѡ�˵���ţ�";
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
                cout << "\n �鿴��ϸ��Ϣ��ת�� ���鿴��ʦ/ѧ����Ϣ�� �˵�\n" << endl;
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
                cout << " ������������������,";
                break;
            }
        } while (N < 0 || N > 9);
    }
}

void EnterStuMenu() {
    int N;
    //�˵�ѭ��
    while (!isExit) {
        system("cls");
        ShowHead();
        cout << "������������������������������������������������������������������������������������������������������������������������������������\n";
        cout << "     "; nowAccount->Display(); cout << '\n';
        cout << "������������������������������������������������������������������������������������������������������������������������������������" << endl;
        cout << "������������������������������������������������������������������������������������������������������������������������������������\n";
        cout << "��               1. �޸��˻�����                                  ��\n";
        cout << "��               2. �鿴�γ���ɼ�                                ��\n";
        cout << "��               9. �˳���¼(������һ��)                          ��\n";
        cout << "��               0. �˳�����                                      ��\n";
        cout << "������������������������������������������������������������������������������������������������������������������������������������" << endl;
        //����ѭ��
        do {
            N = -1;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << " ��������ѡ�˵���ţ�";
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
                cout << " ������������������,";
                break;
            }
        } while (N < 0 || N > 9 || (N > 2 && N < 9));
    }
}
void EnterTeaMenu() {
    int N;
    //�˵�ѭ��
    while (!isExit) {
        system("cls");
        ShowHead();
        cout << "������������������������������������������������������������������������������������������������������������������������������������\n";
        cout << "     "; nowAccount->Display(); cout << '\n';
        cout << "������������������������������������������������������������������������������������������������������������������������������������" << endl;
        cout << "������������������������������������������������������������������������������������������������������������������������������������\n";
        cout << "��               1. �޸��˻�����                                  ��\n";
        cout << "��               2. �鿴�γ���Ǽǳɼ�                            ��\n";
        cout << "��               3. ����γ�                                      ��\n";
        cout << "��               4. ɾ���γ�                                      ��\n";
        cout << "��               9. �˳���¼(������һ��)                          ��\n";
        cout << "��               0. �˳�����                                      ��\n";
        cout << "������������������������������������������������������������������������������������������������������������������������������������" << endl;
        //����ѭ��
        do {
            bool isBreak = false;
            N = -1;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << " ��������ѡ�˵���ţ�";
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
                cout << " ������������������,";
                break;
            }
        } while (N < 0 || N > 9 || (N > 2 && N < 9));
    }
}

void EnterMainMenu() {
    //�����Ӧ�˵�
    switch (nowType) {
    case Account_None:
        assert(nowType != Account_None);
        break;
    case Account_Student:    //ѧ���˵�
        EnterStuMenu();
        break;
    case Account_Teacher:    //��ʦ�˵�
        EnterTeaMenu();
        break;
    case Account_Administrator:    //����Ա�˵�
        EnterAdminMenu();
        break;
    }
}

void Login() {
    std::string username, pwd;
    char ch;
    bool isOK = false;
    //���벿��
    system("cls");
    ShowHead();
    cout << " �����������������������������������������������ǩ�������������������������½������������������������������������������������" << endl;
    while (!isOK) {
        cout << " �������û���:";
        cin >> username;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << " ����������:";
        cin >> pwd;
        //���
        auto it = std::find_if(AccountMap.begin(), AccountMap.end(), [&](std::pair<IDTYPE, Account> account)->bool {return username == account.second.GetUserName(); });
        if (it == AccountMap.end()) {
            bool isInputCorrect = false;    //�Ƿ���ȷ����
            do {
                cout << " �û�����������������Ƿ���������(Y/N):";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
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
            cout << " ��½�ɹ�!" << endl;
            nowAccount = &(it->second);
            nowType = nowAccount->GetAccountType();
            isOK = true;
        }
        else {
            bool isInputCorrect = false;    //�Ƿ���ȷ����
            do {
                cout << " �û�����������������Ƿ���������(Y/N):";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
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

void CreateAccount() {
    Account account;
    std::string username, pwd, pwdChk;
    int type;
    //��ʼ��
    system("cls");
    ShowHead();
    cout << " �����������������������������������������������������������������������ʩ�����������������������������������������������" << endl;
    //��ѭ��
    while (true) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << " ������Ҫ�������˻�����(1-ѧ�� 2-��ʦ 0-������һ��):";
        cin >> type;
        if (type == 0)return;
        while (type != 1 && type != 2) {
            cout << " ������������������(1-ѧ�� 2-��ʦ 0-������һ��):";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cin >> type;
            if (type == 0)return;
        }
        cout << " �������˻���(0-������һ��):";
        cin >> username;
        if (username == "0")return;
        do {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << " �������ʼ����(0-������һ��):";
            cin >> pwd;
            if (pwd == "0")return;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << " ���ٴ������ʼ����:";
            cin >> pwdChk;
            if (pwdChk != pwd) {
                cout << " �����������벻һ�£�";
            }
        } while (pwdChk != pwd);
        account.Init(username, pwd, (ACCOUNT_TYPE)type);
        AccountMap[account.GetID()] = account;
    }
}
void DelAccount() {
    IDTYPE id;
    //��ʼ��
    system("cls");
    ShowAllAccount();
    cout << " ����������������������ɾ�����������������������������������������������ʩ�����������������������������������������������" << endl;
    //��ѭ��
    while (true) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << " ����Ҫɾ�����˻�ID(����0������һ��):";
        cin >> id;
        if (id == 0) {
            return;
        }
        if (AccountMap.find(id) == AccountMap.end()) {
            cout << " �����������������룬";
        }
        else {
            switch (AccountMap[id].GetAccountType()) {
            case Account_Student:
                if (!AccountMap[id].GetAccountCourseID().empty()) {
                    for (auto it = AccountMap[id].GetAccountCourseID().begin(); it != AccountMap[id].GetAccountCourseID().end(); it++) {
                        GradeMap.erase(AccountMap[id] + *it);  //ɾ����Ӧ�ĳɼ�
                        CourseMap[*it].DelStudentOutSet(AccountMap[id].GetID());   //ɾ���γ��еļ�¼
                    }
                }
                AccountMap.erase(id);
                cout << " �˻�" << id << "�ѱ�ɾ��" << endl;
                break;
            case Account_Teacher:
                if (!AccountMap[id].GetAccountCourseID().empty()) {
                    //ɾ������Ŀγ�
                    for (auto it = AccountMap[id].GetAccountCourseID().begin(); it != AccountMap[id].GetAccountCourseID().end(); it++) {
                        //���Ҷ�Ӧ�γ��е�ѧ����ɾ��Grade
                        for (auto stu = CourseMap[*it].GetCourseStudentID().begin(); stu != CourseMap[*it].GetCourseStudentID().end(); stu++) {
                            GradeMap.erase(_GET_GRADE_ID(*stu, *it));  //ɾ����Ӧ�ĳɼ�
                        }
                        CourseMap.erase(*it);   //ɾ���γ��еļ�¼
                    }
                }
                AccountMap.erase(id);
                cout << " �˻�" << id << "�ѱ�ɾ��" << endl;
                break;
            case Account_Administrator:
                cout << " ��ֹɾ������Ա�˻������������룬";
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
    //��ʼ��
    system("cls");
    ShowHead();
    //����Ա��������
    if (nowType == Account_Administrator) {
        cout << " �����������������������ܩ��������������������멨�����������������������ة����������������������é�����������������������\n" << endl;
        ShowAllAccount();
        //��ѭ��
        while (true) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << " ����Ҫ����������˻�ID(����0������һ��):";
            cin >> id;
            if (id == 0)return;
            if (AccountMap.find(id) == AccountMap.end()) {
                cout << " �����������������룬";
            }
            else {
                std::string pwd, pwdChk;
                do {
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    cout << " ������������(����0������һ��):";
                    cin >> pwd;
                    if (pwd == "0")return;
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    cout << " ���ٴ�����������:";
                    cin >> pwdChk;
                    if (pwdChk != pwd) {
                        cout << " �����������벻һ�£�";
                    }
                } while (pwdChk != pwd);
                AccountMap[id].ResetPwd(pwd, *nowAccount);
                cout << " �˻�" << id << "�����޸ĳɹ�" << endl;
            }
        }
    }
    //��ͨ�˻��޸�����
    else {
        bool isOK = false;
        assert(nowType != Account_None);
        cout << " �����������������������ܩ��������������������멨�����������������������ީ����������������������ĩ�����������������������\n" << endl;
        std::string oldpwd, newpwd, pwdChk;
        do {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << " �����������(����0������һ��):";
            cin >> oldpwd;
            if (oldpwd == "0")return;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << " ������������(����0������һ��):";
            cin >> newpwd;
            if (newpwd == "0")return;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << " ���ٴ�����������:";
            cin >> pwdChk;
            if (pwdChk != newpwd) {
                cout << " �����������벻һ�£�";
            }
            else if (nowAccount->ChangePwd(oldpwd, newpwd)) {
                cout << " �����޸ĳɹ�" << endl;
                isOK = true;
            }
            else {
                cout << " �������������";
            }
        } while (!isOK);
    }
}
void ShowAllAccount() {
    //��ʼ��
    system("cls");
    ShowHead();
    cout << " ���������������������������������������������Щ������������������������ʩ�����������������������������������������������" << endl;
    //��ѭ��
    for (auto it = AccountMap.begin(); it != AccountMap.end(); it++) {
        cout << " �˻�ID " << it->first << "  ";
        it->second.Display();
        cout << endl;
    }
}
void ShowAllTeacher() {
    //��ʼ��
    system("cls");
    ShowHead();
    cout << " �����������������������̩�������������������ʦ�������������������������ʩ�����������������������������������������������" << endl;
    //��ʾ������Ϣ
    for (auto it = AccountMap.begin(); it != AccountMap.end(); it++) {
        if (it->second.GetAccountType() == Account_Teacher) {
            cout << " �˻�ID " << it->first << "  ";
            it->second.Display();
            cout << endl;
        }
    }
}
bool ShowOneTeacher() {
    return false;
}
void ShowAllStudent() {
    //��ʼ��
    system("cls");
    ShowHead();
    cout << " ����������������������ѧ�����������������������������������������������ʩ�����������������������������������������������" << endl;
    //��ʾ������Ϣ
    for (auto it = AccountMap.begin(); it != AccountMap.end(); it++) {
        if (it->second.GetAccountType() == Account_Student) {
            cout << " �˻�ID " << it->first << "  ";
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
        cout << " ����Ҫ�鿴��ѧ���˻�ID(����0������һ��):";
        cin >> id;
        if (id == 0) {
            return true;
        }
        if (AccountMap.find(id) == AccountMap.end() || AccountMap[id].GetAccountType() != Account_Student) {
            cout << " �����������������룬";
        }
        else {
            ShowStuGrade(AccountMap[id]);
            break;
        }
    }
    return false;
}
//��ʾȫ���γ�
void ShowAllCourse() {
    //��ʼ��
    system("cls");
    ShowHead();
    cout << " ���������������������������������������������Щ������������������������Ω����������������������̩�����������������������" << endl;
    //��ʾ������Ϣ
    for (auto it = CourseMap.begin(); it != CourseMap.end(); it++) {
        cout << " �γ�ID " << it->first << "  ";
        it->second.Display();
        cout << endl;
    }
}
//��ʾ��ʦ��tea����Ŀγ�
void ShowAllCourse(Account& tea) {
    assert(tea.GetAccountType() == Account_Teacher);
    //��ʼ��
    system("cls");
    ShowHead();
    cout << " ���������������������������������������������詨�����������������������Ω����������������������̩�����������������������" << endl;
    //��ʾ������Ϣ
    for (auto it = tea.GetAccountCourseID().begin(); it != tea.GetAccountCourseID().end(); it++) {
        cout << " �γ�ID " << *it << "  ";
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
    //�˵�ѭ��
    while (true) {
        bool isInputError;
        system("cls");
        ShowHead();
        cout << " ����������������������������������������������ѡ���������������������������Ω�����������������������������������������������" << endl;
        cout << "������������������������������������������������������������������������������������������������������������������������������������\n";
        cout << "��               1. �ֶ����                                      ��\n";
        cout << "��               2. �ļ�����                                      ��\n";
        cout << "��               0. ������һ��                                    ��\n";
        cout << "������������������������������������������������������������������������������������������������������������������������������������" << endl;
        //����ѭ��
        do {
            isInputError = false;
            N = -1;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << " ��������ѡ�˵���ţ�";
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
                cout << " ������������������,";
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
        cout << " ��������Ҫѡ���ѧ��ID(0-������һ��):";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cin >> StuID;
        if (StuID == 0)return;
        while (AccountMap.find(StuID) == AccountMap.end()) {
            cout << " ��������������������Ҫѡ���ѧ��ID(0-������һ��):";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cin >> StuID;
            if (StuID == 0)return;
        }
        auto *nowStu = &AccountMap[StuID];
        bool isBreak = false;
        while (!isBreak) {
            ShowAllCourse();
            cout << "������������������������������������������������������������������������������������������������������������������������������������\n";
            cout << "  ��ǰѡ��ѧ��ID:" << StuID << "  �˻���:" << nowStu->GetUserName() << '\n';
            cout << "������������������������������������������������������������������������������������������������������������������������������������" << endl;
            do {
                cout << " ��������Ҫѡ��Ŀγ�ID(0-������һ��):";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cin >> CourseID;
                if (CourseID == 0) {
                    isBreak = true;
                    break;
                }
                while (CourseMap.find(CourseID) == CourseMap.end()) {
                    cout << " ��������������������Ҫѡ��Ŀγ�ID(0-������һ��):";
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
                cout << "ѡ�γɹ�" << endl;
            } while (!isBreak);
        }
    }
}
void ChooseCourseFile() {
}
void ShowStuGrade(Account& stu) {
    assert(stu.GetAccountType() == Account_Student);
    double sumResult = 0;    //ͳһת��Ϊ���㴦��
    int allPoint = 0;    //��ѧ��
    //��ʼ��
    system("cls");
    ShowHead();
    cout << "������������������������������������������������������������������������������������������������������������������������������������\n";
    cout << "  ��ǰѧ��ID:" << stu.GetID() << "  �˻���:" << stu.GetUserName() << '\n';
    cout << "������������������������������������������������������������������������������������������������������������������������������������" << endl;
    cout << " �����������������������Ω��������������������̩������������������������ɩ�����������������������������������������������" << endl;
    for (auto it = stu.GetAccountCourseID().begin(); it != stu.GetAccountCourseID().end(); it++) {
        assert(GradeMap.find(*it + stu) != GradeMap.end());
        const Grade& grade = GradeMap[*it + stu];
        cout << ' '; grade.Display(); cout << endl;
        sumResult += grade.Result2Pair().second * grade.Result2Pair().first;
        allPoint += grade.Result2Pair().first;
    }
    if (allPoint == 0)
        cout << " ƽ������Ϊ: NaN" << endl;
    else
        cout << " ƽ������Ϊ:" << sumResult / allPoint << endl;
    cout << "\n "; system("pause");
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

bool DelCourse() {

    IDTYPE id;
    while (true) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << " ����Ҫ�鿴��ѧ���˻�ID(����0������һ��):";
        cin >> id;
        if (id == 0) {
            return true;
        }
        if (AccountMap.find(id) == AccountMap.end() || AccountMap[id].GetAccountType() != Account_Student) {
            cout << " �����������������룬";
        }
        else {
            ShowStuGrade(AccountMap[id]);
            break;
        }
    }
    return false;
    //ɾ������Ŀγ�
    for (auto it = AccountMap[id].GetAccountCourseID().begin(); it != AccountMap[id].GetAccountCourseID().end(); it++) {
        //���Ҷ�Ӧ�γ��е�ѧ����ɾ��Grade
        for (auto stu = CourseMap[*it].GetCourseStudentID().begin(); stu != CourseMap[*it].GetCourseStudentID().end(); stu++) {
            GradeMap.erase(_GET_GRADE_ID(*stu, *it));  //ɾ����Ӧ�ĳɼ�
        }
        CourseMap.erase(*it);   //ɾ���γ��еļ�¼
    }
}

void EnterCourseMenu() {
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


