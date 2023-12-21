#include "Studyplan_30.h"


int main() {
    SubjectStack stack;

    int subjectCount, totalDays;
    int allCorrect;
    int selectedSubjectIndex;
    int totalQuizzes = 0;
    int subjectIndex = 0;

    // ���� �ʱ�ȭ 
    Initialize(&stack, 30);

    // ���ÿ� 30���� 1���� ���ʴ�� �� �ֱ�
    for (int i = 30; i >= 1; --i) {
        Push(&stack, i);
    }

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

            // �����̼� ��ȹ ���
            for (int day = 1; day <= totalDays; ++day) {
                int subjectIndex = (day - 1) / 3 % subjectCount;
                int rotationCount = ((day - 1) / (3 * subjectCount)) + 1;

                printf("%d ���� ��ȹ : %s ", day, subjects[subjectIndex].name);

                switch ((day - 1) % 3) {
                case 0:
                    printf("%dȸ��\n", rotationCount);
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
            // ���� D-day Ȯ���ϱ�
            printf("������ ��¥�� �Է��ϼ��� (���� ����, ex: 12��11��): ");
            printf("\n");
            scanf_s("%s", currentDate, 20);

            int daysElapsed = calcDaysLeft(currentDate, examStartDate);

            for (int i = 0; i < subjectCount; ++i) {
                int daysLeft = calcDaysLeft(examStartDate, subjects[i].examDate);

                printf("%s - %d�� ���ҽ��ϴ�.\n", subjects[i].name, daysElapsed + daysLeft);
            }
            printf("\n");
            break;

        case 3:
            // ���� ���� �Է�
            inputConcepts(subjects, subjectCount);
            break;
        case 4:
            // ������ ���� Ȯ���ϰ� �ϱ� ����
            do {
                // ����ڿ��� ������ �����ϵ��� ���
                printf("������ �����ϼ��� (1���� %d����, 0: ����): ", subjectCount);
                int selectedSubjectIndex;
                scanf_s("%d", &selectedSubjectIndex);

                if (selectedSubjectIndex == 0) {
                    break;
                }
                if (selectedSubjectIndex >= 1 && selectedSubjectIndex <= subjectCount) {
                    allCorrect = quizConcepts(subjects, selectedSubjectIndex - 1);
                }
                else {
                    printf("�߸��� �����Դϴ�.\n");
                }

            } while (1);

            //openDiary �Լ� ȣ��
            printf("�ϱ����� ���ðڽ��ϱ�? (1: ��, 0: �ƴϿ�): ");
            int openDiaryChoice;
            scanf_s("%d", &openDiaryChoice);

            if (openDiaryChoice == 1) {
                openDiary();
            }

            break;

        case 5:
            // ���� �̷��
            handleTodayTask(&stack, &subjectIndex, subjects, subjectCount);
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