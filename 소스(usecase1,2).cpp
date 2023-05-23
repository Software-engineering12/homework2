#include <fstream> 
#include <string.h>
#include <iostream>
#include <vector>

// 상수 선언
#define MAX_STRING 32
#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"

// 함수 선언
void doTask();
void join();
void program_exit();

// 변수 선언
FILE* in_fp, * out_fp;

int main()
{
    in_fp = fopen("input.txt", "r+");
    out_fp = fopen("output.txt", "w+");

    if (in_fp == NULL || out_fp == NULL)
    {
        printf("입력 또는 출력 파일을 열 수 없습니다.\n");
        return 1; // 프로그램 종료
    }
    else {
        doTask();
        printf("입출력 성공");
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
                fprintf(out_fp, "3.1. 채용 정보 등록\n");
                // Perform job posting registration functionality
                break;
            }
            case 2:
            {
                fprintf(out_fp, "3.2. 등록된 채용 정보 조회\n");
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
                fprintf(out_fp, "4.1. 채용 정보 검색\n");
                // Perform job search functionality
                break;
            }
            case 2:
            {
                fprintf(out_fp, "4.2. 채용 지원\n");
                // Perform job application functionality
                break;
            }
            case 3:
            {
                fprintf(out_fp, "4.3. 지원 정보 조회\n");
                // Perform application retrieval functionality
                break;
            }
            case 4:
            {
                fprintf(out_fp, "4.4. 지원 취소\n");
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
                fprintf(out_fp, "5.1. 지원 정보 통계\n");

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
                fprintf(out_fp, "6.1. 종료\n");
                program_exit();
                is_program_exit = 1;
                break;
            }
            }
            break;
        }
        }
    }
    //    fclose(in_fp);  // 입력 파일 닫기
    //    fclose(out_fp); // 출력 파일 닫기

    return;
}

void statics() {
    fprintf(out_fp, "통꼐 완료");
}

void function() {

    char user_type[MAX_STRING], name[MAX_STRING], SSN[MAX_STRING], address[MAX_STRING], ID[MAX_STRING], password[MAX_STRING];

    // 입력 형식 : 이름, 주민번호, ID, Password를 파일로부터 읽음
    fscanf(in_fp, "%s %s %s %s", name, SSN, ID, password);


    // 해당 기능 수행


     // 출력 형식
    fprintf(out_fp, "1.1. 회원가입\n");
    fprintf(out_fp, "%s %s %s %s\n", name, SSN, ID, password);
}

void program_exit() {
    return;
}

void Register();
//1.2 회원탈퇴
void unRegister();
//2.1 로그인
void Login();
//2.2 로그아웃
void Logout();



//entity class ... 
/*
    기본적으로 일반, 회사회원 모두 이름,ID,PW를 가지고 있으므로 member entity에 선언하였고
    일반회원은 주민번호(SSN), 회사회원은 사업자번호(BN)를 가지고 있어 그부분은 General member, Company member에서 선언해주었습니다.
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



// 변수 선언 (필요하면 추가로 선언 후 사용)
ifstream in_fp;
ofstream out_fp;
vector<GeneralMember> generalMemberList;
vector<CompanyMember> companyMemberList;
GeneralMember* currentGeneralMember = NULL;
CompanyMember* currentCompanyMember = NULL;


//바운더리 클래스 컨트롤 클래스 ...
/*
1.1 회원가입
RegisterUI 클래스의 selectgeneralRegisterUI, selectcompanyRegisterUI함수는 Register클래스로 함수를 넘겨주는 기능만 수행하고 있습니다.
Register 클래스에선 setGeneralRegisterInfo함수는 이름, 주민번호, id, string을 받아 새로운 GeneralMember객체를 생성하고 그 객체를 generalMemberList에 넣는함수이고
                    setCompanyRegisterInfo함수는 위 기능을 company에 맞게 수행합니다.
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
1.2 회원탈퇴
Unregister클래스와 UnregisterUI클래스로 이루어져있고
UnregisterUI클래스는 Unregister클래스로 입력받은 id값을 넘겨주는 기능만 수행하고있습니다.
Unregister클래스는 입력받은id를 generalMemberList와 companyMemberList에서 확인하여 해당id를 삭제하는 기능을 수행합니다.

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
2.1 로그인
Login클래스와 LoginUI클래스로 이루어져있고
LoginUI클래스는 Login클래스로 입력받은 id,pw 값을 넘겨주는 기능만 수행하고있습니다.
Login클래스는 generalMemberList와 companyMemberList에서 id,pw가 일치하면 로그인성공 인터페이스를 출력합니다.
*/

class Login {
public:
    static void callLogin(string id, string pw) {
        for (int i = 0; i < generalMemberList.size(); i++) {
            if (generalMemberList[i].getId() == id && generalMemberList[i].getPassword() == pw) {
                out_fp << "2.1 로그인\n";
                out_fp << id << pw;
            }
        }
        for (int i = 0; i < companyMemberList.size(); i++) {
            if (companyMemberList[i].getId() == id && companyMemberList[i].getPassword() == pw) {
                out_fp << "2.1 로그인\n";
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
2.2 로그아웃
Logout클래스와 LogoutUI클래스로 이루어져있고
LogoutUI클래스는 Logout클래스로 입력받은 id값을 넘겨주는 기능만 수행하고있습니다.
Logout클래스는 generalMemberList와 companyMemberList에서 id가 일치하면 로그아웃성공 인터페이스를 출력합니다.
*/

class Logout {
public:
    static void callLogout(string id) {
        for (int i = 0; i < generalMemberList.size(); i++) {
            if (generalMemberList[i].getId() == id) {
                out_fp << "2.2 로그아웃\n";
                out_fp << id;
            }
        }
        for (int i = 0; i < companyMemberList.size(); i++) {
            if (companyMemberList[i].getId() == id) {
                out_fp << "2.2 로그아웃\n";
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

//함수 선언 했던 것들 구체화
//1.1 회원가입  입력 파일에 1 1을 통해서 회원가입 기능을 실행하였고 그 다음 숫자를 memberType 인자로 받아 1이면 일반회원가입 2이면 회사회원가입을 실행합니다.
void registerMember() {
    fscanf(in_fp, "%c", &memberType);
    string name, number, ID, password;
    in_fp >> name >> number >> ID >> password;

    if (memberType == 1)
        RegisterUI::selectgeneralRegisterUI(name, number, ID, password);
    else if (memberType == 2)
        RegisterUI::selectcompanyRegisterUI(name, number, ID, password);

    out_fp << "1.1 회원가입\n";
    out_fp << name << number << ID << password;
};

//1.2 회원탈퇴 입력파일에서 id를 받아 회원탈퇴를 실행합니다.
void withdrawMember() {
    fscanf(in_fp, "%c", &id);
    string id;
    in_fp >> id;

    UnregisterUI::selectUnregisterUI(id);

    out_fp << "1.2 회원탈퇴\n";
    out_fp << id;
};

//2.1 로그인 
//입력파일에서 id, pw를 입력받아 로그인을 실행합니다.
void login() {
    fscanf(in_fp, "%c %c", &id, &pw);
    string id, pw;
    in_fp >> id >> pw;

    LoginUI::selectLoginUI(id, pw);

};

/*
2.2 로그아웃
*/
void logout() {
    fscanf(in_fp, "%c", &id);
    string id;
    in_fp >> id;

    LogoutUI::selectLogoutUI(id);
};
