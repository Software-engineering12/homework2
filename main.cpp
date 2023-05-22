//
//  main.cpp
//  소공 과제3
//
//  Created by Dongwan Ryoo on 2023/05/22.
//
// 헤더 선언
#include <stdio.h>
#include <string.h>

// 상수 선언
#define MAX_STRING 32
#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "output.txt"

// 함수 선언
void doTask();
void join();
void program_exit();

// 변수 선언
FILE* in_fp, *out_fp;

int main()
{
    in_fp = fopen("/Users/dongwanryoo/Downloads/input.txt", "r+");
    out_fp = fopen("/Users/dongwanryoo/Downloads/output.txt", "w+");
      
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
                        fprintf(out_fp, "1.1. 회원가입\n");
                        fprintf(out_fp, "완료");
                        break;
                    }
                    case 2:
                    {
                        fprintf(out_fp, "1.2. 회원탈퇴\n");
                        // Perform member withdrawal functionality
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
                        fprintf(out_fp, "2.1. 로그인\n");
                        // Perform login functionality
                        break;
                    }
                    case 2:
                    {
                        fprintf(out_fp, "2.2. 로그아웃\n");
                        // Perform logout functionality
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

void program_exit(){
    return;
}

