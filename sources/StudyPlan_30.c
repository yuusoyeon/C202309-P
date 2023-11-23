#include <stdio.h>

#define MAX_SUBJECTS 10
#define MAX_DAYS 30
#define MAX_CONCEPTS 10

// 메뉴 출력 함수
void printMenu() {
    printf("\n[메뉴]\n");
    printf("1. 30일용 계획 세우기\n");
    printf("2. 부족 개념 입력\n");
    printf("3. 수행 여부 입력하기\n");
    printf("4. 종료\n");
    printf("메뉴를 선택하세요: ");
}

int main() {
    int subjectCount, totalDays;

    // 과목 수 입력
    printf("시험을 보는 과목의 개수를 입력하세요: ");
    scanf_s("%d", &subjectCount);

    // 과목명과 시험 날짜를 저장하는 배열
    char subjects[MAX_SUBJECTS][50];
    char examDates[MAX_SUBJECTS][20];

    // 각 과목의 이름과 시험 날짜 입력
    for (int i = 0; i < subjectCount; ++i) {
        printf("과목 %d의 이름을 입력하세요: ", i + 1);
        scanf_s("%s", subjects[i], sizeof(subjects[i]));

        printf("과목 %d의 시험 날짜를 입력하세요: ", i + 1);
        scanf_s("%s", examDates[i], sizeof(examDates[i]));
    }

    // 부족한 개념을 저장하는 배열
    char concepts[MAX_SUBJECTS][MAX_CONCEPTS][50];
    char definitions[MAX_SUBJECTS][MAX_CONCEPTS][100];

    // 부족한 개념 입력
    for (int i = 0; i < subjectCount; ++i) {
        printf("%s 과목의 부족했던 개념을 입력해주세요 (입력을 마치려면 q를 입력하세요):\n", subjects[i]);

        for (int j = 0; j < MAX_CONCEPTS; ++j) {
            printf("단어: ");
            if (scanf_s("%s", concepts[i][j], sizeof(concepts[i][j])) != 1 || concepts[i][j][0] == 'q') {
                // 'q'를 입력하면 입력 종료
                break;
            }

            printf("정의: ");
            scanf_s("%s", definitions[i][j], sizeof(definitions[i][j]));
        }
    }

    // 메뉴 선택 및 처리
    int menuChoice;
    do {
        printMenu();
        scanf_s("%d", &menuChoice);

        switch (menuChoice) {
        case 1:
            // 30일용 계획 세우기
            totalDays = subjectCount * 3 * subjectCount;
            printf("\n[스터디 계획]\n");

            // 로테이션 계획 및 부족한 개념 출력
            for (int day = 1; day <= MAX_DAYS && day <= totalDays; ++day) {
                int subjectIndex = ((day - 1) / 3) % subjectCount;

                printf("Day %d: %s ", day, subjects[subjectIndex]);

                switch ((day - 1) % 3) {
                case 0:
                    printf("%d회독\n", ((day - 1) / (3 * subjectCount)) + 1);
                    break;
                case 1:
                    printf("문제풀이&오답 체크\n");
                    break;
                case 2:
                    printf("백지 테스트\n");
                    break;
                }

                // 부족한 개념 출력
                printf("부족한 개념: ");
                for (int i = 0; i < MAX_CONCEPTS; ++i) {
                    // 'q' 입력이면 출력 중단
                    if (concepts[subjectIndex][i][0] == 'q') {
                        break;
                    }
                    printf("%s - %s ", concepts[subjectIndex][i], definitions[subjectIndex][i]);
                }

                if ((day % (3 * subjectCount)) == 0 && day != totalDays) {
                    printf("\n");
                }
            }
            break;
        case 2:
            // 부족 개념 입력
            // TODO: 구현 필요
            break;
        case 3:
            // 수행 여부 입력하기
            // TODO: 구현 필요
            break;
        case 4:
            // 종료
            printf("프로그램을 종료합니다.\n");
            break;
        default:
            printf("잘못된 메뉴 선택입니다. 다시 선택하세요.\n");
        }

    } while (menuChoice != 4);

    return 0;
}

