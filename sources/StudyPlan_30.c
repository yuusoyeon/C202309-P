#include <stdio.h>
#include <stdlib.h>

#define MAX_SUBJECTS 10
#define MAX_DAYS 30
#define MAX_CONCEPTS 10

// ����ü ����: ���� ����
struct Subject {
    char name[50];
    char examDate[20];
    char(*concepts)[50];       // �����ͷ� �������� �Ҵ��� �迭
    char(*definitions)[100];   // �����ͷ� �������� �Ҵ��� �迭
};

// �޴� ��� �Լ�
void printMenu() {
    printf("\n[�޴�]\n");
    printf("1. 30�Ͽ� ��ȹ �����\n");
    printf("2. ���� ���� �Է�\n");
    printf("3. ������ ���� Ȯ���ϱ�\n");
    printf("4. ���� ������ �̷�ðڽ��ϱ�? (Y/N)\n");
    printf("5. ������ D-day ��ȹ Ȯ���ϱ�\n");
    printf("6. ����\n");
    printf("�޴��� �����ϼ���: ");
}

// ������ ���� �Է� �Լ�
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

// ������ ���� ��� �Լ�
void printConcepts(struct Subject* subject) {
    printf("%s ������ ������ ����:\n", subject->name);
    for (int i = 0; i < MAX_CONCEPTS; ++i) {
        if (subject->concepts[i][0] == 'q') {
            break;
        }
        printf("%s - %s\n", subject->concepts[i], subject->definitions[i]);
    }
}

// �޸� ���� �Լ�
void freeMemory(struct Subject* subjects, int subjectCount) {
    for (int i = 0; i < subjectCount; ++i) {
        free(subjects[i].concepts);
        free(subjects[i].definitions);
    }
}

// ������ D-day ��ȹ ��� �Լ�
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
            // ���� ���� �Է�
            inputConcepts(subjects, subjectCount);
            break;
        case 3:
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
        case 4:
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
        case 5:
            // ������ D-day ��ȹ Ȯ���ϱ�
            printf("������ D-day�� �Է��ϼ���: ");
            scanf_s("%d", &dDay);
            printDdayPlan(subjects, subjectCount, dDay);
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
