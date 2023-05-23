#include <fstream> 
#include <string.h>
#include <iostream>
#include <vector>

// ��� ����
#define MAX_STRING 32
#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"

// �Լ� ����
void doTask();
void join();
void program_exit();

// ���� ����
FILE* in_fp, * out_fp;

int main()
{
    in_fp = fopen("input.txt", "r+");
    out_fp = fopen("output.txt", "w+");

    if (in_fp == NULL || out_fp == NULL)
    {
        printf("�Է� �Ǵ� ��� ������ �� �� �����ϴ�.\n");
        return 1; // ���α׷� ����
    }
    else {
        doTask();
        printf("����� ����");
    }

    return 0;
}

void doTask()
{
    int menu_level_1 = 0, menu_level_2 = 0;
    int is_program_exit = 0;

    while (!is_program_exit)
    {
        fscanf(in_fp, "%d %d ", &menu_level_1, &menu_level_2);

        switch (menu_level_1)
        {
        case 1:
        {
            switch (menu_level_2)
            {
            case 1:
            {
                registerMember();
                break;
            }
            case 2:
            {
                withdrawMember();
                break;
            }
            }
            break;
        }
        case 2:
        {
            switch (menu_level_2)
            {
            case 1:
            {
                login();
                break;
            }
            case 2:
            {
                logout();
                break;
            }
            }
            break;
        }
        case 3:
        {
            switch (menu_level_2)
            {
            case 1:
            {
                fprintf(out_fp, "3.1. ä�� ���� ���\n");
                // Perform job posting registration functionality
                break;
            }
            case 2:
            {
                fprintf(out_fp, "3.2. ��ϵ� ä�� ���� ��ȸ\n");
                // Perform job posting retrieval functionality
                break;
            }
            }
            break;
        }
        case 4:
        {
            switch (menu_level_2)
            {
            case 1:
            {
                fprintf(out_fp, "4.1. ä�� ���� �˻�\n");
                // Perform job search functionality
                break;
            }
            case 2:
            {
                fprintf(out_fp, "4.2. ä�� ����\n");
                // Perform job application functionality
                break;
            }
            case 3:
            {
                fprintf(out_fp, "4.3. ���� ���� ��ȸ\n");
                // Perform application retrieval functionality
                break;
            }
            case 4:
            {
                fprintf(out_fp, "4.4. ���� ���\n");
                // Perform application cancellation functionality
                break;
            }
            }
            break;
        }
        case 5:
        {
            switch (menu_level_2)
            {
            case 1:
            {
                fprintf(out_fp, "5.1. ���� ���� ���\n");

                break;
            }
            }
            break;
        }
        case 6:
        {
            switch (menu_level_2)
            {
            case 1:
            {
                fprintf(out_fp, "6.1. ����\n");
                program_exit();
                is_program_exit = 1;
                break;
            }
            }
            break;
        }
        }
    }
    //    fclose(in_fp);  // �Է� ���� �ݱ�
    //    fclose(out_fp); // ��� ���� �ݱ�

    return;
}

void statics() {
    fprintf(out_fp, "�벾 �Ϸ�");
}

void function() {

    char user_type[MAX_STRING], name[MAX_STRING], SSN[MAX_STRING], address[MAX_STRING], ID[MAX_STRING], password[MAX_STRING];

    // �Է� ���� : �̸�, �ֹι�ȣ, ID, Password�� ���Ϸκ��� ����
    fscanf(in_fp, "%s %s %s %s", name, SSN, ID, password);


    // �ش� ��� ����


     // ��� ����
    fprintf(out_fp, "1.1. ȸ������\n");
    fprintf(out_fp, "%s %s %s %s\n", name, SSN, ID, password);
}

void program_exit() {
    return;
}

void Register();
//1.2 ȸ��Ż��
void unRegister();
//2.1 �α���
void Login();
//2.2 �α׾ƿ�
void Logout();



