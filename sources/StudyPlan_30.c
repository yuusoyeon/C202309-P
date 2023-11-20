#include <stdio.h>

int main() {
    int subjectCount, totalDays;

    // 과목 수 입력
    printf("시험을 보는 과목의 개수를 입력하세요: ");
    scanf_s("%d", &subjectCount);

    // 전체 기간 계산 (한 회독에 필요한 일 수로 나누어 전체 일 수를 구함)
    totalDays = subjectCount * 3 * subjectCount;

    printf("\n[Study Plan]\n");

    // 로테이션 계획 출력
    for (int day = 1; day <= 30 && day <= totalDays; ++day) {
        char subject = 'A' + ((day - 1) / 3) % subjectCount;

        printf("Day %d: ", day);

        switch ((day - 1) % 3) {
        case 0:
            printf("%c %d회독\n", subject, ((day - 1) / (3 * subjectCount)) + 1);
            break;
        case 1:
            printf("%c 문제풀이&오답 체크\n", subject);
            break;
        case 2:
            printf("%c 백지 테스트\n", subject);
            break;
        }

        if ((day % (3 * subjectCount)) == 0 && day != totalDays) {
            printf("\n");
        }
    }

    return 0;
}
