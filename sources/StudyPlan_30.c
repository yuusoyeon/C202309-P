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
    sscanf_s(date, "%d��%d��", month, day);
}

int calcDaysLeft(const char* currentDate, const char* examDate) {
    struct tm currentTime, examTime;
    memset(&currentTime, 0, sizeof(struct tm));
    memset(&examTime, 0, sizeof(struct tm));

    sscanf_s(currentDate, "%d��%d��", &currentTime.tm_mon, &currentTime.tm_mday);
    currentTime.tm_mon -= 1;
    currentTime.tm_year = 2023 - 1900;

    sscanf_s(examDate, "%d��%d��", &examTime.tm_mon, &examTime.tm_mday);
    examTime.tm_mon -= 1;
    examTime.tm_year = 2023 - 1900;

    time_t currentTimestamp = mktime(&currentTime);
    time_t examTimestamp = mktime(&examTime);

    int daysLeft = (examTimestamp - currentTimestamp) / (60 * 60 * 24);
    return daysLeft;
}

void printMenu() {
    printf("\n[�޴�]\n");
    printf("1. 30�Ͽ� ��ȹ �����\n");
    printf("2. ������ D-day ��ȹ Ȯ���ϱ�\n");
    printf("3. ���� ���� �Է�\n");
    printf("4. ������ ���� Ȯ���ϱ�\n");
    printf("5. ���� ������ �̷�ðڽ��ϱ�? (Y/N)\n");
    printf("6. ����\n");
    printf("�޴��� �����ϼ���: ");
}

void inputConcepts(struct Subject* subjects, int subjectCount) {
    for (int i = 0; i < subjectCount; ++i) {
        printf("%s ������ �����ߴ� ������ �Է����ּ��� (�Է��� ��ġ���� q�� �Է��ϼ���):\n", subjects[i].name);

        for (int j = 0; j < MAX_CONCEPTS; ++j) {
            printf("�ܾ�: ");
            if (scanf_s("%s", subjects[i].concepts[j], 50) != 1 || subjects[i].concepts[j][0] == 'q') {
                break;
            }

            printf("����: ");
            scanf_s("%s", subjects[i].definitions[j], 100);
        }
    }
}

void printConcepts(struct Subject* subject) {
    printf("%s ������ ������ ����:\n", subject->name);
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
    printf("������ D-day�� �Է��ϼ���: ");
    scanf_s("%d", &userDday);

    // ��ȿ�� D-day ������ Ȯ��
    if (userDday < 1 || userDday > MAX_DAYS) {
        printf("D-day ���� �ƴմϴ�.\n");
        return;
    }

    printf("\n[Day %d�� ��ȹ]\n", userDday);

    for (int i = 0; i < subjectCount; ++i) {
        int remainingDays = userDday - daysElapsed;
        printf("%s - %d�� ���ҽ��ϴ�.\n", subjects[i].name, remainingDays);
    }
}

