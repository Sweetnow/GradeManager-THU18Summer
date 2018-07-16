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

//ȫ��״̬��
ACCOUNT_TYPE nowType = Account_None;
Account *nowAccount = nullptr;
std::map<IDTYPE, Account>AccountMap;
std::map<IDTYPE, Course>CourseMap;
std::map<IDTYPE, Grade>GradeMap;
//�Ƿ��˳���������
bool isExit = false;

//�ļ�
const char* FileName = "alldata.bin";

//ѡ��˵�

void ShowHead(), EnterMainMenu(), EnterAdminMenu(), EnterStuMenu(), EnterTeaMenu();

//����Ա�˵�����ģ��

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

//ѡ��ģ��

void ChooseCourse();

//ѧ���˵�����ģ��

void ShowStuGrade(Account&);

//��ʦ�˵�����ģ��

bool CreateCourse();
bool DelCourse();
void EnterCourseMenu(IDTYPE);

//�γ̲˵�����ģ��

void ShowAllStuInCourse(IDTYPE);
void InputGrade(IDTYPE);
bool InputOneGrade(Grade&);

void ChangeGrade(IDTYPE);
void DelGrade(IDTYPE);
void SortAndShow(IDTYPE);

//��������ģ��

void Login();    //��½
void SaveFile(std::ofstream&), LoadFile(std::ifstream&);    //�ļ�����


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
    //��½
    while (!isExit) {
        Login();
        if (isExit) {
            break;
        }
        //������
        EnterMainMenu();
    }
    std::ofstream oFile(FileName, std::ios_base::binary);
    if (oFile.is_open())
        SaveFile(oFile);
    else {
        cout << " Error: �����ļ�δ�ܳɹ���" << endl;
        system("pause");
        exit(0);
    }
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
            cout << " ��������ѡ�˵����:";
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
                cout << " ������������������,";
                break;
            }
        } while (N < 0 || N > 9);
    }
}

//ѧ�����˵�
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
            cout << " ��������ѡ�˵����:";
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

//��ʦ���˵�
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
            cout << " ��������ѡ�˵����:";
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
                cout << " ������������������,";
                break;
            }
        } while (N < 0 || N > 9 || (N > 4 && N < 9));
    }
}

//�����Ӧ�˵�
void EnterMainMenu() {
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

//��½�߼������
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
                cout << " �û����������������!�Ƿ���������(Y/N):";
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
                cout << " �û����������������!�Ƿ���������(Y/N):";
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

//�����˻�
void CreateAccount() {
    std::string username, pwd, pwdChk;
    //��ʼ��
    system("cls");
    ShowHead();
    cout << " �����������������������������������������������������������������������ʩ�����������������������������������������������" << endl;
    //��ѭ��
    while (true) {
        int type;
        bool sameName;
        Account account;
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
                cout << " ���˻����ѱ�ռ�ã������������˻���(0-������һ��):";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cin >> username;
                if (username == "0")return;
            }
        } while (sameName);

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
                cout << " �����������벻һ��!";
            }
        } while (pwdChk != pwd);
        account.Init(username, pwd, (ACCOUNT_TYPE)type);
        AccountMap[account.GetID()] = account;
        cout << " �����˻��ɹ�!\n" << endl;
    }
}

//ɾ���˻�
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
                cout << " �˻�" << id << "�ѱ�ɾ��\n" << endl;
                break;
            case Account_Teacher:
                if (!AccountMap[id].GetAccountCourseID().empty()) {
                    //ɾ������Ŀγ�
                    for (auto it = AccountMap[id].GetAccountCourseID().begin(); it != AccountMap[id].GetAccountCourseID().end(); it++) {
                        //���Ҷ�Ӧ�γ��е�ѧ����ɾ��Grade
                        for (auto stu = CourseMap[*it].GetCourseStudentID().begin(); stu != CourseMap[*it].GetCourseStudentID().end(); stu++) {
                            GradeMap.erase(_GET_GRADE_ID(*stu, *it));  //ɾ����Ӧ�ĳɼ�
                            AccountMap[*stu].DelCourseOutSet(*it);    //ɾ��ѧ����set�еļ�¼
                        }
                        CourseMap.erase(*it);   //ɾ���γ��еļ�¼
                    }
                }
                AccountMap.erase(id);
                cout << " �˻�" << id << "�ѱ�ɾ��\n" << endl;
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

