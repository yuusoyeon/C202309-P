#include <stdio.h>

#define MAX_SUBJECTS 10
#define MAX_DAYS 30
#define MAX_CONCEPTS 10

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

    // 전체 기간 계산 (한 회독에 필요한 일 수로 나누어 전체 일 수를 구함)
    totalDays = subjectCount * 3 * subjectCount;

    printf("\n[Study Plan]\n");

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

    return 0;
}