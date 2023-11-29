#include <stdio.h>

#define MAX_SUBJECTS 10
#define MAX_DAYS 30
#define MAX_CONCEPTS 10

// ���� ����ü ����
typedef struct {
    char word[50];
    char definition[100];
} Concept;

// �޴� ��� �Լ�
void printMenu() {
    printf("\n[�޴�]\n");
    printf("1. 30�Ͽ� ��ȹ �����\n");
    printf("2. ���� ���� �Է�\n");
    printf("3. ���� ���� �Է��ϱ�\n");
    printf("4. ����\n");
    printf("�޴��� �����ϼ���: ");
}

// ������ ���� �Է� �Լ�
void enterConcepts(Concept concepts[MAX_SUBJECTS][MAX_CONCEPTS], int subjectIndex) {
    printf("%s ������ �����ߴ� ������ �Է����ּ��� (�Է��� ��ġ���� q�� �Է��ϼ���):\n", concepts[subjectIndex][0].word);

    for (int j = 0; j < MAX_CONCEPTS; ++j) {
        printf("�ܾ�: ");
        if (scanf_s("%s", concepts[subjectIndex][j].word, sizeof(concepts[subjectIndex][j].word)) != 1 || concepts[subjectIndex][j].word[0] == 'q') {
            // 'q'�� �Է��ϸ� �Է� ����
            break;
        }

        printf("����: ");
        scanf_s("%s", concepts[subjectIndex][j].definition, sizeof(concepts[subjectIndex][j].definition));
    }
}

int main() {
    int subjectCount, totalDays;

    // ������ ���� ��¥�� �����ϴ� �迭
    char subjects[MAX_SUBJECTS][50];
    char examDates[MAX_SUBJECTS][20];

    // ���� �� �Է�
    printf("������ ���� ������ ������ �Է��ϼ���: ");
    scanf_s("%d", &subjectCount);

    // �� ������ �̸��� ���� ��¥ �Է�
    for (int i = 0; i < subjectCount; ++i) {
        printf("���� %d�� �̸��� �Է��ϼ���: ", i + 1);
        scanf_s("%s", subjects[i], sizeof(subjects[i]));

        printf("���� %d�� ���� ��¥�� �Է��ϼ���: ", i + 1);
        scanf_s("%s", examDates[i], sizeof(examDates[i]));
    }

    // ������ ������ �����ϴ� �迭
    Concept concepts[MAX_SUBJECTS][MAX_CONCEPTS];

    // �޴� ���� �� ó��
    int menuChoice;
    do {
        printMenu();
        scanf_s("%d", &menuChoice);

        switch (menuChoice) {
        case 1:
            // 30�Ͽ� ��ȹ �����
            totalDays = subjectCount * 3 * subjectCount;
            printf("\n[���͵� ��ȹ]\n");

            // �����̼� ��ȹ �� ������ ���� ���
            for (int day = 1; day <= MAX_DAYS && day <= totalDays; ++day) {
                int subjectIndex = ((day - 1) / 3) % subjectCount;

                printf("Day %d: %s (���� ��¥: %s) ", day, subjects[subjectIndex], examDates[subjectIndex]);

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
                    if (concepts[subjectIndex][i].word[0] == 'q') {
                        break;
                    }
                    printf("%s - %s ", concepts[subjectIndex][i].word, concepts[subjectIndex][i].definition);
                }

                if ((day % (3 * subjectCount)) == 0 && day != totalDays) {
                    printf("\n");
                }
            }
            break;
        case 2:
            // ���� ���� �Է�
            // ����ڰ� � ���� ���� ������ ������ �Է��� �� ����
            printf("� ���� ���� ������ ������ �Է��Ͻðڽ��ϱ�? (���� ��ȣ �Է�): ");
            int selectedSubject;
            scanf_s("%d", &selectedSubject);

            if (selectedSubject >= 1 && selectedSubject <= subjectCount) {
                enterConcepts(concepts, selectedSubject - 1);
            }
            else {
                printf("�ùٸ� ���� ��ȣ�� �Է��ϼ���.\n");
            }
            break;
        case 3:
            // ���� ���� �Է��ϱ�
            // TODO: ���� �ʿ�
            break;
        case 4:
            // ����
            printf("���α׷��� �����մϴ�.\n");
            break;
        default:
            printf("�߸��� �޴� �����Դϴ�. �ٽ� �����ϼ���.\n");
        }

    } while (menuChoice != 4);

    return 0;
}
