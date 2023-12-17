#include "Studyplan_30.h"


int Initialize(SubjectStack* s, int max) {
    s->ptr = 0;
    if ((s->stk = calloc(max, sizeof(int))) == NULL) {
        s->max = 0;
        return -1;
    }
    s->max = max;
    return 0;
}

void Push(SubjectStack* s, int x) {
    if (s->ptr >= s->max) {
        // ������ ���� á�� ���� ó��
        printf("Subject stack is full.\n");
        return;
    }
    s->stk[s->ptr++] = x;
}

int Pop(SubjectStack* s, int* x) {
    if (s->ptr <= 0) {
        // ������ ����� ���� ó��
        printf("Subject stack is empty.\n");
        return -1;
    }
    *x = s->stk[--s->ptr];
    return 0;
}

int Top(const SubjectStack* s, int* x) {
    if (s->ptr <= 0) {
        // ������ ����� ���� ó��
        printf("Subject stack is empty.\n");
        return -1;
    }
    *x = s->stk[s->ptr - 1];
    return 0;
}

void Terminate(SubjectStack* s) {
    free(s->stk);
    s->max = s->ptr = 0;
}

void getMonthDay(const char* date, int* month, int* day) {
    sscanf_s(date, "%d��%d��", month, day);
}

int calcDaysLeft(const char* currentDate, const char* examDate) {
    struct tm currentTime, examTime;
    memset(&currentTime, 0, sizeof(struct tm));
    memset(&examTime, 0, sizeof(struct tm));

    sscanf_s(currentDate, "%d��%d��", &currentTime.tm_mon, &currentTime.tm_mday);
    currentTime.tm_mon -= 1;
    currentTime.tm_year = 2023 - 1900;

    sscanf_s(examDate, "%d��%d��", &examTime.tm_mon, &examTime.tm_mday);
    examTime.tm_mon -= 1;
    examTime.tm_year = 2023 - 1900;

    time_t currentTimestamp = mktime(&currentTime);
    time_t examTimestamp = mktime(&examTime);

    int daysLeft = (examTimestamp - currentTimestamp) / (60 * 60 * 24);
    return daysLeft;
}

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


int quizConcepts(struct Subject* subjects, int subjectIndex) {
    int allCorrect = 1;
    int additionalQuizzes;

    do {
        printf("%s ������ �����ߴ� ������ ����� Ȯ���մϴ�:\n", subjects[subjectIndex].name);

        for (int i = 0; i < MAX_CONCEPTS; ++i) {
            if (subjects[subjectIndex].concepts[i][0] == 'q') {
                break;
            }

            // ����ڿ��� �ܾ ����� ���� üũ
            printf("�ܾ�: %s\n", subjects[subjectIndex].concepts[i]);
            printf("����: ");
            char userDefinition[100];
            scanf_s("%s", userDefinition, sizeof(userDefinition));

            if (strcmp(userDefinition, subjects[subjectIndex].definitions[i]) == 0) {
                printf("�����Դϴ�!\n");
            }
            else {
                printf("Ʋ�Ƚ��ϴ�. ������: %s\n", subjects[subjectIndex].definitions[i]);
                allCorrect = 0;
            }
        }

        // �߰� ���� ���� �����
        printf("������ ������ �ٽ� Ǯ��ðڽ��ϱ�? (1: ��, 0: �ƴϿ�): ");
        scanf_s("%d", &additionalQuizzes);

    } while (additionalQuizzes == 1);

    return allCorrect;
}


// ��� �ϱ��� ���� �Լ�
void openDiary() {
    char password[20];
    char line[MAX];
    char contents[MAX];

    printf("��� �ϱ⿡ ���� ���� ȯ���մϴ�.\n");
    printf("��й�ȣ�� �Է��ϼ��� (�ִ� 20�ڸ�): ");
    scanf_s("%s", password, sizeof(password));

    printf("\n\n=== ��й�ȣ Ȯ�� ��===\n\n");

    if (strcmp(password, "��������") != 0) {
        printf("=== ��й�ȣ�� Ʋ�Ⱦ��. ===\n\n");
        return;
    }

    printf("=== ��й�ȣ Ȯ�� �Ϸ�.===\n\n");
    char* fileName = "./diary.txt";
    FILE* file;
    fopen_s(&file, fileName, "a+");
    if (file == NULL) {
        printf("���� ���� ����\n");

        return;
    }

    while (fgets(line, MAX, file) != NULL) {
        printf("%s", line);
    }

    printf("\n\n������ ��� �ۼ��ϼ���! �����Ϸ��� EXIT�� �Է��ϼ���.\n\n");

    while (1) {
        scanf_s("%[^\n]", contents, sizeof(contents));
        getchar();

        if (strcmp(contents, "EXIT") == 0) {
            printf("����ϱ� �Է��� �����մϴ�.\n\n");
            break;
        }
        fputs(contents, file);
        fputs("\n", file);
    }
    fclose(file);
}

void printDdayPlan(struct Subject* subjects, int subjectCount, const char* currentDate, const char* examStartDate) {
    int daysElapsed = calcDaysLeft(currentDate, examStartDate);

    printf("\n[D-day ���� �ϼ�]\n");

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
}

void handleTodayTask(SubjectStack* stack, int* subjectIndex, const struct Subject* subjects, int subjectCount) {
    // ������ �� �� ���� ���� �Է� �ޱ�
    printf("���� �� ���� �����ϼ̳���? (1: ��, 0: �ƴϿ�): ");
    int todayTaskCompleted;
    scanf_s("%d", &todayTaskCompleted);

    if (todayTaskCompleted) {
        // ������ �� �� ���� �Ϸ� �� ���ÿ��� �� �� ����(pop)�� ������ ���
        int poppedValue;
        if (Pop(stack, &poppedValue) == 0) {
            poppedValue += 1;
            printf("���� �� ���� �����ϼ̽��ϴ�. ������ ��ȹ�� �����մϴ�. (���� �ؾ��� �� (%d����): %d)\n", poppedValue, poppedValue);
        }
        else {
            printf("���� �� ���� �����ϴ�.\n");
        }
    }
    else {
        // ������ �� �� �������� �ʾ��� �� ������ �ǵ帮�� �ʰ� ���� �� �� ����(top)�� ���
        int topValue;
        if (Top(stack, &topValue) == 0) {
            printf("���� �� ���� �������� �����̽��ϴ�. ���Ϸ� �̷�����ϴ�. (���� �ؾ� �� �� (%d����): %d)\n", topValue, topValue);
        }
        else {
            printf("���� �� ���� �����ϴ�.\n");
        }
    }

}