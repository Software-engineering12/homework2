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


void doTask();
void program_exit();
/* 함수 선언
void join(); //1.1 회원가입
             //1.2 회원탈퇴
...          //2.1 로그인
             //2.2 로그아웃
             ..이런식으로 함수이름 뒤에 주석 기입 번호와 함께
*/
//3.1 채용 정보 등록
void addRecruitmentInfo();
//3.2 등록된 채용 정보 조회
void getRecruitment();
//4.4 지원 취소
void removeApplicant(const string& applicant);

//entity class ... 

class member {
private:
    string name;
    string memberType;
    string address;
    int phoneNumber;
    string id;
    string password;
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
    int idNumber;
    vector<RecruitmentInfo> recruitmentList;
    RecruitmentInfo* currentRecrutitmetInfo = NULL;
public:
    GeneralMember(string n, string ad, string i, string p, int idN) :member(n, ad, i, p) {
        idNumber = idN;
    }
    //지원자 삭제
    void removeApplicant(const string& applicant) {
        for (auto it = recruitmentList.begin(); it != recruitmentList.end(); ++it) {
            if (*it == applicant) {
                applicants.erase(it);
                break;
            }
        }
    }
    void getapplyInfo(GeneralMember* M); // 지원 정보 조회 
};

class CompanyMember :public member {
private:
    int businessNumber;
    string businessField;
    vector<RecruitmentInfo> recruitmentList;
    RecruitmentInfo* currentRecrutitmetInfo = NULL;
public:
    CompanyMember(string n, string ad, string i, string p, int bn, string bf) :member(n, ad, i, p) {
        businessNumber = bn;
        businessField = bf;
    }
    void addRecruitment(int businessNumber, string job, string numberOfPeople, string applicationDeadLine) {
        RecruitmentInfo r(businessNumber, job, numberOfPeople, applicationDeadLine);
        recruitmentList.push_back(r);
    }
    vector<RecruitmentInfo> getRecruitmentList() {
        return recruitmentList;
    }
    int getbusinessNumber() {
        return businessNumber;
    }
};

class RecruitmentInfo {
private:
    int businessNumber;
    string job;
    string numberOfPeople;
    string applicationDeadLine;
    string businessField;
    bool deadLine;
    vector<string> applicants; // 지원자 목록 백터 추가
public:
    RecruitmentInfo(int p, string j, string n, string a, bool d = 0) {
        businessNumber = p;
        job = j;
        numberOfPeople = n;
        applicationDeadLine = a;
        deadLine = d;
    }
    int getbusinessNumber() {
        return businessNumber;
    }
    string getJob() {
        return job;
    }
    string getNumberOfPeople() {
        return numberOfPeople;
    }
    string getApplicationDeadLine() {
        return applicationDeadLine;
    }
    bool getDeadeLine() {
        return deadLine;
    }
};
class ApplyList {
private:
    string ID;
    string CompanyName;
    string job;
    string numofpeople;
    string deadline;
    int businessNumber;
public:
    ApplyList(string num, string name, string Do, string n, string d, int idnum) {
        ID = num;
        CompanyName = name;
        job = Do;
        numofpeople = n;
        deadline = d;
        businessNumber = idnum;
    };
    string getID() {
        return ID;
    };
    string getCompanyName() {
        return CompanyName;
    };
    string getjob() {
        return job;
    };
    string getnumofpeople() {
        return numofpeople;
    };
    string getdeadline() {
        return deadline;
    };
    int getbusinessNumber() {
        return businessNumber;
    };
};// 일반 멤버의 지원 정보를 저장하는 리스트


// 변수 선언 (필요하면 추가로 선언 후 사용)
ifstream in_fp;
ofstream out_fp;
vector<GeneralMember> generalMemberList;
vector<CompanyMember> companyMemberList;
vector<RecruitmentInfo> recruitmentList;
GeneralMember* currentGeneralMember = NULL;
CompanyMember* currentCompanyMember = NULL;
vector<ApplyList> GeneralApplyList;

