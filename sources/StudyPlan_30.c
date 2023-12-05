#include "Studyplan_30.h"
#include <stdio.h>
#include <stdlib.h>

void printMenu() {
    printf("\n[�޴�]\n");
    printf("1. 30�Ͽ� ��ȹ �����\n");
    printf("2. ������ D-day ��ȹ Ȯ���ϱ�\n");
    printf("3. ���� ���� �Է�\n");
    printf("4. ������ ���� Ȯ���ϱ�\n");
    printf("5. ���� ������ �̷�ðڽ��ϱ�? (Y/N)\n");
    printf("6. ����\n");
    printf("�޴��� �����ϼ���: ");
}

void inputConcepts(struct Subject* subjects, int subjectCount) {
    for (int i = 0; i < subjectCount; ++i) {
        printf("%s ������ �����ߴ� ������ �Է����ּ��� (�Է��� ��ġ���� q�� �Է��ϼ���):\n", subjects[i].name);

        for (int j = 0; j < MAX_CONCEPTS; ++j) {
            printf("�ܾ�: ");
            if (scanf_s("%s", subjects[i].concepts[j], 50) != 1 || subjects[i].concepts[j][0] == 'q') {
                // 'q'�� �Է��ϸ� �Է� ����
                break;
            }

            printf("����: ");
            scanf_s("%s", subjects[i].definitions[j], 100);
        }
    }
}

void printConcepts(struct Subject* subject) {
    printf("%s ������ ������ ����:\n", subject->name);
    for (int i = 0; i < MAX_CONCEPTS; ++i) {
        if (subject->concepts[i][0] == 'q') {
            break;
        }
        printf("%s - %s\n", subject->concepts[i], subject->definitions[i]);
    }
}

void freeMemory(struct Subject* subjects, int subjectCount) {
    for (int i = 0; i < subjectCount; ++i) {
        free(subjects[i].concepts);
        free(subjects[i].definitions);
    }
}

void printDdayPlan(struct Subject* subjects, int subjectCount, int dDay) {
    printf("\n[Day %d�� ��ȹ]\n", dDay);

    for (int day = 1; day <= dDay; ++day) {
        int subjectIndex = (day - 1) / 3 % subjectCount;

        printf("    %s ", subjects[subjectIndex].name);

        switch ((day - 1) % 3) {
        case 0:
            printf("%dȸ��\n", ((day - 1) / 3) + 1);
            break;
        case 1:
            printf("����Ǯ��&���� üũ\n");
            break;
        case 2:
            printf("���� �׽�Ʈ\n");
            break;
        }

        if (day % 3 == 0) {
            printf("\n");
        }
    }
}
