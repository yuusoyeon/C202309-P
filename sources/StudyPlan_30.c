#include <stdio.h>

#define MAX_SUBJECTS 10
#define MAX_DAYS 30

int main() {
    int subjectCount, totalDays;

    // ���� �� �Է�
    printf("������ ���� ������ ������ �Է��ϼ���: ");
    scanf_s("%d", &subjectCount);

    // ������ ���� ��¥�� �����ϴ� �迭
    char subjects[MAX_SUBJECTS][50];
    char examDates[MAX_SUBJECTS][20];

    // �� ������ �̸��� ���� ��¥ �Է�
    for (int i = 0; i < subjectCount; ++i) {
        printf("���� %d�� �̸��� �Է��ϼ���: ", i + 1);
        scanf_s("%s", subjects[i], sizeof(subjects[i]));

        printf("���� %d�� ���� ��¥�� �Է��ϼ���: ", i + 1);
        scanf_s("%s", examDates[i], sizeof(examDates[i]));
    }

    // ��ü �Ⱓ ��� (�� ȸ���� �ʿ��� �� ���� ������ ��ü �� ���� ����)
    totalDays = subjectCount * 3 * subjectCount;

    printf("\n[Study Plan]\n");

    // �����̼� ��ȹ ���
    for (int day = 1; day <= MAX_DAYS && day <= totalDays; ++day) {
        int subjectIndex = ((day - 1) / 3) % subjectCount;

        printf("Day %d: %s ", day, subjects[subjectIndex]);

        switch ((day - 1) % 3) {
        case 0:
            printf("%dȸ��\n", ((day - 1) / (3 * subjectCount)) + 1);
            break;
        case 1:
            printf("����Ǯ��&���� üũ\n");
            break;
        case 2:
            printf("���� �׽�Ʈ\n");
            break;
        }

        if ((day % (3 * subjectCount)) == 0 && day != totalDays) {
            printf("\n");
        }
    }

    return 0;
}