//바운더리 클래스 컨트롤 클래스 ...
//1.1 회원가입 
class RegisterUI {};
class Register {};

//3.1 채용 정보 등록

class addNewRecruitment {
public:
    static void addRecruitment(string job, string numberOfPeople, string applicationDeadLine) {
        currentCompanyMember->addRecruitment(job, numberOfPeople, applicationDeadLine);
    }
};

class addRecruitmentUI {
public:
    static void createRecruitment(string job, string numberOfPeople, string applicationDeadLine) {
        addNewRecruitment::addRecruitment(job, numberOfPeople, applicationDeadLine);
    }

};
//3.2 등록된 채용 정보 조회
class GetRecruitmentInfoUI {
public:
    static void call_recruitmentinfo() {
        GetRecruitmentInfoUI::getRecruitment;
    };

    class GetRecruitmentInfo {
        recruitmentList = currentCompanyMember->getRecruitmentList;
        for (auto it = recruitmentList.begin(); it != recruitmentList.end(); ++it)
        {

        }
    }
};

//4.1 채용 정보 검색
class RecruitmentSearchUI {
public:
    void Search();
};// 바운더리
class RecruitmentSearch {
public:
    RecruitmentSearch() {};
    void ShowInfo();
}; // 컨트롤
class Recruitmentapply {
public:
    Recruitmentapply() {};
    void searchRecruitmentInfo(string name);
    void applyRecruitment(int ID);
}; // 엔티티
void RecruitmentSearchUI::Search() {
    RecruitmentSearch *Search;
    Search->ShowInfo();
};
void RecruitmentSearch::ShowInfo() {
    string name;
    in_fp >> name;
    Recruitmentapply apply;
    apply.
};
void Recruitmentapply::searchRecruitmentInfo(string name) {
    int CompanyNumber;
    string cname;
    string cwork;
    string NumOfPeople;
    string Deadline;
    for (int i = 0;i < companyMemberList.size();i++) { // CompanyMemberList에서 이름을 비교해서 사업자 번호를 얻는다.
        if (name == companyMemberList[i].getName()) {
            cname = companyMemberList[i].getName();
            CompanyNumber = companyMemberList[i].getbusinessNumber();
        };
        break;
    };
    for (int i = 0;i < recruitmentList.size();i++) { // 얻은 사업자 번호를 통해 recruitmentList에서 채용 정보를 얻는다.
        if (CompanyNumber == recruitmentList[i].getbusinessNumber()) {
            cwork = recruitmentList[i].getJob();
            NumOfPeople = recruitmentList[i].getNumberOfPeople();
            Deadline = recruitmentList[i].getApplicationDeadLine();
        };
        break;
    };
    out_fp << cname << CompanyNumber << cwork << NumOfPeople << Deadline << endl;
};

//4.2 채용 지원
class ApplyForRecruitmentUI {
public:
    void ApplyInput();
}; // 바운더리
class ApplyForRecruitment {
public:
    ApplyForRecruitment() {};
    void Apply();
}; // 컨트롤

void ApplyForRecruitmentUI::ApplyInput() {
    ApplyForRecruitment* App;
    App->Apply();
}; 
void ApplyForRecruitment::Apply() {
    int CompanyNumber;
    in_fp >> CompanyNumber;
    Recruitmentapply* recruit;
    recruit->applyRecruitment(CompanyNumber);
};
void Recruitmentapply::applyRecruitment(int ID) { 
    string CompanyName;
    int CompanyNumber;
    string Job;
    string userID;
    string numofpeople;
    string deadline;
    CompanyNumber = ID;
    for (int i = 0;i < recruitmentList.size();i++) {
        if (CompanyNumber == recruitmentList[i].getbusinessNumber()) { //입력받은 사업자 번호를 통해 채용 리스트에서 정보를 가져온다.
            Job = recruitmentList[i].getJob();
            deadline = recruitmentList[i].getApplicationDeadLine();
            numofpeople = recruitmentList[i].getNumberOfPeople();
        };
        break;
    };
    for (int i = 0;i < companyMemberList.size();i++) {
        if (CompanyNumber == companyMemberList[i].getbusinessNumber()) {
            CompanyName = companyMemberList[i].getName();
        };
        break;
    };
    userID = currentGeneralMember->getId();
    ApplyList A(userID, CompanyName, Job, numofpeople, deadline, CompanyNumber); // 일반 회원의 지원 정보 리스트에 해당 지원 정보를 입력한다.
    GeneralApplyList.push_back(A);
    out_fp << CompanyName << CompanyNumber << Job << endl;
};

