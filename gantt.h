#ifndef GANTT_H
#define GANTT_H

#define BUFFER_SIZE 300
#define NB_COL 7
#define LEFT_COL_WIDTH 40
#define CENTRAL_COL_WIDTH 12
#define RIGHT_COL_WIDTH 16

struct task{
	char task[300];
	int start_day;
	int end_day;
	int nb_dependencies;
	int dependencies[10];
};

int main(void);

char* inputHandler(char* prompt, char* error_prompt, int (*condition)(char* input));
int menuCondition(char* input);
int noCondition(char* input);
int dayCondition(char* input);
int nbDependenciesCondition(char* input);
int oneToTenCondition(char* input);

int countDigits(int n);

void drawGantt(struct task tasks[], int nb_tasks);
void editGantt(struct task tasks[], int nb_tasks);

void printDependentTasks(struct task taskList[], int taskId, int visitedTasks[]);
int checkIfCircular(struct task taskList[], int taskId, int visitedTasks[]);
void inputGantt(struct task inputTasks[]);

#endif /* GANTT_H */