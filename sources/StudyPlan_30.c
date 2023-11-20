#include <stdio.h>

int main() {
    int subjectCount, totalDays;

    // ���� �� �Է�
    printf("������ ���� ������ ������ �Է��ϼ���: ");
    scanf_s("%d", &subjectCount);

    // ��ü �Ⱓ ��� (�� ȸ���� �ʿ��� �� ���� ������ ��ü �� ���� ����)
    totalDays = subjectCount * 3 * subjectCount;

    printf("\n[Study Plan]\n");

    // �����̼� ��ȹ ���
    for (int day = 1; day <= 30 && day <= totalDays; ++day) {
        char subject = 'A' + ((day - 1) / 3) % subjectCount;

        printf("Day %d: ", day);

        switch ((day - 1) % 3) {
        case 0:
            printf("%c %dȸ��\n", subject, ((day - 1) / (3 * subjectCount)) + 1);
            break;
        case 1:
            printf("%c ����Ǯ��&���� üũ\n", subject);
            break;
        case 2:
            printf("%c ���� �׽�Ʈ\n", subject);
            break;
        }

        if ((day % (3 * subjectCount)) == 0 && day != totalDays) {
            printf("\n");
        }
    }

    return 0;
}
