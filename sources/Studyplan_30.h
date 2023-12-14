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

// ����ü ����: ���� ����
struct Subject {
    char name[50];
    char examDate[20];
    char(*concepts)[50];       // �����ͷ� �������� �Ҵ��� �迭
    char(*definitions)[100];   // �����ͷ� �������� �Ҵ��� �迭
};

// ���� ���� �и��ϴ� �Լ�
void getMonthDay(const char* date, int* month, int* day);

// �� ��¥ ���� ���̸� ����ϴ� �Լ�
int calcDaysLeft(const char* currentDate, const char* examDate);

// �޴� ��� �Լ�
void printMenu();

// ������ ���� �Է� �Լ�
void inputConcepts(struct Subject* subjects, int subjectCount);

// ������ ���� ��� �Լ�
void printConcepts(struct Subject* subject);

// �޸� ���� �Լ�
void freeMemory(struct Subject* subjects, int subjectCount);

// ������ D-day ��ȹ ��� �Լ�
void printDdayPlan(struct Subject* subjects, int subjectCount, const char* currentDate, const char* examStartDate);

int quizConcepts(struct Subject* subject);

#endif // STUDYPLAN_30_H
