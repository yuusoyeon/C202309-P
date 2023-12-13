#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SUBJECTS 10
#define MAX_DAYS 30
#define MAX_CONCEPTS 10

// 구조체 정의: 과목 정보
struct Subject {
    char name[50];
    char examDate[20];
    char(*concepts)[50];       // 포인터로 동적으로 할당할 배열
    char(*definitions)[100];   // 포인터로 동적으로 할당할 배열
};

// 월과 일을 분리하는 함수
void getMonthDay(const char* date, int* month, int* day) {
    sscanf_s(date, "%d월%d일", month, day);
}

// 두 날짜 간의 차이를 계산하는 함수
int calcDaysLeft(const char* currentDate, const char* examDate) {
    struct tm currentTime, examTime;
    memset(&currentTime, 0, sizeof(struct tm));
    memset(&examTime, 0, sizeof(struct tm));

    // 현재 날짜 설정
    sscanf_s(currentDate, "%d월%d일", &currentTime.tm_mon, &currentTime.tm_mday);
    currentTime.tm_mon -= 1;  // tm_mon은 0부터 시작하므로 1을 빼줍니다.
    currentTime.tm_year = 2023 - 1900;  // 현재 연도 설정 (2023년 기준)

    // 시험 날짜 설정
    sscanf_s(examDate, "%d월%d일", &examTime.tm_mon, &examTime.tm_mday);
    examTime.tm_mon -= 1;  // tm_mon은 0부터 시작하므로 1을 빼줍니다.
    examTime.tm_year = 2023 - 1900;  // 현재 연도 설정 (2023년 기준)

    time_t currentTimestamp = mktime(&currentTime);
    time_t examTimestamp = mktime(&examTime);

    // 두 날짜 간의 차이 계산
    int daysLeft = (examTimestamp - currentTimestamp) / (60 * 60 * 24);
    return daysLeft;
}

// 메뉴 출력 함수
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

// 부족한 개념 입력 함수
void inputConcepts(struct Subject* subjects, int subjectCount) {
    for (int i = 0; i < subjectCount; ++i) {
        printf("%s 과목의 부족했던 개념을 입력해주세요 (입력을 마치려면 q를 입력하세요):\n", subjects[i].name);

        for (int j = 0; j < MAX_CONCEPTS; ++j) {
            printf("단어: ");
            if (scanf_s("%s", subjects[i].concepts[j], 50) != 1 || subjects[i].concepts[j][0] == 'q') {
                // 'q'를 입력하면 입력 종료
                break;
            }

            printf("정의: ");
            scanf_s("%s", subjects[i].definitions[j], 100);
        }
    }
}

// 부족한 개념 출력 함수
void printConcepts(struct Subject* subject) {
    printf("%s 과목의 부족한 개념:\n", subject->name);
    for (int i = 0; i < MAX_CONCEPTS; ++i) {
        if (subject->concepts[i][0] == 'q') {
            break;
        }
        printf("%s - %s\n", subject->concepts[i], subject->definitions[i]);
    }
}

// 메모리 해제 함수
void freeMemory(struct Subject* subjects, int subjectCount) {
    for (int i = 0; i < subjectCount; ++i) {
        free(subjects[i].concepts);
        free(subjects[i].definitions);
    }
}

// 오늘의 D-day 계획 출력 함수
void printDdayPlan(struct Subject* subjects, int subjectCount, const char* currentDate, const char* examStartDate) {
    int daysElapsed = calcDaysLeft(currentDate, examStartDate);
    
}

int main() {
    int subjectCount, totalDays;

    // 과목 수 입력
    printf("시험을 보는 과목의 개수를 입력하세요: ");
    scanf_s("%d", &subjectCount);

    // 동적으로 할당된 Subject 구조체 배열
    struct Subject* subjects = (struct Subject*)malloc(subjectCount * sizeof(struct Subject));
    if (subjects == NULL) {
        printf("메모리 할당 오류\n");
        return -1;
    }

    // 과목의 시험 시작 날짜 입력
    char examStartDate[20];
    printf("시험 기간의 시작 날짜를 입력하세요 (월일 형식, ex: 12월11일): ");
    scanf_s("%s", examStartDate, 20);

    // 각 과목의 이름과 시험 날짜 입력
    for (int i = 0; i < subjectCount; ++i) {
        printf("과목 %d의 이름을 입력하세요: ", i + 1);
        scanf_s("%s", subjects[i].name, 50);

        printf("과목 %d의 시험 날짜를 입력하세요 (월일 형식, ex: 12월18일): ", i + 1);
        scanf_s("%s", subjects[i].examDate, 20);

        // 각 과목에 대해 동적으로 배열 할당
        subjects[i].concepts = (char(*)[50])malloc(MAX_CONCEPTS * sizeof(char[50]));
        subjects[i].definitions = (char(*)[100])malloc(MAX_CONCEPTS * sizeof(char[100]));
    }

    // 메뉴 선택 및 처리
    int menuChoice;
    char currentDate[20];
    do {

        printMenu();
        scanf_s("%d", &menuChoice);

        switch (menuChoice) {
        // 30일용 계획 세우기
        case 1:
            totalDays = MAX_DAYS;
            printf("\n[스터디 계획]\n");

            // 로테이션 계획 및 부족한 개념 출력
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
            // 오늘의 D-day 계획 확인하기
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
            // 부족 개념 입력
            inputConcepts(subjects, subjectCount);
            break;
        case 4:
            // 부족한 개념 확인하기
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
            // 오늘 일정을 미루시겠습니까?
            printf("오늘 일정을 미루시겠습니까? (Y/N): ");
            char choice;
            scanf_s(" %c", &choice, 1);

            if (choice == 'Y' || choice == 'y') {
                // Day 30의 전체 계획을 하루씩 뒤로 밀기
                for (int i = MAX_DAYS - 1; i > 0; --i) {
                    subjects[(i - 1) / 3 % subjectCount].concepts[i % MAX_CONCEPTS][0] =
                        subjects[(i - 1) / 3 % subjectCount].concepts[(i - 1) % MAX_CONCEPTS][0];
                }
                printf("Day 30의 계획이 하루씩 뒤로 밀렸습니다.\n");
            }
            break;
        case 6:
            // 종료
            printf("프로그램을 종료합니다.\n");
            break;
        default:
            printf("잘못된 메뉴 선택입니다. 다시 선택하세요.\n");
        }

    } while (menuChoice != 6);

    // 메모리 해제
    freeMemory(subjects, subjectCount);
    free(subjects);

    return 0;
}