//����Ա�������룬��ͨ�û��޸�����
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
                        cout << " �����������벻һ��!";
                    }
                } while (pwdChk != pwd);
                AccountMap[id].ResetPwd(pwd, *nowAccount);
                cout << " �˻�" << id << "�����޸ĳɹ�\n" << endl;
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
                cout << " �����������벻һ��!";
            }
            else if (nowAccount->ChangePwd(oldpwd, newpwd)) {
                cout << " �����޸ĳɹ�\n" << endl;
                isOK = true;
            }
            else {
                cout << " �������������!";
            }
        } while (!isOK);
    }
}

//��ʾ�����˻�������Ϣ
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
    cout << " ��������������������������������������������������������������������������������������������������������������������������������" << endl;
}

//��ʾ���н�ʦ�˻�������Ϣ
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
    cout << " ��������������������������������������������������������������������������������������������������������������������������������" << endl;
}

//�鿴ĳһ��ʦ�˻���ϸ��Ϣ
bool ShowOneTeacher() {
    IDTYPE id;
    while (true) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << " ����Ҫ�鿴�Ľ�ʦ�˻�ID(0-������һ��):";
        cin >> id;
        if (id == 0) {
            return true;
        }
        if (AccountMap.find(id) == AccountMap.end() || AccountMap[id].GetAccountType() != Account_Teacher) {
            cout << " �����������������룬";
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

//��ʾ����ѧ���˻�������Ϣ
bool ShowAllStudent(bool justShow) {
    //��ʼ��
    system("cls");
    ShowHead();
    cout << " ����������������������ѧ�����������������������������������������������ʩ�����������������������������������������������" << endl;
    //��ʾ������Ϣ
    for (auto it = AccountMap.begin(); it != AccountMap.end(); it++) {
        if (it->second.GetAccountType() == Account_Student) {
            cout << " �˻�ID:" << it->first << "  ";
            it->second.Display();
            cout << endl;
        }
    }
    cout << " ��������������������������������������������������������������������������������������������������������������������������������" << endl;
    if (!justShow) {
        bool isInputCorrect = false;
        int N;
        do {
            cout << " ѡ��鿴��Ŀ(1-����ѧ���������� 2-����ѧ���ɼ� 0-������һ��):";
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

//�鿴ĳһѧ���˻���ϸ��Ϣ
bool ShowOneStudent() {
    IDTYPE id;
    while (true) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << " ����Ҫ�鿴��ѧ���˻�ID(0-������һ��):";
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
        cout << " �γ�ID:" << it->first << "  ";
        it->second.Display();
        cout << endl;
    }
    cout << " ��������������������������������������������������������������������������������������������������������������������������������" << endl;
}

//��ʾ��ʦ��tea����Ŀγ�
void ShowAllCourse(Account& tea) {
    assert(tea.GetAccountType() == Account_Teacher);
    //��ʼ��
    system("cls");
    ShowHead();
    cout << "������������������������������������������������������������������������������������������������������������������������������������\n";
    cout << "  ��ǰ��ʦID:" << tea.GetID() << "  �˻���:" << tea.GetUserName() << '\n';
    cout << "������������������������������������������������������������������������������������������������������������������������������������" << endl;
    cout << " ���������������������������������������������詨�����������������������Ω����������������������̩�����������������������" << endl;
    //��ʾ������Ϣ
    for (auto it = tea.GetAccountCourseID().begin(); it != tea.GetAccountCourseID().end(); it++) {
        cout << " �γ�ID:" << *it << "  ";
        CourseMap[*it].Display();
        cout << endl;
    }
    cout << " ��������������������������������������������������������������������������������������������������������������������������������" << endl;
}

//�鿴ĳһ�γ���ϸ��Ϣ
bool ShowOneCourse() {
    IDTYPE id;
    while (true) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << " ����Ҫ�鿴�Ŀγ�ID(0-������һ��):";
        cin >> id;
        if (id == 0) {
            return true;
        }
        if (CourseMap.find(id) == CourseMap.end()) {
            cout << " �����������������룬";
        }
        else {
            EnterCourseMenu(id);
            break;
        }
    }
    return false;
}

//�鿴tea�����ĳһ�γ���ϸ��Ϣ
bool ShowOneCourse(Account& tea) {
    IDTYPE id;
    while (true) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << " ����Ҫ�鿴�Ŀγ�ID(0-������һ��):";
        cin >> id;
        if (id == 0) {
            return true;
        }
        if (CourseMap.find(id) == CourseMap.end() || !tea.IsCourseInSet(id)) {
            cout << " �����������������룬";
        }
        else {
            EnterCourseMenu(id);
            break;
        }
    }
    return false;
}

//��������ѧ�����ܳɼ�����ʾ������ת��ΪGPA������δС�����6λ��
void SortAll() {
    int allstuPoint = 0;
    double allstuResult = 0;
    system("cls");
    ShowHead();
    cout << " �����������������������������������������������������������������������ũ�����������������������������������������������" << endl;
    std::vector<RESULT_FOR_SORT>sorted;
    sorted.reserve(AccountMap.size());    //���þ�����
    for (auto stu = AccountMap.begin(); stu != AccountMap.end(); stu++) {
        //����ÿ��ѧ���ļ���
        if (stu->second.GetAccountType() == Account_Student) {
            double sumResult = 0;    //ͳһת��Ϊ���㴦��
            int allPoint = 0;    //��ѧ��
            for (auto it = stu->second.GetAccountCourseID().begin(); it != stu->second.GetAccountCourseID().end(); it++) {
                if (GradeMap.find(*it + stu->second) == GradeMap.end()) {    //���û�б���ɼ����࣬�ʹ���֮
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
        cout << ' ' << std::setw(3) << count++ << "  ѧ��ID:" << it->stuID << "  �˻���:" << std::setw(10) << std::left << AccountMap[it->stuID].GetUserName() << std::right;
        if (it->allPoint == 0)
            cout << " ƽ������Ϊ: NaN" << endl;
        else {
            cout << " ƽ������Ϊ:" << it->sumResult / it->allPoint << endl;
            allstuPoint += it->allPoint;
            allstuResult += it->sumResult;
        }
    }
    cout << " ��������������������������������������������������������������������������������������������������������������������������������" << endl;
    if (allstuPoint == 0)
        cout << " ����ѧ��ƽ������Ϊ: NaN" << endl;
    else
        cout << " ����ѧ��ƽ������Ϊ:" << allstuResult / allstuPoint << '\n' << endl;
    cout << ' '; system("pause");
}


//Ϊѧ��ѡ��(��һ���)
void ChooseCourse() {
    //��ѭ��
    while (true) {
        //ȷ��ѧ��
        bool isStuSelect = false, isCourseSelect = false;
        IDTYPE StuID, CourseID;
        ShowAllStudent(true);
        cout << " ��������������������������������������������ʼ������������������������ѡ�����������������������Ω�����������������������" << endl;
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
        //ȷ���γ�
        bool isBreak = false;
        while (!isBreak) {
            //��ʼ��
            system("cls");

            cout << " ��������������������������������������������ʼ������������������������ѡ�����������������������Ω�����������������������" << endl;
            //��ʾ������Ϣ
            for (auto it = CourseMap.begin(); it != CourseMap.end(); it++) {
                if (!nowStu->IsCourseInSet(it->first)) {
                    cout << " �γ�ID:" << it->first << "  ";
                    it->second.Display();
                    cout << endl;
                }
            }
            cout << " ��������������������������������������������������������������������������������������������������������������������������������" << endl;
            cout << "������������������������������������������������������������������������������������������������������������������������������������\n";
            cout << "  ��ǰѡ��ѧ��ID:" << StuID << "  �˻���:" << nowStu->GetUserName() << '\n';
            cout << "������������������������������������������������������������������������������������������������������������������������������������" << endl;

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
            cout << " ѡ�γɹ�\n" << endl;
            cout << ' '; system("pause");
        }
    }
}

//��ʾѧ��stu�ɼ���Ϣ
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
        if (GradeMap.find(*it + stu) == GradeMap.end()) {    //���û�б���ɼ����࣬�ʹ���֮
            Grade grade(CourseMap[*it], stu.GetID());
            GradeMap[*it + stu] = grade;
        }
        const Grade& grade = GradeMap[*it + stu];
        cout << ' '; grade.Display(); cout << endl;
        sumResult += grade.Result2Pair().second * grade.Result2Pair().first;
        allPoint += grade.Result2Pair().first;
    }
    cout << " ��������������������������������������������������������������������������������������������������������������������������������" << endl;
    if (allPoint == 0)
        cout << " ƽ������Ϊ: NaN" << endl;
    else
        cout << " ƽ������Ϊ:" << sumResult / allPoint << endl;
    cout << "\n "; system("pause");
}

//��ʦ�����γ�
bool CreateCourse() {

    Course course;
    std::string coursename;
    int point;
    int type;
    //�γ���
    cout << " �����뿪��γ�����(0-������һ��):";
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    cin >> coursename;
    if (coursename == "0")return true;
    //ѧ��
    cout << " ������ÿγ�ѧ��(0-������һ��):";
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    cin >> point;
    if (point == 0)return true;
    while (point <= 0) {
        cout << " ѧ�����������0������������(0-������һ��):";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cin >> point;
        if (point == 0)return true;
    }
    //�Ʒַ�ʽ
    cout << " ������γ����۷�ʽ(1-�ٷ��� 2-�ȼ��� 3-P/F 0-������һ��):";
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    cin >> type;
    if (type == 0)return true;
    while (type < 0 || type>3) {
        cout << " ������������������γ����۷�ʽ(1-�ٷ��� 2-�ȼ��� 3-P/F 0-������һ��):";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cin >> type;
        if (type == 0)return true;
    }
    course.Init(coursename, point, (RESULT_TYPE)type);
    CourseMap[course.GetID()] = course;
    nowAccount->AddCourseIntoSet(course.GetID());
    cout << " �γ̴����ɹ�!\n" << endl;
    cout << ' '; system("pause");
    return false;
}

//��ʦɾ���γ�
bool DelCourse() {
    IDTYPE id;
    while (true) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << " ����Ҫɾ���Ŀγ�ID(����0������һ��):";
        cin >> id;
        if (id == 0) {
            return true;
        }
        if (CourseMap.find(id) == CourseMap.end() || !nowAccount->IsCourseInSet(id)) {
            cout << " �����������������룬";
        }
        else {
            //���Ҷ�Ӧ�γ��е�ѧ����ɾ��Grade
            for (auto stu = CourseMap[id].GetCourseStudentID().begin(); stu != CourseMap[id].GetCourseStudentID().end(); stu++) {
                GradeMap.erase(_GET_GRADE_ID(*stu, id));  //ɾ����Ӧ�ĳɼ�
                AccountMap[*stu].DelCourseOutSet(id);    //ɾ��ѧ��set�еļ�¼
            }
            //ɾ������Ŀγ�
            CourseMap.erase(id);   //ɾ���γ��еļ�¼
            nowAccount->DelCourseOutSet(id);    //ɾ����ʦ�пγ̵ļ�¼
            cout << " ɾ���γ̳ɹ�!\n" << endl;
            cout << ' '; system("pause");
            break;
        }
    }
    return false;
}

//�γ̳ɼ������˵�
void EnterCourseMenu(IDTYPE courseID) {
    int N;
    //��ʼ��
    while (true) {
        system("cls");
        ShowHead();
        cout << "������������������������������������������������������������������������������������������������������������������������������������\n";
        cout << "  ��ǰ�γ�ID:" << courseID << " "; CourseMap[courseID].Display(); cout << '\n';
        cout << "������������������������������������������������������������������������������������������������������������������������������������" << endl;
        //�˵�ѭ��
        cout << "������������������������������������������������������������������������������������������������������������������������������������\n";
        cout << "��               1. �鿴����ѧ���ɼ�                              ��\n";
        cout << "��               2. ����¼��ɼ�                                  ��\n";
        cout << "��               3. �޸ĳɼ�                                      ��\n";
        cout << "��               4. ɾ���ɼ�                                      ��\n";
        cout << "��               5. �ɼ�����                                      ��\n";
        cout << "��               0. ������һ��                                    ��\n";
        cout << "������������������������������������������������������������������������������������������������������������������������������������" << endl;
        //����ѭ��
        do {
            bool isBreak = false;
            N = -1;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << " ��������ѡ�˵����:";
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
                cout << " ������������������,";
                break;
            }
        } while (N < 0 || N > 9 || (N > 5 && N < 9));
    }
}

//��ʾ����ѧ���ɼ�
void ShowAllStuInCourse(IDTYPE courseID) {
    double sumResult = 0;
    int count = 0;
    double maxResult = -1;
    double minResult = INT_MAX;
    bool hasGrade[12] = { false,false,false,false,false,false,false,false,false,false,false,false };
    //��ʼ��
    system("cls");
    ShowHead();
    cout << "������������������������������������������������������������������������������������������������������������������������������������\n";
    cout << "  ��ǰ�γ�ID:" << courseID << " "; CourseMap[courseID].Display(); cout << '\n';
    cout << "������������������������������������������������������������������������������������������������������������������������������������" << endl;
    cout << " ����������������������ѧ�����������������������������������������������ɩ�����������������������������������������������" << endl;
    //���������ѧ��
    for (auto it = CourseMap[courseID].GetCourseStudentID().begin(); it != CourseMap[courseID].GetCourseStudentID().end(); it++) {
        IDTYPE gradeID = _GET_GRADE_ID(*it, courseID);
        if (GradeMap.find(gradeID) == GradeMap.end()) {    //���û�б���ɼ����࣬�ʹ���֮
            Grade grade(CourseMap[courseID], *it);
            GradeMap[gradeID] = grade;
        }
        const Grade& grade = GradeMap[gradeID];
        cout << " ѧ��ID:" << *it << "  �˻���:" << std::setw(10) << std::left << AccountMap[*it].GetUserName() << std::right;
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
    cout << " ��������������������������������������������������������������������������������������������������������������������������������" << endl;
    if (count > 0) {    //����¼���ѧ��
        if (CourseMap[courseID].GetCourseResultType() == Result_Percent) {    //�ٷ���
            cout << " ƽ����:" << sumResult / count << "  ��߷�:" << maxResult << "  ��ͷ�:" << minResult << endl;
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
            cout << " ƽ������:" << sumResult / count << "  ��߼���:" << GRADE_TO_GPA[maxGrade] << "  ��ͼ���:" << GRADE_TO_GPA[minGrade] << endl;
        }
    }
    cout << "\n "; system("pause");
}

//�������˳��¼��ɼ�
void InputGrade(IDTYPE courseID) {
    bool isBreak = false;
    //��ʼ��
    for (auto it = CourseMap[courseID].GetCourseStudentID().begin(); it != CourseMap[courseID].GetCourseStudentID().end() && !isBreak; it++) {
        system("cls");
        cout << " ��������������������������������������������ʼ������������������������¼�����������������������멨����������������������" << endl;
        cout << "������������������������������������������������������������������������������������������������������������������������������������\n";
        cout << "  ��ǰ�γ�ID:" << courseID << " "; CourseMap[courseID].Display(); cout << '\n';
        cout << "������������������������������������������������������������������������������������������������������������������������������������" << endl;
        IDTYPE gradeID = _GET_GRADE_ID(*it, courseID);
        if (GradeMap.find(gradeID) == GradeMap.end()) {    //���û�б���ɼ����࣬�ʹ���֮
            Grade grade(CourseMap[courseID], *it);
            GradeMap[gradeID] = grade;
        }
        Grade& grade = GradeMap[gradeID];
        isBreak = InputOneGrade(grade);
    }
    cout << " �����������������������ꩨ�������������������ɩ�����������������������¼�����������������������멨����������������������" << endl;

}

//Ϊһ��grade¼��ɼ�
bool InputOneGrade(Grade & grade) {
    cout << "������������������������������������������������������������������������������������������������������������������������������������\n";
    cout << "  ��ǰѧ��ID:" << grade.GetStuID() << "  �˻���:" << std::setw(10) << std::left << AccountMap[grade.GetStuID()].GetUserName() << std::right << '\n';
    cout << "������������������������������������������������������������������������������������������������������������������������������������" << endl;
    bool isInput = true;
    if (grade.GetCourseResultType() == grade.GetGradeResult().m_eType) {    //�Ѿ������ù��ɼ�
        char ch;
        bool isInputCorrect = false;    //�Ƿ���ȷ����
        isInput = false;
        cout << ' ';
        grade.DisplayGradeOnly();
        do {
            cout << " ��ѧ���Ѿ�¼����ɼ����Ƿ�����¼��(Y/N):";
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
    if (isInput) {    //¼��ɼ�
        bool isInputCorrect = false;    //�Ƿ���ȷ����
        switch (grade.GetCourseResultType()) {
        case Result_Percent:    //�ٷ���
            int percent;
            cout << ' ';
            do {
                cout << "����ٷ��Ƴɼ�(�ɼ���Χ0-100 -1-������һ��):";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cin >> percent;
                if (percent == -1)return true;
                if (percent >= 0 && percent <= 100) {
                    isInputCorrect = true;
                    grade.SetGradeResult(RESULT(percent, Result_Percent));
                }
                else {
                    cout << " �����������������룬";
                }
            } while (!isInputCorrect);
            break;
        case Result_Grade:    //�ȼ���
            int GRADE;
            cout << ' ';
            do {
                cout << "����ȼ��Ƴɼ�(-1-������һ��)\n 0-A+ 1-A 2-A- 3-B+ 4-B 5-B- 6-C+ 7-C 8-C- 9-D+ 10-D 11-F\n:";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cin >> GRADE;
                if (GRADE == -1)return true;
                if (GRADE >= 0 && GRADE < 12) {
                    isInputCorrect = true;
                    grade.SetGradeResult(RESULT(GRADE, Result_Grade));
                }
                else {
                    cout << " �����������������룬";
                }
            } while (!isInputCorrect);
            break;
        case Result_PF:    //ͨ���벻ͨ��
            char ch;
            cout << ' ';
            do {
                cout << "ͨ��/��ͨ��(P-ͨ�� F-��ͨ�� 0-������һ��):";
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
                    cout << " �����������������룬";
                    break;
                }
            } while (!isInputCorrect);
            break;
        }
        cout << " ¼��ɹ�!\n" << endl;
    }
    cout << ' '; system("pause");
    return false;
}

//�޸�ĳһѧ���ɼ�
void ChangeGrade(IDTYPE courseID) {
    while (true) {
        system("cls");
        cout << " �����������������������ީ��������������������ĩ������������������������ɩ�����������������������������������������������" << endl;
        cout << "������������������������������������������������������������������������������������������������������������������������������������\n";
        cout << "  ��ǰ�γ�ID:" << courseID << " "; CourseMap[courseID].Display(); cout << '\n';
        cout << "������������������������������������������������������������������������������������������������������������������������������������" << endl;
        cout << " ����������������������ѡ���������������������񩨩���������������������ѧ������������������������������������������������" << endl;
        //ѡ��ѧ��
        for (auto it = CourseMap[courseID].GetCourseStudentID().begin(); it != CourseMap[courseID].GetCourseStudentID().end(); it++) {
            cout << " ѧ��ID��" << *it << "  ";
            AccountMap[*it].Display();
            cout << endl;
        }
        cout << " ��������������������������������������������������������������������������������������������������������������������������������" << endl;
        IDTYPE stuID;
        while (true) {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << " ����Ҫѡ���ѧ���˻�ID(0-������һ��):";
            cin >> stuID;
            if (stuID == 0) {
                return;
            }
            if (AccountMap.find(stuID) == AccountMap.end() || AccountMap[stuID].GetAccountType() != Account_Student || !CourseMap[courseID].IsStudentInSet(stuID)) {
                cout << " �����������������룬";
            }
            else {
                //�����޸�
                system("cls");
                cout << " �����������������������ީ��������������������ĩ������������������������ɩ�����������������������������������������������" << endl;
                cout << "������������������������������������������������������������������������������������������������������������������������������������\n";
                cout << "  ��ǰ�γ�ID:" << courseID << " "; CourseMap[courseID].Display(); cout << '\n';
                cout << "������������������������������������������������������������������������������������������������������������������������������������" << endl;
                IDTYPE gradeID = _GET_GRADE_ID(stuID, courseID);
                if (GradeMap.find(gradeID) == GradeMap.end()) {    //���û�б���ɼ����࣬�ʹ���֮
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

//ɾ��/���ѧ���ɼ�
void DelGrade(IDTYPE courseID) {
    while (true) {
        //��ʼ��
        system("cls");
        ShowHead();
        cout << "������������������������������������������������������������������������������������������������������������������������������������\n";
        cout << "  ��ǰ�γ�ID:" << courseID << " "; CourseMap[courseID].Display(); cout << '\n';
        cout << "������������������������������������������������������������������������������������������������������������������������������������" << endl;
        cout << " ����������������������ɾ�����������������������������������������������ɩ�����������������������������������������������" << endl;
        //���������ѧ��
        for (auto it = CourseMap[courseID].GetCourseStudentID().begin(); it != CourseMap[courseID].GetCourseStudentID().end(); it++) {
            IDTYPE gradeID = _GET_GRADE_ID(*it, courseID);
            if (GradeMap.find(gradeID) == GradeMap.end()) {    //���û�б���ɼ����࣬�ʹ���֮
                Grade grade(CourseMap[courseID], *it);
                GradeMap[gradeID] = grade;
            }
            const Grade& grade = GradeMap[gradeID];
            cout << " ѧ��ID:" << *it << "  �˻���:" << std::setw(10) << std::left << AccountMap[*it].GetUserName() << std::right;
            cout << ' '; grade.DisplayGradeOnly(); cout << endl;
        }
        cout << " ��������������������������������������������������������������������������������������������������������������������������������" << endl;
        IDTYPE stuID;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << " ����Ҫѡ���ѧ���˻�ID(0-������һ��):";
        cin >> stuID;
        if (stuID == 0) {
            return;
        }
        while (AccountMap.find(stuID) == AccountMap.end() || AccountMap[stuID].GetAccountType() != Account_Student || !CourseMap[courseID].IsStudentInSet(stuID)) {
            cout << " �����������������룬����Ҫѡ���ѧ���˻�ID(0-������һ��):";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cin >> stuID;
            if (stuID == 0) {
                return;
            }
        }
        //ɾ���ɼ�
        GradeMap.erase(_GET_GRADE_ID(stuID, courseID));
        cout << " ɾ���ɹ�!\n" << endl;
        cout << ' '; system("pause");
    }
}

//���γ�������ѧ���ɼ��������У�����δ¼����������
void SortAndShow(IDTYPE courseID) {
    std::set<Grade, std::greater<const Grade&>>sorted;
    for (auto it = CourseMap[courseID].GetCourseStudentID().begin(); it != CourseMap[courseID].GetCourseStudentID().end(); it++) {
        IDTYPE gradeID = _GET_GRADE_ID(*it, courseID);
        if (GradeMap.find(gradeID) == GradeMap.end()) {    //���û�б���ɼ����࣬�ʹ���֮
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
    //��ʼ��
    system("cls");
    ShowHead();
    cout << "������������������������������������������������������������������������������������������������������������������������������������\n";
    cout << "  ��ǰ�γ�ID:" << courseID << " "; CourseMap[courseID].Display(); cout << '\n';
    cout << "������������������������������������������������������������������������������������������������������������������������������������" << endl;
    cout << " �����������������������ɩ����������������������������������������������������������������������򩨩���������������������" << endl;
    //���������ѧ��
    for (auto it = sorted.begin(); it != sorted.end(); it++) {

        const Grade& grade = *it;
        cout << " ѧ��ID:" << it->GetStuID() << "  �˻���:" << std::setw(10) << std::left << AccountMap[it->GetStuID()].GetUserName() << std::right;
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
    cout << " ��������������������������������������������������������������������������������������������������������������������������������" << endl;
    if (count > 0) {    //����¼���ѧ��
        if (CourseMap[courseID].GetCourseResultType() == Result_Percent) {    //�ٷ���
            cout << " ƽ����:" << sumResult / count << "  ��߷�:" << maxResult << "  ��ͷ�:" << minResult << endl;
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
            cout << " ƽ������:" << sumResult / count << "  ��߼���:" << GRADE_TO_GPA[maxGrade] << "  ��ͼ���:" << GRADE_TO_GPA[minGrade] << endl;
        }
    }
    cout << "\n "; system("pause");
}

//д�������ļ�������ȫ����Ϣ
void SaveFile(std::ofstream& File) {
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

//���������ļ�����ȡȫ����Ϣ
void LoadFile(std::ifstream& File) {
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
        cout << " Error: �����ļ�δ�ܳɹ���" << endl;
        system("pause");
        exit(0);
    }
}


