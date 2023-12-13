#define STUDYPLAN_30_H

struct Subject {
    char name[50];
    char examDate[20];
    char(*concepts)[50];
    char(*definitions)[100];
};

void getMonthDay(const char* date, int* month, int* day);

int calcDaysLeft(const char* currentDate, const char* examDate);

void printMenu();

void inputConcepts(struct Subject* subjects, int subjectCount);

void printConcepts(struct Subject* subject);

void freeMemory(struct Subject* subjects, int subjectCount);

void printDdayPlan(struct Subject* subjects, int subjectCount, const char* currentDate, const char* examStartDate);
