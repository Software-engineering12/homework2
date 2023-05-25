// 헤더 선언 (필요하면 추가로 선언)
#include <fstream>
#include <string.h>
#include<iostream>
#include<vector>

using namespace std;

// 상수 선언
#define MAX_STRING 32
#define INPUT_FILE_NAME "input.txt“
#define OUTPUT_FILE_NAME "output.txt"

//함수 선언
void doTask();
void program_exit();
void registerMember()
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
    string name; //회원 이름
    string memberType; //회원 타입 (일반 회원, 회사 회원 구분)
    string address; // 주소
    int phoneNumber; // 핸드폰 번호
    string id; // 회원 ID
    string password; // 비밀 번호
public:
    member(string n, string ad, string i, string p) {
        name = n;
        address = ad;
        id = i;
        password = p;
    }
    string getName() {
        return name;
    }
    string getAddress() {
        return address;
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
    int idNumber; // 주민 번호
    vector<RecruitmentInfo> recruitmentList;
public:
    GeneralMember(string n, string ad, string i, string p, int idN) :member(n, ad, i, p) {
        idNumber = idN;
    }
    vector<RecruitmentInfo> getRecruitmentList() {
        return recruitmentList;
    }
    void addRecruitment(RecruitmentInfo r) {
        recruitmentList.push_back(r);
    }
    
    //지원 취소 파트
    void removeRecruitment(Recruitment r) {
        for (auto it = recruitmentList.begin(); it != recruitmentList.end(); ++it) {
            if (r == &it) {
                recruitmentList.erase(it);
                break;
            }
        }
    }
};

class CompanyMember :public member {
private:
    RecruitmentInfo recruitment;
    RecruitmentInfo* currentRecrutitmetInfo = NULL;
    int businessNumber; // 사업자 번호
public:
    CompanyMember(string n, string ad, string i, string p, int bn, string bf) :member(n, ad, i, p) {
        businessNumber = bn;
        businessField = bf;
    }
    
    int getBusinessNumber() {
        return businessNumber;
    }
    string getBusinessField() {
        return businessField;
    }
    RecruitmentInfo getRecruitment() {
        return recruitment;
    }

    void addRecruitment(string job, string numberOfPeople, string applicationDeadLine) {
        recruitment.setJob = job;
        recruitment.setNumberOfPeople = numberOfPeople;
        recruitment.setApplicationDeadLine = applicationDeadLine;
    }
};

