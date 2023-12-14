// Studyplan_30.h

#ifndef STUDYPLAN_30_H
#define STUDYPLAN_30_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

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

// 월과 일을 분리하는 함수
void getMonthDay(const char* date, int* month, int* day);

// 두 날짜 간의 차이를 계산하는 함수
int calcDaysLeft(const char* currentDate, const char* examDate);

// 메뉴 출력 함수
void printMenu();

// 부족한 개념 입력 함수
void inputConcepts(struct Subject* subjects, int subjectCount);

// 부족한 개념 출력 함수
void printConcepts(struct Subject* subject);

// 메모리 해제 함수
void freeMemory(struct Subject* subjects, int subjectCount);

// 오늘의 D-day 계획 출력 함수
void printDdayPlan(struct Subject* subjects, int subjectCount, const char* currentDate, const char* examStartDate);

int quizConcepts(struct Subject* subject);

#endif // STUDYPLAN_30_H