//4.3 지원 정보 조회
class GetApplicationInformationUI {
public:
    void GetApplicationInfo();
}; // 바운더리

class GetApplicationInformation {
public:
    GetApplicationInformation() {};
    void ShowAppInfo();
}; // 컨트롤
void GetApplicationInformationUI::GetApplicationInfo() {
    GetApplicationInformation* GetApp;
    GetApp->ShowAppInfo();
};
void GetApplicationInformation::ShowAppInfo() {
    GeneralMember* General;
    General->getapplyInfo(currentGeneralMember);
};
void GeneralMember::getapplyInfo(GeneralMember* general) {
    string CompanyName;
    int CompanyNumber;
    string Job;
    string numOfpeople;
    string deadline;
    for (int i = 0;i < GeneralApplyList.size();i++) { // 현재 접속중인 회원의 정보 (currentGeneralMember)를 통해 지원 정보 리스트를 가져와 출력한다.
        if (general->getId() == GeneralApplyList[i].getID()) {
            CompanyName = GeneralApplyList[i].getCompanyName();
            CompanyNumber = GeneralApplyList[i].getbusinessNumber();
            Job = GeneralApplyList[i].getjob();
            numOfpeople = GeneralApplyList[i].getnumofpeople();
            deadline = GeneralApplyList[i].getdeadline();
        };
        break;
    };
    out_fp << CompanyName << CompanyNumber << Job << numOfpeople << deadline << endl;
};



//4.4 지원 취소
class CancelApplication {
public:
    static void cancelApplication(const string& applicant) {
        currentGeneralMember->cancelApplication(applicant);
    }
};
class CancelApplicationUI {
public:
    static void cancelApplication(const string& applicant) {
        CancelApplication::cancelApplication(applicant);
    }
};

//함수 선언 했던 것들 구체화
//1.1 회원가입
void join() {
    string name, address, ID, password;
    in_fp >> name >> address >> ID >> password;

    out_fp << "1.1 회원가입\n";
    out_fp << name << ID;
    //과제 입출력 참고..
}

//1.2 회원탈퇴..

//3.1 채용 정보 등록
void addRecruitmentInfo() {
    string job, numberOfPeople, applicationDeadLine;
    in_fp >> job >> numberOfPeople >> applicationDeadLine;
    addRecruitmentUI::createRecruitment(job, numberOfPeople, applicationDeadLine);
    out_fp << ">[" << job << "][" << numberOfPeople << "][" << applicationDeadLine << "]\n";
}
//3.2 등록된 채용 정보 조회
void getRecruitment() {

}

//4.4 지원 취소
void removeApplicant(const string& applicant) {
    for (auto it = applicants.begin(); it != applicants.end(); ++it) {
        if (*it == applicant) {
            applicants.erase(it);
            break;
        }
    }
}

//main
int main()
{
    // 파일 입출력을 위한 초기화
    in_fp.open(INPUT_FILE_NAME);
    out_fp.open(OUTPUT_FILE_NAME);
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
                break;
            }
            case 2:
            {
                out_fp << "1.2. 회원탈퇴\n";
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
                break;
            }
            case 2:
            {
                out_fp << "2.2. 로그아웃\n";

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

                break;
            }
            case 2:
            {
                out_fp << "4.2. 채용 지원\n";

                break;
            }
            case 3:
            {
                out_fp << "4.3. 지원 정보 조회\n";

                break;
            }
            case 4:
            {
                out_fp << "4.4. 지원 취소\n";

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
