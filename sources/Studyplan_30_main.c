#include "Studyplan_30.h"
#include <stddef.h>


#define MAX_SUBJECTS 10
#define MAX_DAYS 30
#define MAX_CONCEPTS 10

int main() {
    int subjectCount, totalDays;

    printf("시험을 보는 과목의 개수를 입력하세요: ");
    scanf_s("%d", &subjectCount);

    struct Subject* subjects = (struct Subject*)malloc(subjectCount * sizeof(struct Subject));
    if (subjects == NULL) {
        printf("메모리 할당 오류\n");
        return -1;
    }

    char examStartDate[20];
    printf("시험 기간의 시작 날짜를 입력하세요 (월일 형식, ex: 12월11일): ");
    scanf_s("%s", examStartDate, 20);

    for (int i = 0; i < subjectCount; ++i) {
        printf("과목 %d의 이름을 입력하세요: ", i + 1);
        if (scanf_s("%49s", subjects[i].name, sizeof(subjects[i].name)) != 1) {
            printf("Invalid input for subject name.\n");
            return -1; // or handle the error appropriately
        }

        printf("과목 %d의 시험 날짜를 입력하세요 (월일 형식, ex: 12월18일): ", i + 1);
        scanf_s("%19s", subjects[i].examDate, 20);

        subjects[i].concepts = (char(*)[50])malloc(MAX_CONCEPTS * sizeof(char[50]));
        subjects[i].definitions = (char(*)[100])malloc(MAX_CONCEPTS * sizeof(char[100]));

        if (subjects[i].concepts == NULL || subjects[i].definitions == NULL) {
            printf("Memory allocation error for subject %d.\n", i + 1);
            return -1; // or handle the error appropriately
        }
    }

    int menuChoice;
    char currentDate[20];
    do {
        printMenu();
        scanf_s("%d", &menuChoice);

        switch (menuChoice) {
        case 1:
            totalDays = MAX_DAYS;
            printf("\n[스터디 계획]\n");

            for (int day = 1; day <= totalDays; ++day) {
                int subjectIndex = (day - 1) % subjectCount;
                int rotationCount = ((day - 1) / (3 * subjectCount)) + 1;

                printf("Day %d: %s ", day, subjects[subjectIndex].name);

                switch ((day - 1) % 3) {
                case 0:
                    printf("%d회독\n", rotationCount);
                    break;
                case 1:
                    printf("%s 문제풀이&오답 체크\n", subjects[subjectIndex].name);
                    break;
                case 2:
                    printf("%s 백지 테스트\n", subjects[subjectIndex].name);
                    break;
                }

                if (day % 3 == 0) {
                    printf("\n");
                }
            }
            break;

        case 2:
            printf("오늘의 날짜를 입력하세요 (월일 형식, ex: 12월11일): ");
            scanf_s("%s", currentDate, 20);

            int daysElapsed = calcDaysLeft(currentDate, examStartDate);

            for (int i = 0; i < subjectCount; ++i) {
                int daysLeft = calcDaysLeft(examStartDate, subjects[i].examDate);
                printf("%s - %d일 남았습니다.\n", subjects[i].name, daysElapsed + daysLeft);
            }

            printf("\n[오늘의 계획]\n");

            int subjectIndex = (daysElapsed - 1) / 3 % subjectCount;

            printf("    %s ", subjects[subjectIndex].name);

            switch ((daysElapsed - 1) % 3) {
            case 0:
                printf("%d회독\n", ((daysElapsed - 1) / 3) + 1);
                break;
            case 1:
                printf("문제풀이&오답 체크\n");
                break;
            case 2:
                printf("백지 테스트\n");
                break;
            }

            printf("\n");

            break;

        case 3:
            inputConcepts(subjects, subjectCount);
            break;

        case 4:
            printf("과목을 선택하세요 (1부터 %d까지): ", subjectCount);
            int selectedSubjectIndex;
            scanf_s("%d", &selectedSubjectIndex);
            if (selectedSubjectIndex >= 1 && selectedSubjectIndex <= subjectCount) {
                printConcepts(&subjects[selectedSubjectIndex - 1]);
            }
            else {
                printf("잘못된 선택입니다.\n");
            }
            break;

        case 5:
            printf("오늘 일정을 미루시겠습니까? (Y/N): ");
            char choice;
            scanf_s(" %c", &choice, 1);

            if (choice == 'Y' || choice == 'y') {
                for (int i = MAX_DAYS - 1; i > 0; --i) {
                    subjects[(i - 1) / 3 % subjectCount].concepts[i % MAX_CONCEPTS][0] =
                        subjects[(i - 1) / 3 % subjectCount].concepts[(i - 1) % MAX_CONCEPTS][0];
                }
                printf("Day 30의 계획이 하루씩 뒤로 밀렸습니다.\n");
            }
            break;

        case 6:
            printf("프로그램을 종료합니다.\n");
            break;

        default:
            printf("잘못된 메뉴 선택입니다. 다시 선택하세요.\n");
        }

    } while (menuChoice != 6);

    freeMemory(subjects, subjectCount);
    free(subjects);

    return 0;
}
