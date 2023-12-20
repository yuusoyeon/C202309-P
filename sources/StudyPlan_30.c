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
        // 스택이 가득 찼을 때의 처리
        printf("Subject stack is full.\n");
        return;
    }
    s->stk[s->ptr++] = x;
}

int Pop(SubjectStack* s, int* x) {
    if (s->ptr <= 0) {
        // 스택이 비었을 때의 처리
        printf("Subject stack is empty.\n");
        return -1;
    }
    *x = s->stk[--s->ptr];
    return 0;
}

int Top(const SubjectStack* s, int* x) {
    if (s->ptr <= 0) {
        // 스택이 비었을 때의 처리
        printf("Subject stack is empty.\n");
        return -1;
    }
    *x = s->stk[s->ptr - 1];
    return 0;
}



int calcDaysLeft(const char* currentDate, const char* examDate) {
    struct tm currentTime, examTime;
    memset(&currentTime, 0, sizeof(struct tm));
    memset(&examTime, 0, sizeof(struct tm));

    // 현재 날짜 설정
    sscanf_s(currentDate, "%d월%d일", &currentTime.tm_mon, &currentTime.tm_mday);
    currentTime.tm_mon -= 1;  // tm_mon은 0부터 시작하므로 1을 빼줍니다.
    currentTime.tm_year = 2023 - 1900;  // 현재 연도 설정 (2023년 기준)

    // 시험 날짜 설정
    sscanf_s(examDate, "%d월%d일", &examTime.tm_mon, &examTime.tm_mday);
    examTime.tm_mon -= 1;  // tm_mon은 0부터 시작하므로 1을 빼줍니다.
    examTime.tm_year = 2023 - 1900;  // 현재 연도 설정 (2023년 기준)

    time_t currentTimestamp = mktime(&currentTime);
    time_t examTimestamp = mktime(&examTime);

    // 두 날짜 간의 차이 계산
    int daysLeft = (examTimestamp - currentTimestamp) / (60 * 60 * 24);
    return daysLeft;
}

void printMenu() {
    printf("\n[메뉴]\n");
    printf("1. 30일용 계획 세우기\n");
    printf("2. 오늘의 D-day 계획 확인하기\n");
    printf("3. 부족 개념 입력\n");
    printf("4. 퀴즈 풀고 일기 쓰기\n");
    printf("5. 오늘 일정을 미루시겠습니까? (Y/N)\n");
    printf("6. 종료\n");
    printf("메뉴를 선택하세요: ");
}

void inputConcepts(struct Subject* subjects, int subjectCount) {
    for (int i = 0; i < subjectCount; ++i) {
        printf("%s 과목의 부족했던 개념을 입력해주세요 (입력을 마치려면 q를 입력하세요):\n", subjects[i].name);

        for (int j = 0; j < MAX_CONCEPTS; ++j) {
            printf("단어: ");
            if (scanf_s("%s", subjects[i].concepts[j], 50) != 1 || subjects[i].concepts[j][0] == 'q') {
                break;
            }

            printf("정의: ");
            scanf_s("%s", subjects[i].definitions[j], 100);
        }
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
        printf("%s 과목의 부족했던 개념을 퀴즈로 확인합니다:\n", subjects[subjectIndex].name);

        for (int i = 0; i < MAX_CONCEPTS; ++i) {
            if (subjects[subjectIndex].concepts[i][0] == 'q') {
                break;
            }

            // 사용자에게 단어를 물어보고 정답 체크
            printf("단어: %s\n", subjects[subjectIndex].concepts[i]);
            printf("정의: ");
            char userDefinition[100];
            scanf_s("%s", userDefinition, sizeof(userDefinition));

            if (strcmp(userDefinition, subjects[subjectIndex].definitions[i]) == 0) {
                printf("정답입니다!\n");
            }
            else {
                printf("틀렸습니다. 정답은: %s\n", subjects[subjectIndex].definitions[i]);
                allCorrect = 0;
            }
        }

        // 추가 퀴즈 여부 물어보기
        printf("동일한 문제를 다시 풀어보시겠습니까? (1: 예, 0: 아니오): ");
        scanf_s("%d", &additionalQuizzes);

    } while (additionalQuizzes == 1);

    return allCorrect;
}

// 비밀 일기장 열기 함수
void openDiary() {
    char password[20];
    char line[MAX];
    char contents[MAX];

    printf("  ~ 일기 쓰기 ~ \n");
    printf("비밀번호를 입력하세요 (최대 20자리): ");
    scanf_s("%s", password, sizeof(password));

    printf("\n\n=== 비밀번호 확인 중===\n\n");

    if (strcmp(password, "project") == 0) {
        printf("=== 비밀번호 확인 완료.===\n\n");

        // 파일 열기
        FILE* file;
        if (fopen_s(&file, "diary.txt", "a+") != 0) {
            printf("파일 열기 실패\n");
            return;
        }

        // 파일 내용 출력
        while (fgets(line, MAX, file) != NULL) {
            printf("%s", line);
        }

        printf("\n\n내용을 계속 작성하세요! 종료하려면 EXIT를 입력하세요.\n\n");

        // 내용 입력 및 파일에 쓰기
        while (1) {
            scanf_s(" %[^\n]", contents, sizeof(contents));
            getchar();

            if (strcmp(contents, "EXIT") == 0) {
                printf("비밀일기 입력을 종료합니다.\n\n");
                break;
            }

            fputs(contents, file);
            fputs("\n", file);
        }

        // 파일 닫기
        fclose(file);
    }
    else {
        printf("=== 비밀번호가 틀렸어요. ===\n\n");
        return;
    }
}



void printDdayPlan(struct Subject* subjects, int subjectCount, const char* currentDate, const char* examStartDate) {
    int daysElapsed = calcDaysLeft(currentDate, examStartDate);
}

void handleTodayTask(SubjectStack* stack, int* subjectIndex, const struct Subject* subjects, int subjectCount) {
    // 오늘의 할 일 수행 여부 입력 받기
    printf("오늘 할 일을 수행하셨나요? (1: 예, 0: 아니오): ");
    int todayTaskCompleted;
    scanf_s("%d", &todayTaskCompleted);

    if (todayTaskCompleted) {
        // 오늘의 할 일 수행 완료 시 스택에서 맨 위 숫자(pop)를 가져와 출력
        int poppedValue;

        if (Pop(stack, &poppedValue) == 0) {
            printf("오늘 할 일을 수행하셨습니다. 오늘차 계획을 삭제합니다. (내일 해야할 일 : %d일차 계획)\n", poppedValue + 1, poppedValue + 1);
        }
        else {
            printf("남은 할 일이 없습니다.\n");
        }
    }

    else {
        // 오늘의 할 일 수행하지 않았을 때 스택은 건드리지 않고 현재 맨 위 숫자(top)만 출력
        int topValue;
        if (Top(stack, &topValue) == 0) {
            printf("오늘 할 일을 수행하지 않으셨습니다. 내일로 미뤄집니다. (내일 해야 할 일 : %d일차 계획)\n", topValue, topValue);
        }
        else {
            printf("남은 할 일이 없습니다.\n");
        }
    }

}