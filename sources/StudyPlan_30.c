#include "Studyplan_30.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stddef.h>


#define MAX_SUBJECTS 10
#define MAX_DAYS 30
#define MAX_CONCEPTS 10

void getMonthDay(const char* date, int* month, int* day) {
    sscanf_s(date, "%d월%d일", month, day);
}

int calcDaysLeft(const char* currentDate, const char* examDate) {
    struct tm currentTime, examTime;
    memset(&currentTime, 0, sizeof(struct tm));
    memset(&examTime, 0, sizeof(struct tm));

    sscanf_s(currentDate, "%d월%d일", &currentTime.tm_mon, &currentTime.tm_mday);
    currentTime.tm_mon -= 1;
    currentTime.tm_year = 2023 - 1900;

    sscanf_s(examDate, "%d월%d일", &examTime.tm_mon, &examTime.tm_mday);
    examTime.tm_mon -= 1;
    examTime.tm_year = 2023 - 1900;

    time_t currentTimestamp = mktime(&currentTime);
    time_t examTimestamp = mktime(&examTime);

    int daysLeft = (examTimestamp - currentTimestamp) / (60 * 60 * 24);
    return daysLeft;
}

void printMenu() {
    printf("\n[메뉴]\n");
    printf("1. 30일용 계획 세우기\n");
    printf("2. 오늘의 D-day 계획 확인하기\n");
    printf("3. 부족 개념 입력\n");
    printf("4. 부족한 개념 확인하기\n");
    printf("5. 오늘 일정을 미루시겠습니까? (Y/N)\n");
    printf("6. 종료\n");
    printf("메뉴를 선택하세요: ");
}

void inputConcepts(struct Subject* subjects, int subjectCount) {
    for (int i = 0; i < subjectCount; ++i) {
        printf("%s 과목의 부족했던 개념을 입력해주세요 (입력을 마치려면 q를 입력하세요):\n", subjects[i].name);

        for (int j = 0; j < MAX_CONCEPTS; ++j) {
            printf("단어: ");
            if (scanf_s("%s", subjects[i].concepts[j], 50) != 1 || subjects[i].concepts[j][0] == 'q') {
                break;
            }

            printf("정의: ");
            scanf_s("%s", subjects[i].definitions[j], 100);
        }
    }
}

void printConcepts(struct Subject* subject) {
    printf("%s 과목의 부족한 개념:\n", subject->name);
    for (int i = 0; i < MAX_CONCEPTS; ++i) {
        if (subject->concepts[i][0] == 'q') {
            break;
        }
        printf("%s - %s\n", subject->concepts[i], subject->definitions[i]);
    }
}

void freeMemory(struct Subject* subjects, int subjectCount) {
    for (int i = 0; i < subjectCount; ++i) {
        free(subjects[i].concepts);
        free(subjects[i].definitions);
    }
}

void printDdayPlan(struct Subject* subjects, int subjectCount, const char* currentDate, const char* examStartDate) {
    int daysElapsed = calcDaysLeft(currentDate, examStartDate);

    int userDday;
    printf("오늘의 D-day를 입력하세요: ");
    scanf_s("%d", &userDday);

    // 유효한 D-day 값인지 확인
    if (userDday < 1 || userDday > MAX_DAYS) {
        printf("D-day 값이 아닙니다.\n");
        return;
    }

    printf("\n[Day %d의 계획]\n", userDday);

    for (int i = 0; i < subjectCount; ++i) {
        int remainingDays = userDday - daysElapsed;
        printf("%s - %d일 남았습니다.\n", subjects[i].name, remainingDays);
    }
}

