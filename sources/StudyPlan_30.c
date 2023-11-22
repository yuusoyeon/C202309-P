#include <stdio.h>

#define MAX_SUBJECTS 10
#define MAX_DAYS 30

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

    // 전체 기간 계산 (한 회독에 필요한 일 수로 나누어 전체 일 수를 구함)
    totalDays = subjectCount * 3 * subjectCount;

    printf("\n[Study Plan]\n");

    // 로테이션 계획 출력
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

        if ((day % (3 * subjectCount)) == 0 && day != totalDays) {
            printf("\n");
        }
    }

    return 0;
}
