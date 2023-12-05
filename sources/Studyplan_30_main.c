#include "Studyplan_30.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    int subjectCount, totalDays;

    // ���� �� �Է�
    printf("������ ���� ������ ������ �Է��ϼ���: ");
    scanf_s("%d", &subjectCount);

    // �������� �Ҵ�� Subject ����ü �迭
    struct Subject* subjects = (struct Subject*)malloc(subjectCount * sizeof(struct Subject));
    if (subjects == NULL) {
        printf("�޸� �Ҵ� ����\n");
        return -1;
    }

    // �� ������ �̸��� ���� ��¥ �Է�
    for (int i = 0; i < subjectCount; ++i) {
        printf("���� %d�� �̸��� �Է��ϼ���: ", i + 1);
        scanf_s("%s", subjects[i].name, 50);

        printf("���� %d�� ���� ��¥�� �Է��ϼ���: ", i + 1);
        scanf_s("%s", subjects[i].examDate, 20);

        // �� ���� ���� �������� �迭 �Ҵ�
        subjects[i].concepts = (char(*)[50])malloc(MAX_CONCEPTS * sizeof(char[50]));
        subjects[i].definitions = (char(*)[100])malloc(MAX_CONCEPTS * sizeof(char[100]));
    }

    // �޴� ���� �� ó��
    int menuChoice;
    int dDay = 0;  // D-day ���� �ʱ�ȭ
    do {
        printMenu();
        scanf_s("%d", &menuChoice);

        switch (menuChoice) {
        case 1:
            // 30�Ͽ� ��ȹ �����
            totalDays = MAX_DAYS;
            printf("\n[���͵� ��ȹ]\n");

            // �����̼� ��ȹ �� ������ ���� ���
            for (int day = 1; day <= totalDays; ++day) {
                int subjectIndex = (day - 1) / 3 % subjectCount;

                printf("Day %d: %s ", day, subjects[subjectIndex].name);

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
            break;
        case 2:
            // ������ D-day ��ȹ Ȯ���ϱ�
            printf("������ D-day�� �Է��ϼ���: ");
            scanf_s("%d", &dDay);
            printDdayPlan(subjects, subjectCount, dDay);
            break;

        case 3:
            // ���� ���� �Է�
            inputConcepts(subjects, subjectCount);
            break;
        case 4:
            // ������ ���� Ȯ���ϱ�
            printf("������ �����ϼ��� (1���� %d����): ", subjectCount);
            int subjectIndex;
            scanf_s("%d", &subjectIndex);
            if (subjectIndex >= 1 && subjectIndex <= subjectCount) {
                printConcepts(&subjects[subjectIndex - 1]);
            }
            else {
                printf("�߸��� �����Դϴ�.\n");
            }
            break;
        case 5:
            // ���� ������ �̷�ðڽ��ϱ�?
            printf("���� ������ �̷�ðڽ��ϱ�? (Y/N): ");
            char choice;
            scanf_s(" %c", &choice, 1);

            if (choice == 'Y' || choice == 'y') {
                // Day 30�� ��ü ��ȹ�� �Ϸ羿 �ڷ� �б�
                for (int i = MAX_DAYS - 1; i > 0; --i) {
                    subjects[(i - 1) / 3 % subjectCount].concepts[i % MAX_CONCEPTS][0] =
                        subjects[(i - 1) / 3 % subjectCount].concepts[(i - 1) % MAX_CONCEPTS][0];
                }
                printf("Day 30�� ��ȹ�� �Ϸ羿 �ڷ� �зȽ��ϴ�.\n");

            }
            break;
        case 6:
            // ����
            printf("���α׷��� �����մϴ�.\n");
            break;
        default:
            printf("�߸��� �޴� �����Դϴ�. �ٽ� �����ϼ���.\n");
        }

    } while (menuChoice != 6);

    // �޸� ����
    freeMemory(subjects, subjectCount);
    free(subjects);

    return 0;
}
