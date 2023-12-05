
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
void printMenu();

// ������ ���� �Է� �Լ�
void inputConcepts(struct Subject* subjects, int subjectCount);

// ������ ���� ��� �Լ�
void printConcepts(struct Subject* subject);

// �޸� ���� �Լ�
void freeMemory(struct Subject* subjects, int subjectCount);

// ������ D-day ��ȹ ��� �Լ�
void printDdayPlan(struct Subject* subjects, int subjectCount, int dDay);

