#include "Studyplan_30.h"

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

            // 로테이션 계획 출력
            for (int day = 1; day <= totalDays; ++day) {
                int subjectIndex = (day - 1) / 3 % subjectCount;
                int rotationCount = ((day - 1) / (3 * subjectCount)) + 1;

                printf("Day %d: %s ", day, subjects[subjectIndex].name);

                switch ((day - 1) % 3) {
                case 0:
                    printf("%d회독\n", rotationCount);
                    break;
                case 1:
                    printf("문제풀이&오답 체크\n");
                    break;
                case 2:
                    printf("백지 테스트\n");
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

            printf("\n[D-day 남은 일수]\n");

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
            // 부족한 개념 확인 및 퀴즈
            printf("과목을 선택하세요 (1부터 %d까지): ", subjectCount);
            int selectedSubjectIndex;
            scanf_s("%d", &selectedSubjectIndex);

            if (selectedSubjectIndex >= 1 && selectedSubjectIndex <= subjectCount) {
                int allCorrect = quizConcepts(&subjects[selectedSubjectIndex - 1]);
                if (allCorrect) {
                    printf("일기장을 여시겠습니까? (1: 예, 0: 아니오): ");
                    int openDiaryChoice;
                    scanf_s("%d", &openDiaryChoice);

                    if (openDiaryChoice == 1) {
                        openDiary();
                    }
                }
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