class RecruitmentInfo {
private:
    string job; // 업무
    int numberOfPeople; // 인원 수
    string applicationDeadLine; // 마감일
    bool deadLine; //마감 여부
public:
    RecruitmentInfo(string j, int n, string a, bool d = 0) {
        job = j;
        numberOfPeople = n;
        applicationDeadLine = a;
        deadLine = d;
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
    bool getDeadeLine() {
        return deadLine;
    }
    void setJob(string j) {
        job = j;
    }
    void setNumberOfPeople(int n) {
        numberOfPeople = n;
    }
    void setApplicationDeadLine(string a) {
        applicationDeadLine = a;
    }
    void setDeadLine(bool d) {
        deadLine = d;
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
//1.1 회원가입 
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

//1.2 회원탈퇴
class Unregister {
public:
    static void withdraw() {
        if (currentCompanyMember != NULL) {
            out_fp << currentCompanyMember->getId() << endl;
            companyMemberList.erase(currentCompanyMember);
        }
        if (currentGeneralMember != NULL) {
            out_fp<< currentGeneralMember->getId() << endl;
            generalMemberList.erase(currentCompanyMember);
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
        for (auto it = generalMemberList.begin(); it != generalMemberList.end(); ++it) {
            if (it->getId==id && it->getPassword==pw) {
                currentGeneralMember = it;
                out_fp << ">" << id << pw << \n;
            }
        }
        for (auto it = companyMemberList.begin(); it != companyMemberList.end(); ++it) {
            if (it->getId == id && it->getPassword == pw) {
                currentCompanyMember = it;
                out_fp << ">" << id << pw << \n;
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

//2.2 로그아웃
class Logout {
public:
    static void callLogout() {
        if (currentCompanyMember != NULL) currentCompanyMember = NULL;
        if (currentGeneralMember != NULL) currentGeneralMember = NULL;
    }
};
class LogoutUI {
public:
    static void selectLogoutUI() {
        Logout::callLogout();
    }
};

//3.1 채용 정보 등록
class addNewRecruitment {
public:
    static void add_Recruitment(string job, string numberOfPeople, string applicationDeadLine) {
        currentCompanyMember->addRecruitment(job, numberOfPeople, applicationDeadLine);
        out_fp << ">" << job  << numberOfPeople  << applicationDeadLine << \n;
    }
};
class addRecruitmentUI {
public:
    static void createRecruitment(string job, string numberOfPeople, string applicationDeadLine) {
        addNewRecruitment::add_Recruitment(job, numberOfPeople, applicationDeadLine);
    }

};

//3.2 등록된 채용 정보 조회
class GetRecruitmentInfoUI {
public:
    static void call_recruitmentinfo() {
        GetRecruitmentInfo::getRecruitment;
    }
};
class GetRecruitmentInfo {
public
    static void getRecruitment() {
    RecruitmentInfo r = currentCompanyMember->getRecruitment();
    out_fp << ">" << r.getJob() << r.getNumberOfPeople() << r.getApplicationDeadLine() << "\n";
    }
};

//4.1 채용 정보 검색

class RecruitmentSearchUI {
public:
    static void SearchRecritment() {
        string CompanyName;
        in_fp >> CompanyName;
        RecruitmentSearch::call_recruitmentSearch(CompanyName);
    }
};

class RecruitmentSearch {
public:
    static void call_recruitmentSearch(string name) {
        RecruitmentSearchInfo::recruitmentSearch(name);
    }
};
class RecruitmentSearchInfo{
public:
    static void recruitmentSearch(string name) {
        for (auto it = companyMemberList.begin(); it != companyMemberList.end(); ++it) {
            if (name = it->getName()) {
                RecruitmentInfo r = it->getRecruitment();
                out_fp << ">" << it->getName() << it->getBusinessNumber << r.getJob() << r.getNumberOfPeople() << r.getApplicationDeadLine() << "\n";
            }
        }
    }
};

//4.2 채용 지원
class ApplyForRecruitmentUI {
public:
    static void callApply() {
        int number;
        in_fp >> number;
        ApplyForRecruitment::apply(number);
    }
};

class ApplyForRecruitment {
public:
    static void apply(int number) {
        RecruitmentApply :: applyRecruitment(number);
    }
};
class RecruitmentApply {
public:
    static void applyRecruitment(int number)
    {
        for (auto it = companyMemberList.begin(); it != companyMemberList.end(); ++it) {
            if (name = it->getBusinessNumber()) {
                RecruitmentInfo r = it->getRecruitment();
                out_fp << ">" << it->getName() << it->getBusinessNumber << r.getJob() << "\n";
                currentGeneralMember->addRecruitment(r); 
            }
        }
    }
};

//4.3 지원 정보 조회
class GetApplicationInformationUI {
public:
    static void callGetApplicationInfo() {
        GetApplicationInformation::getApplicationInfo();
    }
};

class GetApplicationInformation {
public:
    static void getApplicationInfo() {
        ApplicationInformation::showAppInfo();
    }
};

class ApplicationInformation{
public:
    static void showAppInfo() {
        vector<RecruitmentInfo> list = currentGeneralMember->getRecruitmentList();
        //일반회원이 지원한 채용 리스트를 복제해온뒤
        for (auto it = companyMemberList.begin(); it != companyMemberList.end(); ++it) {
            for (auto i = list.begin(); i != list.end(); ++i) {
                if (it->getRecruitment() == &i) {//회사회원 전체를 스캔해 같은 채용이면 
                    out_fp << ">" << it->getName() << it->getBusinessNumber() << i->getJob() << i->getNumberOfPeople() << i->getApplicationDeadLine() << "\n";
                }
            }
        }
    }// 더 간단하게 할 수 있을것 같은데 방법을 잘 모르겠음
};

//4.4 지원 취소
class CancelApplicationInfo {
public:
    static void cancelApplication(string applicant) {
        vector<RecruitmentInfo> list = currentGeneralMember->getRecruitmentList();
        //일반회원이 지원한 채용 리스트를 복제해온뒤
        for (auto it = companyMemberList.begin(); it != companyMemberList.end(); ++it) {
            for (auto i = list.begin(); i != list.end(); ++i) {
                if (it->getRecruitment() == &i) {//회사회원 전체를 스캔해 같은 채용이면 
                    out_fp << ">" << it->getName() << it->getBusinessNumber() << i->getJob() << "\n";
                    currentGeneralMember->removeRecruitment(it->getRecruitment());
                }
            }
        }
    }// 더 간단하게 할 수 있을것 같은데 방법을 잘 모르겠음
    }
};
class CancelApplicationUI {
public:
    static void cancelCallApplication(string applicant) {
        CancelApplicationInfo::cancelApplication(applicant);
    }
};

//5.1 지원 정보 통계
class GetApplicationStatsUI {
public:
    static void showApplicationStats() {
        GetApplicationStatsInfo::getApplicationStats();
    }
};
class GetApplicationStatsInfo {
public:
    static void getApplicationStats() {
        string job;
        int count = 0;
        if (currentCompanyMember != NULL) {//회사회원이 로그인 상태일 경우
            for (auto it = generalMemberList.begin(); it != generalMemberList.end(); ++it) {
                vector<RecruitmentInfo> list = it->getRecruitmentList();
                for (auto i = list.begin(); i != list.end(); ++i) {
                    if (currentCompanyMember->addRecruitment() == &i) {
                        job = i->getJob();
                        count++;
                    }
                }
            }
            out_fp << ">" << job << count << "\n";
        }
        if (currentGeneralMember != NULL) {//일반회원이 로그인 상태일 경우
            vector<RecruitmentInfo> list = currentGeneralMember->getRecruitmentList();
            for (auto i = list.begin(); i != list.end(); ++i) {
                out_fp << ">" << i->getJob() << list.size();
            }
        }
    }
};

//함수 선언 했던 것들 구체화

//1.1 회원가입
void registerMember() {
    string name, number, ID, password,memberType;
    in_fp >> memberType>> name >> number >> ID >> password;

    if (memberType == 1) RegisterUI::selectgeneralRegisterUI(name, number, ID, password);
    if (memberType == 2) RegisterUI::selectcompanyRegisterUI(name, number, ID, password);
    out_fp <<"<"<<memberType<<"["<< name<<"][" << number<<"][" << ID<<"][" << password<<"]"\n;
};

//1.2 회원탈퇴 
void withdrawMember() {
    UnregisterUI::selectUnregisterUI();
};

//2.1 로그인 
void login() {
    string id, pw;
    in_fp >> id >> pw;
    LoginUI::selectLoginUI(id, pw);
};

//2.2 로그아웃
void logout() {
    LogoutUI::selectLogoutUI();
};

//3.1 채용 정보 등록
void addRecruitmentInfo() {
    string job, numberOfPeople, applicationDeadLine;
    in_fp >> job >> numberOfPeople >> applicationDeadLine;
    addRecruitmentUI::createRecruitment(job, numberOfPeople, applicationDeadLine);
}

//3.2 등록된 채용 정보 조회
void getRecruitment(){
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

//main
int main()
{
    // 파일 입출력을 위한 초기화
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
                out_fp << "6.1. 프로그램 종료\n";
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
}

void program_exit() {}
