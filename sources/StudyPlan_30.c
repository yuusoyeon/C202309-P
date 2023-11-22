#include <stdio.h>

#define MAX_SUBJECTS 10
#define MAX_DAYS 30
#define MAX_CONCEPTS 10

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

    // ������ ������ �����ϴ� �迭
    char concepts[MAX_SUBJECTS][MAX_CONCEPTS][50];
    char definitions[MAX_SUBJECTS][MAX_CONCEPTS][100];

    // ������ ���� �Է�
    for (int i = 0; i < subjectCount; ++i) {
        printf("%s ������ �����ߴ� ������ �Է����ּ��� (�Է��� ��ġ���� q�� �Է��ϼ���):\n", subjects[i]);

        for (int j = 0; j < MAX_CONCEPTS; ++j) {
            printf("�ܾ�: ");
            if (scanf_s("%s", concepts[i][j], sizeof(concepts[i][j])) != 1 || concepts[i][j][0] == 'q') {
                // 'q'�� �Է��ϸ� �Է� ����
                break;
            }

            printf("����: ");
            scanf_s("%s", definitions[i][j], sizeof(definitions[i][j]));
        }
    }

    // ��ü �Ⱓ ��� (�� ȸ���� �ʿ��� �� ���� ������ ��ü �� ���� ����)
    totalDays = subjectCount * 3 * subjectCount;

    printf("\n[Study Plan]\n");

    // �����̼� ��ȹ �� ������ ���� ���
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

        // ������ ���� ���
        printf("������ ����: ");
        for (int i = 0; i < MAX_CONCEPTS; ++i) {
            // 'q' �Է��̸� ��� �ߴ�
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