
#define MAX_SUBJECTS 10
#define MAX_DAYS 30
#define MAX_CONCEPTS 10

// 구조체 정의: 과목 정보
struct Subject {
    char name[50];
    char examDate[20];
    char(*concepts)[50];       // 포인터로 동적으로 할당할 배열
    char(*definitions)[100];   // 포인터로 동적으로 할당할 배열
};

// 메뉴 출력 함수
void printMenu();

// 부족한 개념 입력 함수
void inputConcepts(struct Subject* subjects, int subjectCount);

// 부족한 개념 출력 함수
void printConcepts(struct Subject* subject);

// 메모리 해제 함수
void freeMemory(struct Subject* subjects, int subjectCount);

// 오늘의 D-day 계획 출력 함수
void printDdayPlan(struct Subject* subjects, int subjectCount, int dDay);

