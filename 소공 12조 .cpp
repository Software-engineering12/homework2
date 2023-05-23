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
void addRecruitmentInfo()
//3.2 등록된 채용 정보 조회
void getRecruitmentInfo()

//entity class ... 

class member{
private:
    string name;
    string memberType;
    string address;
    int phoneNumber;
    string id;
    string password;
public:
    member(string n,string ad,string i,string p){
        name=n;
        address=ad;
        id=i;
        password=p;
    }
    string getName(){
        return name;
    }
    string getAddress(){
        return address;
    }
    string getId(){
        return id;
    }
    string getPassword(){
        return password;
    }
}

class CeneralMember :public member{
private:
    int idNumber;
public:
    GeneralMember(string n,string ad,string i,string p,int idN):member(n,ad,i,p){
        idNumber=idN;
    }
}

class CompanyMember:public member{
private:
    int businessNumber;
    string businessField;
public:
    CompanyMember(string n,string ad,string i,string p,int bn,string bf):member(n,ad,i,p){
        businessNumber=bn;
        businessField=bf;
    }
}

class RecruitmentInfo{
private:
    string job;
    string numberOfPeople;
    string applicationDeadLine;
    bool deadLine; //필요할 것 같아서 선언함 지워도 됨
public:
    RecruitmentInfo(string j,string n,string a,bool d=0){
        job=j;
        numberOfPeople=n;
        applicationDeadLine=a;
        deadLine=d;
    }
    string getJob(){
        return job;
    }
    string getNumberOfPeople(){
        return numberOfPeople;
    }
    string getApplicationDeadLine(){
        return applicationDeadLine;
    }
    bool getDeadeLine(){
        return deadLine;
    }
}

// 변수 선언 (필요하면 추가로 선언 후 사용)
ifstream in_fp;
ofstream out_fp;
vector<GeneralMember> generalMemberList;
vector<CompanyMember> companyMemberList;
vector<RecruitmentInfo> recruitmentList;
GeneralMember *currentGeneralMember=NULL;
CompanyMember *currentCompanyMember=NULL;
RecruitmentInfo *currentRecrutitmetInfo=NULL;

//바운더리 클래스 컨트롤 클래스 ...
//1.1 회원가입 
class RegisterUI {}
class Register {}

//3.1 채용 정보 등록

class addRecruitment{
public:
    static void addRecruitment(string job,string numberOfPeople,string applicationDeadLine){
        currentRecrutitmetInfo->addRecruitment(job,numberOfPeople,applicationDeadLine);
    }
}

class addRecruitmentUI{
public:
    static void createRecruitment(string job,string numberOfPeople,string applicationDeadLine){
        addRecruitment::addRecruitment(job,numberOfPeople,applicationDeadLine);
    }
}
//3.2 등록된 채용 정보 조회

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
void addRecruitmentInfo(){
    string job,numberOfPeople,applicationDeadLine;
    in_fp>>job>>numberOfPeople>>applicationDeadLine;
    addRecruitmentUI::createRecruitment(job,numberOfPeople,applicationDeadLine);
    out_fp<<"3.1 채용 정보 등록\n"<<">["<<job<<"]["<<numberOfPeople<<"]["<<applicationDeadLine<<"]\n";
}
//3.2 등록된 채용 정보 조회


//main
int main()
{
    // 파일 입출력을 위한 초기화
    FILE* in_fp = fopen(INPUT_FILE_NAME, "r+");
    FILE* out_fp = fopen(OUTPUT_FILE_NAME, "w+");

    ...

        doTask();

    ...

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
        fscanf(in_fp, "%d %d ", &menu_level_1, &menu_level_2);


        // 메뉴 구분 및 해당 연산 수행
        switch (menu_level_1)
        {
        case 1:
        {
            switch (menu_level_2)
            {
            case 1:   // "1.1. 회원가입“ 메뉴 부분
            {
                // join() 함수에서 해당 기능 수행 
                join();

                break;
            }
            case 2:
            {
                ...
                    break;
            }
            }
            ....
        case 7:
            {
                switch (menu_level_2)
                {
                case 1:   // "6.1. 종료“ 메뉴 부분
                {
                    ..
                        program_exit();
                    is_program_exit = 1;
                    break;;
                }
                }

            }

            .......
        }

        return;
        }



        void program_exit()
        {
            ....
        }

