// Studyplan_30.h

#ifndef STUDYPLAN_30_H
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

typedef struct {
    int max;
    int ptr;
    int* stk;
} SubjectStack;

int Initialize(SubjectStack* s, int max);

void Push(SubjectStack* s, int x);

int Pop(SubjectStack* s, int* x);

int Top(const SubjectStack* s, int* x);

// 두 날짜 간의 차이를 계산하는 함수
int calcDaysLeft(const char* currentDate, const char* examDate);

// 메뉴 출력 함수
void printMenu();

// 부족한 개념 입력 함수
void inputConcepts(struct Subject* subjects, int subjectCount);

// 메모리 해제 함수
void freeMemory(struct Subject* subjects, int subjectCount);

// 오늘의 D-day 계획 출력 함수
void printDdayPlan(struct Subject* subjects, int subjectCount, const char* currentDate, const char* examStartDate);

// 퀴즈 출력 함수 
int quizConcepts(struct Subject* subject, int subjectIndex);

// 일기장 작성 함수 
void openDiary();

// 할 일 수행 여부 입력 함수
void handleTodayTask(SubjectStack* stack, int* subjectIndex, const struct Subject* subjects, int subjectCount);

#endif // STUDYPLAN_30_H