//entity class ... 
/*
    �⺻������ �Ϲ�, ȸ��ȸ�� ��� �̸�,ID,PW�� ������ �����Ƿ� member entity�� �����Ͽ���
    �Ϲ�ȸ���� �ֹι�ȣ(SSN), ȸ��ȸ���� ����ڹ�ȣ(BN)�� ������ �־� �׺κ��� General member, Company member���� �������־����ϴ�.
*/
class member {
private:
    string name;
    string id;
    string password;

public:
    member(string n, string i, string p) {
        name = n;
        id = i;
        password = p;
    }
    string getName() {
        return name;
    }
    string getId() {
        return id;
    }
    string getPassword() {
        return password;
    }
};

class GeneralMember :public member {
private:
    string SSN;
public:
    GeneralMember(string n, string ssn, string i, string p) :member(n, i, p) {
        SSN = ssn;
    }
};

class CompanyMember :public member {
private:
    string BN;
public:
    CompanyMember(string n, string bn, string i, string p) :member(n, i, p) {
        BN = bn;
    }
};



// ���� ���� (�ʿ��ϸ� �߰��� ���� �� ���)
ifstream in_fp;
ofstream out_fp;
vector<GeneralMember> generalMemberList;
vector<CompanyMember> companyMemberList;
GeneralMember* currentGeneralMember = NULL;
CompanyMember* currentCompanyMember = NULL;


//�ٿ���� Ŭ���� ��Ʈ�� Ŭ���� ...
/*
1.1 ȸ������
RegisterUI Ŭ������ selectgeneralRegisterUI, selectcompanyRegisterUI�Լ��� RegisterŬ������ �Լ��� �Ѱ��ִ� ��ɸ� �����ϰ� �ֽ��ϴ�.
Register Ŭ�������� setGeneralRegisterInfo�Լ��� �̸�, �ֹι�ȣ, id, string�� �޾� ���ο� GeneralMember��ü�� �����ϰ� �� ��ü�� generalMemberList�� �ִ��Լ��̰�
                    setCompanyRegisterInfo�Լ��� �� ����� company�� �°� �����մϴ�.
*/
class Register {
public:
    static void setGeneralRegisterInfo(string name, string ssn, string id, string pw) {
        GeneralMember newGeneralMember(name, ssn, id, pw);
        generalMemberList.push_back(newGeneralMember);
    };
    static void setCompanyRegisterInfo(string name, string bn, string id, string pw) {
        CompanyMember newCompanyMember(name, bn, id, pw);
        companyMemberList.push_back(newCompanyMember);
    };
};
class RegisterUI {
public:
    static void selectgeneralRegisterUI(string name, string ssn, string id, string pw) {
        Register::setGeneralRegisterInfo(name, ssn, id, pw);
    }
    static void selectcompanyRegisterUI(string name, string bn, string id, string pw) {
        Register::setCompanyRegisterInfo(name, bn, id, pw);
    }

};

/*
1.2 ȸ��Ż��
UnregisterŬ������ UnregisterUIŬ������ �̷�����ְ�
UnregisterUIŬ������ UnregisterŬ������ �Է¹��� id���� �Ѱ��ִ� ��ɸ� �����ϰ��ֽ��ϴ�.
UnregisterŬ������ �Է¹���id�� generalMemberList�� companyMemberList���� Ȯ���Ͽ� �ش�id�� �����ϴ� ����� �����մϴ�.

*/
class Unregister {
public:
    static void withdraw(string id) {
        for (int i = 0; i < generalMemberList.size(); i++) {
            if (generalMemberList[i].getId() == id) {
                generalMemberList.erase(generalMemberList.begin() + i);
            }
        }
        for (int i = 0; i < companyMemberList.size(); i++) {
            if (companyMemberList[i].getId() == id) {
                companyMemberList.erase(companyMemberList.begin() + i);
            }
        }
    }
};

class UnregisterUI {
public:
    static void selectUnregisterUI(string id) {
        Unregister::withdraw(id);
    }
};


