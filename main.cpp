
// 헤더 선언 (필요하면 추가로 선언)
#include <fstream>
#include <string.h>
#include<iostream>
#include<vector>
#include<map>
#include<iomanip>

using namespace std;

// 상수 선언
#define MAX_STRING 32
#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"

//함수 선언
void doTask();
void program_exit();
void registerMember();
void withdrawMember();
void login();
void logout();
void addRecruitmentInfo();
void getRecruitment();
void searchRecruitment();
void applyInput();
void getApplication();
void removeApplicant();
void getApplicationStats();

//entity class ...

class member {
private:
    string id;
    string password;
public:
    member(string i, string p) {
        id = i;
        password = p;
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
    string name;
    int idNumber;
public:
    GeneralMember(string n, int idN,string i,string p) :member(i,p) {
        name = n;
        idNumber = idN;
    }
    string getName() {
        return name;
    }
    int getIdNumber() {
        return idNumber;
    }
};

class CompanyMember :public member {
private:
    int businessNumber;
    string businessField;
public:
    CompanyMember(string bf,int bn,string i,string p) :member(i, p) {
        businessNumber = bn;
        businessField = bf;
    }
    int getBusinessNumber() {
        return businessNumber;
    }
    string getBusinessField() {
        return businessField;
    }
};

class RecruitmentInfo {
private:
    string job;
    int numberOfPeople;
    string applicationDeadLine;
    vector<int> idNumber; //일반 회원 정보
    int businessNumber=-1;    //회사 회원 정보
    string businessField="NULL";
public:
    RecruitmentInfo(string j, int np, string a) {
        job = j;
        numberOfPeople = np;
        applicationDeadLine = a;
    }
    string getJob() {
        return job;
    }
    int getNumberOfPeople() {
        return numberOfPeople;
    }
    string getApplicationDeadLine() {
        return applicationDeadLine;
    }
    vector<int> getIdNumber() {
        return idNumber;
    }
    int getBusineesNumber() {
        return businessNumber;
    }
    string getBusinessField() {
        return businessField;
    }
    int getNumberSize() {
        return idNumber.size();
    }
    void setIdNumber(int idn) {
        idNumber.push_back(idn);
    }
    void setBusinessNumber(int bs) {
        businessNumber = bs;
    }
    void setBusinessField(string bf) {
        businessField = bf;
    }
    void deleteIdNumber(int num) {
        idNumber.erase(remove(idNumber.begin(), idNumber.end(), num), idNumber.end());
    }
};

// 변수 선언 (필요하면 추가로 선언 후 사용)
ifstream in_fp;
ofstream out_fp;
vector<GeneralMember> generalMemberList;
vector<CompanyMember> companyMemberList;
GeneralMember* currentGeneralMember=NULL;
CompanyMember* currentCompanyMember=NULL;
vector<RecruitmentInfo> recruitmentList;



//바운더리 클래스 컨트롤 클래스 ...
//1.1 회원가입
class Register {
public:
    static void setGeneralRegisterInfo(string name, int ssn, string id, string pw) {
        GeneralMember newGeneralMember(name, ssn, id, pw);
        generalMemberList.push_back(newGeneralMember);
    }
    static void setCompanyRegisterInfo(string name, int bn, string id, string pw) {
        CompanyMember newCompanyMember(name, bn, id, pw);
        companyMemberList.push_back(newCompanyMember);
    }
};
class RegisterUI {
public:
    static void selectgeneralRegisterUI(string name, int ssn, string id, string pw) {
        Register::setGeneralRegisterInfo(name, ssn, id, pw);
    }
    static void selectcompanyRegisterUI(string name, int bn, string id, string pw) {
        Register::setCompanyRegisterInfo(name, bn, id, pw);
    }
};

//1.2 회원탈퇴
class Unregister {
public:
    static void withdraw() {
        if (currentCompanyMember != NULL) {
            out_fp << ">" << currentCompanyMember->getId() << "\n";
            delete currentCompanyMember;
            currentCompanyMember = NULL;
        }
        if (currentGeneralMember != NULL) {
            out_fp << ">" << currentGeneralMember->getId() << "\n";
            delete currentGeneralMember;
            currentGeneralMember = NULL;
        }
    }
};
class UnregisterUI {
public:
    static void selectUnregisterUI() {
        Unregister::withdraw();
    }
};

//2.1 로그인
class Login {
public:
    static void callLogin(string id, string pw) {
        int i = 0;
        int j = 0;
        while (true) {
            if (generalMemberList.size() == i) break;
            if (generalMemberList[i].getId() == id && generalMemberList[i].getPassword() == pw) {
                out_fp << ">" << " " << id << " " << pw << "\n";
                currentGeneralMember = &generalMemberList[i];
                break;
            }
            else i++;
        }
        while (true) {
            if (companyMemberList.size() == j) break;
            if (companyMemberList[j].getId() == id && companyMemberList[j].getPassword() == pw) {
                out_fp << ">" << " " << id << " " << pw << "\n";
                currentCompanyMember = &companyMemberList[j];
                break;
            }
            else j++;
        }
        if (currentCompanyMember==NULL&&currentGeneralMember==NULL) out_fp << "로그인 실패\n";
    }
};
class LoginUI {
public:
    static void selectLoginUI(string id, string pw) {
        Login::callLogin(id, pw);
    }
};

//2.2 로그아웃
class Logout {
public:
    static void callLogout() {
        if (currentCompanyMember != NULL) {
            out_fp << ">" << " " << currentCompanyMember->getId()  << "\n";
            currentCompanyMember = NULL;
        }
        if (currentGeneralMember != NULL) {
            out_fp << ">" << " " << currentGeneralMember->getId()  << "\n";
            currentGeneralMember = NULL;
        }
    }
};
class LogoutUI {
public:
    static void selectLogoutUI() {
        Logout::callLogout();
    }
};

//3.1 채용 정보 등록
class AddNewRecruitment {
public:
    static void add_Recruitment(string job, int numberOfPeople, string applicationDeadLine) {
        RecruitmentInfo r(job, numberOfPeople, applicationDeadLine);
        r.setBusinessField(currentCompanyMember->getBusinessField());
        r.setBusinessNumber(currentCompanyMember->getBusinessNumber());
        recruitmentList.push_back(r);
        out_fp << ">" << " " << job << " " << numberOfPeople << " " << applicationDeadLine << "\n";
    }
};
class AddRecruitmentUI {
public:
    static void createRecruitment(string job, int numberOfPeople, string applicationDeadLine) {
        AddNewRecruitment::add_Recruitment(job, numberOfPeople, applicationDeadLine);
    }
};

//3.2 등록된 채용 정보 조회
class GetRecruitmentInfo {
public:
    static void getRecruitment() {
        for (int i = 0; i != recruitmentList.size(); i++) {
            if (recruitmentList[i].getBusineesNumber() == currentCompanyMember->getBusinessNumber()) {
                string job = recruitmentList[i].getJob();
                int numberOfPeople = recruitmentList[i].getNumberOfPeople();
                string applicationDeadLine = recruitmentList[i].getApplicationDeadLine();
                out_fp << ">" << " " << job << " " << numberOfPeople << " " << applicationDeadLine << "\n";
            }
        }
    }
};
class GetRecruitmentInfoUI {
public:
    static void call_recruitmentinfo() {
        GetRecruitmentInfo::getRecruitment();
    }
};

//4.1 채용 정보 검색
class RecruitmentSearchInfo {
public:
    static void recruitmentSearch(string name) {
        for (int i = 0; i != recruitmentList.size(); i++) {
            if (recruitmentList[i].getBusinessField() == name) {
                string businessField = recruitmentList[i].getBusinessField();
                int busineesNumber = recruitmentList[i].getBusineesNumber();
                string job = recruitmentList[i].getJob();
                int numberOfPeople = recruitmentList[i].getNumberOfPeople();
                string applicationDeadLine = recruitmentList[i].getApplicationDeadLine();
                out_fp << ">" << " " << businessField << " " << busineesNumber << " " << job << " " << numberOfPeople << " " << applicationDeadLine << "\n";
            }
        }
    }
};
class RecruitmentSearchUI {
public:
    static void call_recruitmentSearch(string name) {
        RecruitmentSearchInfo::recruitmentSearch(name);
    }
};

//4.2 채용 지원
class ApplyForRecruitment {
public:
    static void applyRecruitment(int number)
    {
        for (int i = 0; i != recruitmentList.size(); i++) {
            if (recruitmentList[i].getBusineesNumber() == number) {
                recruitmentList[i].setIdNumber(currentGeneralMember->getIdNumber()); //채용 정보 리스트에 주민번호를 set함
                string businessField = recruitmentList[i].getBusinessField();
                int busineesNumber = recruitmentList[i].getBusineesNumber();
                string job = recruitmentList[i].getJob();
                out_fp << ">" << " "  << businessField << " " << busineesNumber <<" " << job << "\n";
            }
        }
    }
};
class ApplyForRecruitmentUI {
public:
    static void apply(int number) {
        ApplyForRecruitment::applyRecruitment(number);
    }
};

//4.3 지원 정보 조회
class GetApplicationInformation {
public:
    static void showAppInfo() {
        for (int i = 0; i != recruitmentList.size(); i++) {//채용정보리스트를 조회하면서
            for (int j=0; j != recruitmentList[i].getIdNumber().size();j++) {//조회한 채용 정보에 회원의 주민번호들을 조회하면서
                if (currentGeneralMember->getIdNumber() == recruitmentList[i].getIdNumber()[j]) { //일반회원이 지원한 채용이면
                    string businessField = recruitmentList[i].getBusinessField();
                    int busineesNumber = recruitmentList[i].getBusineesNumber();
                    string job = recruitmentList[i].getJob();
                    int numberOfPeople = recruitmentList[i].getNumberOfPeople();
                    string applicationDeadLine = recruitmentList[i].getApplicationDeadLine();
                    out_fp << ">" << " " << businessField << " " << busineesNumber << " " << job << " " << numberOfPeople << " " << applicationDeadLine << "\n";
                }
            }
        }
    }
};
class GetApplicationInformationUI {
public:
    static void getApplicationInfo() {
        GetApplicationInformation::showAppInfo();
    }
};

//4.4 지원 취소
class CancelApplicationInfo {
public:
    static void cancelApplication(string applicant) {
        for (int i = 0; i != recruitmentList.size(); i++) {
            if (applicant == recruitmentList[i].getBusinessField()) {
                string businessField = recruitmentList[i].getBusinessField();
                int busineesNumber = recruitmentList[i].getBusineesNumber();
                string job = recruitmentList[i].getJob();
                out_fp << ">" << " " << job << " " << businessField << " " << busineesNumber << "\n";
                recruitmentList[i].deleteIdNumber(currentGeneralMember->getIdNumber());
            }
        }
    }
};
class CancelApplicationUI {
public:
    static void cancelCallApplication(string applicant) {
        CancelApplicationInfo::cancelApplication(applicant);
    }
};

//5.1 지원 정보 통계
class GetApplicationStatsInfo {
public:
    static void getApplicationStats() {
        if (currentCompanyMember != NULL) {//회사회원이 로그인 상태일 경우
            for (int i = 0; i != recruitmentList.size(); i++) {
                if (currentCompanyMember->getBusinessNumber() == recruitmentList[i].getBusineesNumber()) {
                    out_fp << ">" << " " << recruitmentList[i].getJob() << " " << recruitmentList[i].getNumberSize() << "\n";
                }
            }
        }
        if (currentGeneralMember != NULL) {//일반회원이 로그인 상태일 경우
            map<string, int> statistics;
            for (int i = 0; i != recruitmentList.size(); i++) {
                for (int j=0; j != recruitmentList[i].getIdNumber().size(); j++) {
                    if (currentGeneralMember->getIdNumber() == recruitmentList[i].getIdNumber()[j]) {
                        if (statistics.count(recruitmentList[i].getJob()) == 1) statistics[recruitmentList[i].getJob()]++;                       
                        else statistics[recruitmentList[i].getJob()] = 1;
                        }
                    }
                }
            out_fp << ">";
            for (auto iter = statistics.begin(); iter != statistics.end(); ++iter) out_fp <<">"<< " "<< iter->first << " " << iter->second << "\n";
            }
    }
};
class GetApplicationStatsUI {
public:
    static void showApplicationStats() {
        GetApplicationStatsInfo::getApplicationStats();
    }
};
//함수 선언 했던 것들 구체화

//1.1 회원가입
void registerMember() {
    string name, ID, password;
    int number, memberType;
    in_fp >> memberType >> name >> number >> ID >> password;

    if (memberType == 1) RegisterUI::selectcompanyRegisterUI(name, number, ID, password);
    if (memberType == 2) RegisterUI::selectgeneralRegisterUI(name, number, ID, password);
    out_fp << ">" << " " << memberType << " " << name << " " << number << " " << ID << " " << password << "\n";
}

//1.2 회원탈퇴
void withdrawMember() {
    UnregisterUI::selectUnregisterUI();
}

//2.1 로그인
void login() {
    string id, pw;
    in_fp >> id >> pw;
    LoginUI::selectLoginUI(id, pw);
}

//2.2 로그아웃
void logout() {
    LogoutUI::selectLogoutUI();
}

//3.1 채용 정보 등록
void addRecruitmentInfo() {
    string job, applicationDeadLine;
    int numberOfPeople;
    in_fp >> job >> numberOfPeople >> applicationDeadLine;
    AddRecruitmentUI::createRecruitment(job, numberOfPeople, applicationDeadLine);
}

//3.2 등록된 채용 정보 조회
void getRecruitment() {
    GetRecruitmentInfoUI::call_recruitmentinfo();
}

//4.1 채용 정보 검색
void searchRecruitment() {
    string str;
    in_fp >> str;
    RecruitmentSearchUI::call_recruitmentSearch(str);
}

//4.2 채용 지원
void applyInput() {
    int num;
    in_fp >> num;
    ApplyForRecruitmentUI::apply(num);
}
//4.3 지원 정보 조회
void getApplication() {
    GetApplicationInformationUI::getApplicationInfo();
}

//4.4 지원 취소
void removeApplicant() {
    string str;
    CancelApplicationUI::cancelCallApplication(str);
}
//5.1 지원 정보 통계
void getApplicationStats() {
    GetApplicationStatsUI::showApplicationStats();
}
//6.1 프로그램 종료
void program_exit() {}

int main()
{
    in_fp.open(INPUT_FILE_NAME);
    out_fp.open(OUTPUT_FILE_NAME);
    doTask(); 
    return 0;
}

void doTask()
{
    // 메뉴 파싱을 위한 level 구분을 위한 변수
    int menu_level_1 = 0, menu_level_2 = 0;
    int is_program_exit = 0;

    while (!is_program_exit)
    {
        // 입력파일에서 메뉴 숫자 2개를 읽기
        in_fp >> menu_level_1 >> menu_level_2;


        // 메뉴 구분 및 해당 연산 수행
        switch (menu_level_1)
        {
        case 1:
        {
            switch (menu_level_2)
            {
            case 1:   // "1.1. 회원가입“ 메뉴 부분
            {
                out_fp << "1.1. 회원가입\n";
                registerMember();
                break;
            }
            case 2:
            {
                out_fp << "1.2. 회원탈퇴\n";
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
                out_fp << "2.1. 로그인\n";
                login();
                break;
            }
            case 2:
            {
                out_fp << "2.2. 로그아웃\n";
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
                out_fp << "3.1. 채용 정보 등록\n";
                addRecruitmentInfo();
                break;
            }
            case 2:
            {
                out_fp << "3.2. 등록된 채용 정보 조회\n";
                getRecruitment();
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
                out_fp << "4.1. 채용 정보 검색\n";
                searchRecruitment();
                break;
            }
            case 2:
            {
                out_fp << "4.2. 채용 지원\n";
                applyInput();
                break;
            }
            case 3:
            {
                out_fp << "4.3. 지원 정보 조회\n";
                getApplication();
                break;
            }
            case 4:
            {
                out_fp << "4.4. 지원 취소\n";
                removeApplicant();
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
                out_fp << "5.1. 지원 정보 통계\n";
                getApplicationStats();
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
                out_fp << "6.1. 종료\n";
                program_exit();
                is_program_exit = 1;
                break;
            }
            }
            break;
        }
        }
    }
    return;
}
