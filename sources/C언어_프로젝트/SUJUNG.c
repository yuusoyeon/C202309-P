#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

// ���� ���� �и��ϴ� �Լ�
void getMonthDay(const char* date, int* month, int* day) {
    sscanf_s(date, "%d��%d��", month, day);
}

// �� ��¥ ���� ���̸� ����ϴ� �Լ�
int calcDaysLeft(const char* currentDate, const char* examDate) {
    struct tm currentTime, examTime;
    memset(&currentTime, 0, sizeof(struct tm));
    memset(&examTime, 0, sizeof(struct tm));

    // ���� ��¥ ����
    sscanf_s(currentDate, "%d��%d��", &currentTime.tm_mon, &currentTime.tm_mday);
    currentTime.tm_mon -= 1;  // tm_mon�� 0���� �����ϹǷ� 1�� ���ݴϴ�.
    currentTime.tm_year = 2023 - 1900;  // ���� ���� ���� (2023�� ����)

    // ���� ��¥ ����
    sscanf_s(examDate, "%d��%d��", &examTime.tm_mon, &examTime.tm_mday);
    examTime.tm_mon -= 1;  // tm_mon�� 0���� �����ϹǷ� 1�� ���ݴϴ�.
    examTime.tm_year = 2023 - 1900;  // ���� ���� ���� (2023�� ����)

    time_t currentTimestamp = mktime(&currentTime);
    time_t examTimestamp = mktime(&examTime);

    // �� ��¥ ���� ���� ���
    int daysLeft = (examTimestamp - currentTimestamp) / (60 * 60 * 24);
    return daysLeft;
}

// �޴� ��� �Լ�
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
void printDdayPlan(struct Subject* subjects, int subjectCount, const char* currentDate, const char* examStartDate) {
    int daysElapsed = calcDaysLeft(currentDate, examStartDate);
    
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

    // ������ ���� ���� ��¥ �Է�
    char examStartDate[20];
    printf("���� �Ⱓ�� ���� ��¥�� �Է��ϼ��� (���� ����, ex: 12��11��): ");
    scanf_s("%s", examStartDate, 20);

    // �� ������ �̸��� ���� ��¥ �Է�
    for (int i = 0; i < subjectCount; ++i) {
        printf("���� %d�� �̸��� �Է��ϼ���: ", i + 1);
        scanf_s("%s", subjects[i].name, 50);

        printf("���� %d�� ���� ��¥�� �Է��ϼ��� (���� ����, ex: 12��18��): ", i + 1);
        scanf_s("%s", subjects[i].examDate, 20);

        // �� ���� ���� �������� �迭 �Ҵ�
        subjects[i].concepts = (char(*)[50])malloc(MAX_CONCEPTS * sizeof(char[50]));
        subjects[i].definitions = (char(*)[100])malloc(MAX_CONCEPTS * sizeof(char[100]));
    }

    // �޴� ���� �� ó��
    int menuChoice;
    char currentDate[20];
    do {

        printMenu();
        scanf_s("%d", &menuChoice);

        switch (menuChoice) {
        // 30�Ͽ� ��ȹ �����
        case 1:
            totalDays = MAX_DAYS;
            printf("\n[���͵� ��ȹ]\n");

            // �����̼� ��ȹ �� ������ ���� ���
            for (int day = 1; day <= totalDays; ++day) {
                int subjectIndex = (day - 1) % subjectCount;
                int rotationCount = ((day - 1) / (3 * subjectCount)) + 1;

                printf("Day %d: %s ", day, subjects[subjectIndex].name);

                switch ((day - 1) % 3) {
                case 0:
                    printf("%dȸ��\n", rotationCount);
                    break;
                case 1:
                    printf("%s ����Ǯ��&���� üũ\n", subjects[subjectIndex].name);
                    break;
                case 2:
                    printf("%s ���� �׽�Ʈ\n", subjects[subjectIndex].name);
                    break;
                }

                if (day % 3 == 0) {
                    printf("\n");
                }
            }
            break;


        case 2:
            // ������ D-day ��ȹ Ȯ���ϱ�
            printf("������ ��¥�� �Է��ϼ��� (���� ����, ex: 12��11��): ");
            scanf_s("%s", currentDate, 20);

            int daysElapsed = calcDaysLeft(currentDate, examStartDate);


            for (int i = 0; i < subjectCount; ++i) {
                int daysLeft = calcDaysLeft(examStartDate, subjects[i].examDate);
                printf("%s - %d�� ���ҽ��ϴ�.\n", subjects[i].name, daysElapsed + daysLeft);
            }

            printf("\n[������ ��ȹ]\n");

            int subjectIndex = (daysElapsed - 1) / 3 % subjectCount;

            printf("    %s ", subjects[subjectIndex].name);

            switch ((daysElapsed - 1) % 3) {
            case 0:
                printf("%dȸ��\n", ((daysElapsed - 1) / 3) + 1);
                break;
            case 1:
                printf("����Ǯ��&���� üũ\n");
                break;
            case 2:
                printf("���� �׽�Ʈ\n");
                break;
            }

            printf("\n");

            break;
                
        case 3:
            // ���� ���� �Է�
            inputConcepts(subjects, subjectCount);
            break;
        case 4:
            // ������ ���� Ȯ���ϱ�
            printf("������ �����ϼ��� (1���� %d����): ", subjectCount);
            int selectedSubjectIndex;
            scanf_s("%d", &selectedSubjectIndex);
            if (selectedSubjectIndex >= 1 && selectedSubjectIndex <= subjectCount) {
                printConcepts(&subjects[selectedSubjectIndex - 1]);
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