/*
2.1 �α���
LoginŬ������ LoginUIŬ������ �̷�����ְ�
LoginUIŬ������ LoginŬ������ �Է¹��� id,pw ���� �Ѱ��ִ� ��ɸ� �����ϰ��ֽ��ϴ�.
LoginŬ������ generalMemberList�� companyMemberList���� id,pw�� ��ġ�ϸ� �α��μ��� �������̽��� ����մϴ�.
*/

class Login {
public:
    static void callLogin(string id, string pw) {
        for (int i = 0; i < generalMemberList.size(); i++) {
            if (generalMemberList[i].getId() == id && generalMemberList[i].getPassword() == pw) {
                out_fp << "2.1 �α���\n";
                out_fp << id << pw;
            }
        }
        for (int i = 0; i < companyMemberList.size(); i++) {
            if (companyMemberList[i].getId() == id && companyMemberList[i].getPassword() == pw) {
                out_fp << "2.1 �α���\n";
                out_fp << id << pw;
            }
        }
    }
};

class LoginUI {
public:
    static void selectLoginUI(string id, string pw) {
        Login::callLogin(id, pw);
    }
};

/*
2.2 �α׾ƿ�
LogoutŬ������ LogoutUIŬ������ �̷�����ְ�
LogoutUIŬ������ LogoutŬ������ �Է¹��� id���� �Ѱ��ִ� ��ɸ� �����ϰ��ֽ��ϴ�.
LogoutŬ������ generalMemberList�� companyMemberList���� id�� ��ġ�ϸ� �α׾ƿ����� �������̽��� ����մϴ�.
*/

class Logout {
public:
    static void callLogout(string id) {
        for (int i = 0; i < generalMemberList.size(); i++) {
            if (generalMemberList[i].getId() == id) {
                out_fp << "2.2 �α׾ƿ�\n";
                out_fp << id;
            }
        }
        for (int i = 0; i < companyMemberList.size(); i++) {
            if (companyMemberList[i].getId() == id) {
                out_fp << "2.2 �α׾ƿ�\n";
                out_fp << id;
            }
        }
    }
};

class LogoutUI {
public:
    static void selectLogoutUI(string id) {
        Logout::callLogout(id);
    }
};

//�Լ� ���� �ߴ� �͵� ��üȭ
//1.1 ȸ������  �Է� ���Ͽ� 1 1�� ���ؼ� ȸ������ ����� �����Ͽ��� �� ���� ���ڸ� memberType ���ڷ� �޾� 1�̸� �Ϲ�ȸ������ 2�̸� ȸ��ȸ�������� �����մϴ�.
void registerMember() {
    fscanf(in_fp, "%c", &memberType);
    string name, number, ID, password;
    in_fp >> name >> number >> ID >> password;

    if (memberType == 1)
        RegisterUI::selectgeneralRegisterUI(name, number, ID, password);
    else if (memberType == 2)
        RegisterUI::selectcompanyRegisterUI(name, number, ID, password);

    out_fp << "1.1 ȸ������\n";
    out_fp << name << number << ID << password;
};

//1.2 ȸ��Ż�� �Է����Ͽ��� id�� �޾� ȸ��Ż�� �����մϴ�.
void withdrawMember() {
    fscanf(in_fp, "%c", &id);
    string id;
    in_fp >> id;

    UnregisterUI::selectUnregisterUI(id);

    out_fp << "1.2 ȸ��Ż��\n";
    out_fp << id;
};

//2.1 �α��� 
//�Է����Ͽ��� id, pw�� �Է¹޾� �α����� �����մϴ�.
void login() {
    fscanf(in_fp, "%c %c", &id, &pw);
    string id, pw;
    in_fp >> id >> pw;

    LoginUI::selectLoginUI(id, pw);

};

/*
2.2 �α׾ƿ�
*/
void logout() {
    fscanf(in_fp, "%c", &id);
    string id;
    in_fp >> id;

    LogoutUI::selectLogoutUI(id);
};
