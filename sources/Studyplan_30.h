// Studyplan_30.h

#define STUDYPLAN_30_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SUBJECTS 10
#define MAX_DAYS 30
#define MAX_CONCEPTS 10
#define MAX 1000

// 구조체 정의: 과목 정보
struct Subject {
    char name[50];
    char examDate[20];
    char(*concepts)[50];       // 포인터로 동적으로 할당할 배열
    char(*definitions)[100];   // 포인터로 동적으로 할당할 배열
};

// 스택 구현 구조체 
typedef struct {
    int max;              // max: 스택의 최대 크기를 나타내는 정수
    int ptr;              // ptr: 스택의 현재 위치를 가리키는 정수
    int* stk;             // stk : 스택에 실제로 저장되는 정수 값들을 가리키는 포인터
} SubjectStack;

// 스택 초기화 함수
int Initialize(SubjectStack* s, int max);

// 스택 데이터 추가 함수
void Push(SubjectStack* s, int x);

// 스택 데이터 제거 함수
int Pop(SubjectStack* s, int* x);

// 스택 유지 함수
int Top(const SubjectStack* s, int* x);

// 두 날짜 간의 차이를 계산하는 함수
int calcDaysLeft(const char* currentDate, const char* examDate);

// 메뉴 출력 함수
void printMenu();

// 부족한 개념 입력 함수
void inputConcepts(struct Subject* subjects, int subjectCount);

// 메모리 해제 함수
void freeMemory(struct Subject* subjects, int subjectCount);

// 퀴즈 출력 함수 
int quizConcepts(struct Subject* subject, int subjectIndex);

// 일기장 작성 함수 
void openDiary();

// 할 일 수행 여부 입력 함수
void handleTodayTask(SubjectStack* stack, int* subjectIndex, const struct Subject* subjects, int subjectCount);

