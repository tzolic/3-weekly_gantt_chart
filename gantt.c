#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gantt.h"

void drawGantt(struct task tasks[], int nb_tasks){
	char weekdays[7][10] = {"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};

	//add +1 for each width size because of the '|' column separator each time
	int total_width = (LEFT_COL_WIDTH + 1) + ((NB_COL + 1) * (CENTRAL_COL_WIDTH + 1)) + RIGHT_COL_WIDTH;

	/*----------column header (6 parts)----------*/
	//1-print first big line
	for(int i = 0; i < total_width; i++){
		printf("_");
	}
	puts("");

	//2-empty space at the intersection between row and column headers
	for(int i = 0; i < LEFT_COL_WIDTH; i++){
		printf(" ");
	}
	printf("|");

	//3-weekdays header
	for(int i = 0; i < NB_COL; i++){
		int total_padding = (CENTRAL_COL_WIDTH - strlen(weekdays[i]));
		int l_padding, r_padding;

		if(total_padding % 2 == 1){
			l_padding = total_padding / 2 + 1;
			r_padding = total_padding / 2;
		}
		else{
			l_padding = total_padding / 2;
			r_padding = total_padding / 2;
		}

		printf("%*s%s%*s|", l_padding, "", weekdays[i], r_padding, "");
	}

	//4-task id header
	char task_id[13] = "Task id";
	int total_padding = (CENTRAL_COL_WIDTH - strlen(task_id));
	int l_padding, r_padding;

	if(total_padding % 2 == 1){
		l_padding = total_padding / 2 + 1;
		r_padding = total_padding / 2;
	}
	else{
		l_padding = total_padding / 2;
		r_padding = total_padding / 2;
	}

	printf("%*s%s%*s|",l_padding,"",task_id,r_padding,"");

	//5-dependencies header
	char dependencies[13] = "Dependencies";
	total_padding = (RIGHT_COL_WIDTH - strlen(dependencies));

	if(total_padding % 2 == 1){
		l_padding = total_padding / 2 + 1;
		r_padding = total_padding / 2;
	}
	else{
		l_padding = total_padding / 2;
		r_padding = total_padding / 2;
	}

	printf("%*s%s%*s\n", l_padding, "", dependencies, r_padding,"");

	//6-separator between header and content
	for(int j = 0; j < total_width; j++){
		printf("=");
	}
	puts("");

	/*----------content (4 parts)----------*/
	//1-row header
	for(int i = 0; i < nb_tasks; i++){
		int total_padding = (LEFT_COL_WIDTH - strlen(tasks[i].task));
		int l_padding, r_padding;

		if(total_padding % 2 == 1){
			l_padding = total_padding / 2 + 1;
			r_padding = total_padding / 2;
		}
		else{
			l_padding = total_padding / 2;
			r_padding = total_padding / 2;
		}

		printf("%*s%s%*s|", l_padding, "", tasks[i].task, r_padding, "");

		//2-content
		char content[4];

		for(int k = 0; k < NB_COL; k++){
			//if the day column is between start day and end day
			if(((k + 1) >= tasks[i].start_day) && ((k + 1) <= tasks[i].end_day)){
				strcpy(content, "XXX");
			}
			else{
				strcpy(content, "");
			}

			int total_padding = (CENTRAL_COL_WIDTH - strlen(content));
			int l_padding, r_padding;

			if(total_padding % 2 == 1){
				l_padding = total_padding / 2 + 1;
				r_padding = total_padding / 2;
			}
			else{
				l_padding = total_padding / 2;
				r_padding = total_padding / 2;
			}

			printf("%*s%s%*s|", l_padding, "", content, r_padding, "");
		}

		//3-task id
		total_padding = (CENTRAL_COL_WIDTH - countDigits(i + 1));
		if(total_padding % 2 == 1){
				l_padding = total_padding / 2 + 1;
				r_padding = total_padding / 2;
			}
			else{
				l_padding = total_padding / 2;
				r_padding = total_padding / 2;
			}

		printf("%*s%d%*s|", l_padding, "", i + 1, r_padding, "");

		//4-dependencies
		if(tasks[i].nb_dependencies >= 1){
			total_padding = (RIGHT_COL_WIDTH - (tasks[i].nb_dependencies + tasks[i].nb_dependencies - 1));
		}
		else{
			total_padding = (RIGHT_COL_WIDTH);
		}

		if(total_padding % 2 == 1){
			l_padding = total_padding / 2 + 1;
			r_padding = total_padding / 2;
		}
		else{
			l_padding = total_padding / 2;
			r_padding = total_padding / 2;
		}

		char result[20] = "";
		char temp[20];

		sprintf(temp, "%d", tasks[i].dependencies[0]);
		strcat(result, temp);

		for(int j = 1; j < tasks[i].nb_dependencies; j++){
			sprintf(temp," %d",tasks[i].dependencies[j]);
			strcat(result, temp);
		}

		if(tasks[i].nb_dependencies >= 1){
			printf("%*s%s%*s\n", l_padding, "", result, r_padding, "");
		}
		else{
			printf("%*s%s%*s\n", l_padding, "", "", r_padding, "");
		}

		//4-separator
		for(int j = 0; j < total_width; j++){
			printf("-");
		}
		puts("");
	}
}




/*----------edit gantt chart (3 parts)----------*/
void editGantt(struct task tasks[], int nb_tasks){
	char* buffer;
	int found_index;

	char* choice = inputHandler("1-Edit the gantt chart\n2-Run a test\n3-Main Menu\nEnter your choice:\n", "Input error! Enter a valid choice (1-3):\n", menuCondition);

	//1-edit a task
	if(strcmp("1", choice) == 0){

		//ask to enter the current task name
		int found_task = 0;

		char* current_task = inputHandler("Enter current task name you wish to change:\n", "", noCondition);

		for(int i = 0; i < nb_tasks; i++){
			if(strcmp(current_task, tasks[i].task) == 0){
				found_task = 1;
				found_index = i;
				break;
			}
		}

		while(found_task == 0){
			char* current_task = inputHandler("\033[1;31mAvailability Error! Enter an available task name:\n\033[0m", "", noCondition);

			for(int i = 0; i < nb_tasks; i++)
			{
				if(strcmp(current_task, tasks[i].task) == 0){
					found_task = 1;
					found_index = i;
					break;
				}
			}
		}

		//enter new task name
		char* new_task = inputHandler("Enter new task name:\n", "", noCondition);
		strcpy(tasks[found_index].task, new_task);

		//enter start date
		char* start_day_string = inputHandler("Start day (1-7):\n", "Input Error! Enter a start day (1-7):\n", dayCondition);
		//enter end date
		char* end_day_string = inputHandler("End day (1-7):\n", "Input Error! Enter an end day (1-7):\n", dayCondition);
		int start_day = atoi(start_day_string);
		int end_day = atoi(end_day_string);

		while(!(start_day <= end_day)){
			printf("\033[1;31m");
			printf("Logic Error! Enter an end day that satisfies start day <= end day:\n");
			printf("\033[0m");

			//enter start date
			char* start_day_string = inputHandler("Start day (1-7):\n", "Input Error! Enter a start day (1-7):\n", dayCondition);
			//enter end date
			char* end_day_string = inputHandler("End day (1-7):\n", "Input Error! Enter an end day (1-7):\n", dayCondition);
			start_day = atoi(start_day_string);
			end_day = atoi(end_day_string);
		}

		tasks[found_index].start_day = start_day;
		tasks[found_index].end_day = end_day;

		//enter dependencies
		char* nb_dependencies_string = inputHandler("Enter number of dependencies for this task (0-9):\n", "Input error! Enter number of dependencies for this task (0-9):\n", nbDependenciesCondition);
		int nb_dependencies = atoi(nb_dependencies_string);

		tasks[found_index].nb_dependencies = nb_dependencies;

		int dependencies[10];

		for(int i = 0; i < nb_dependencies; i++){

			char prompt[300];
			char error_prompt[300];
			sprintf(prompt, "%s %d %s", "Enter dependency number", i + 1, "(1-10):\n");
			sprintf(error_prompt, "%s %d %s", "Input error! Enter dependency number", i + 1, "(1-10):\n");
			char* dependency = inputHandler(prompt, error_prompt, oneToTenCondition);
			dependencies[i] = atoi(dependency);

			tasks[found_index].dependencies[i] = dependencies[i];
		}

		//draw updated gantt chart
		drawGantt(tasks, nb_tasks);
		editGantt(tasks, nb_tasks);
	}

	//2-run a test
	else if(strcmp("2", choice) == 0){
		//ask for which dependency to check
		char* task_id_string = inputHandler("Enter the task id to check its dependencies (1-10):\n", "Input error! Enter the task id to check its dependencies (1-10):\n", oneToTenCondition);
		
		int task_id = atoi(task_id_string);

		int visited_tasks[nb_tasks + 1]; //adjust index
		for (int i = 0; i <= nb_tasks; i++){
			visited_tasks[i] = 0;
		}
		//print dependencies and check for circular dependencies
		printf("Dependencies for task %d:\n", task_id);
		printDependentTasks(tasks, task_id , visited_tasks);
		printf("\n");

		editGantt(tasks, nb_tasks);
	}

	//3-return to main menu
	else if(strcmp("3", choice) == 0){
		main();
	}
}




void printDependentTasks(struct task task_list[], int task_id, int visited_tasks[]){
	printf("%d -> ", task_id);
	visited_tasks[task_id] = 1;

	for (int i = 0; i < task_list[task_id - 1].nb_dependencies; i++){
		int dependent_task_id = task_list[task_id - 1].dependencies[i];

		if (visited_tasks[dependent_task_id] == 0){
			printDependentTasks(task_list, dependent_task_id, visited_tasks);
		}
		else{
			int circular = checkIfCircular(task_list, dependent_task_id, visited_tasks);
			if (circular != 0){
				printf("\033[1;31m");
				printf("!!!Circular Dependency Found!!!\n");
				printf("\033[0m");
			}
		}
	}
}





int checkIfCircular(struct task task_list[], int task_id, int visited_tasks[]){
	//mark current task as visited
	visited_tasks[task_id] = 1;

	//go through dependencies of the current task
	for (int i = 0; i < task_list[task_id - 1].nb_dependencies; i++){
			int dependent_task_id = task_list[task_id - 1].dependencies[i];

			//if dependent task is already visited, it's a circular dependency
			if (visited_tasks[dependent_task_id] == 1){
					return 1; // Return 1 since circular dependency has been found
			}
			//if dependent task is not visited, recursively check for circular dependencies
			if (checkIfCircular(task_list, dependent_task_id, visited_tasks)){
					return 1;
			}
	}
	
	visited_tasks[task_id] = 0; // Reset
	return 0; // no circular dependency found
}




struct task inputTasks[] = {};

void inputGantt(struct task input_tasks[]){
	//ask how many tasks does the user want
	char* nb_tasks_string = inputHandler("How many tasks would you like to add? (1-10):\n", "Input error! How many tasks would you like to add? (1-10):\n", oneToTenCondition);
	int nb_tasks = atoi(nb_tasks_string);

	for(int i = 0; i < nb_tasks; i++){
		//enter new task name
		char temp[300];
		sprintf(temp, "Enter new task name %d:\n", (i + 1));
		char* input_task = inputHandler(temp, "", noCondition);

		strcpy(input_tasks[i].task, input_task);

		//enter start date
		char* start_day_string = inputHandler("Start day (1-7):\n", "Input Error! Enter a start day (1-7):\n", dayCondition);

		//enter end date
		char* end_day_string = inputHandler("End day (1-7):\n", "Input Error! Enter an end day (1-7):\n", dayCondition);

		int start_day = atoi(start_day_string);
		int end_day = atoi(end_day_string);

		while(!(start_day <= end_day)){
			printf("\033[1;31m");
			printf("Logic Error! Enter an end day that satisfies start day <= end day:\n");
			printf("\033[0m");

			//enter start date
			char* start_day_string = inputHandler("Start day (1-7):\n", "Input Error! Enter a start day (1-7):\n", dayCondition);

			//enter end date
			char* end_day_string = inputHandler("End day (1-7):\n", "Input Error! Enter an end day (1-7):\n", dayCondition);

			start_day = atoi(start_day_string);
			end_day = atoi(end_day_string);
		}

		input_tasks[i].start_day = start_day;
		input_tasks[i].end_day = end_day;
		
		//enter dependencies
		char* nb_dependencies_string = inputHandler("Enter number of dependencies for this task (0-9):\n", "Input error! Enter number of dependencies for this task (0-9):\n", nbDependenciesCondition);
		int nb_dependencies = atoi(nb_dependencies_string);

		input_tasks[i].nb_dependencies = nb_dependencies;

		int dependencies[10];

		for(int j = 0; j < nb_dependencies; j++){

			char prompt[300];
			char error_prompt[300];
			sprintf(prompt, "%s %d %s", "Enter dependency number", j + 1, "(1-10):\n");
			sprintf(error_prompt, "%s %d %s", "Input error! Enter dependency number", j + 1, "(1-10):\n");
			char* dependency = inputHandler(prompt, error_prompt, oneToTenCondition);
			dependencies[j] = atoi(dependency);

			input_tasks[i].dependencies[j] = dependencies[j];
		}
	}

	//draw updated gantt chart
	drawGantt(input_tasks, nb_tasks);
	editGantt(input_tasks, nb_tasks);
}




char* inputHandler(char* prompt, char* error_prompt, int (*condition)(char* input)){
  //choose initial buffer size
  size_t buffer_size = 300;

  //allocate dynamically memory input buffer
  char* input = (char*)malloc(buffer_size * sizeof(char));
  if (input == NULL){
      fprintf(stderr, "Memory allocation failed!");
      exit(1);
  }

  //display prompt
  printf("%s", prompt);
  fflush(stdout);

  //read input in stdin
  fgets(input, buffer_size, stdin);
  input[strlen(input) - 1] = '\0';

  //handle length error
  while((strlen(input) + 2) >= buffer_size){
    //clear buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("\033[1;31m");
    //length error prompt
    printf("Length error! Input exceeds maximum input limit. Please enter a shorter input:\n");
    fflush(stdout);
    printf("\033[0m");

    fgets(input, buffer_size, stdin);
    input[strlen(input) - 1] = '\0';
  }

  //handle condition error
  while(condition(input) == 0){
    printf("\033[1;31m");
    //error prompt
    printf("%s", error_prompt);
    fflush(stdout);
    printf("\033[0m");
    
    fgets(input, buffer_size, stdin);
    input[strlen(input) - 1] = '\0';

    //handle length error again inside condition error
    while((strlen(input) + 2) >= buffer_size){
      int c;
      while ((c = getchar()) != '\n' && c != EOF);

      printf("\033[1;31m");
      printf("Length error! Input exceeds maximum input limit. Please enter a shorter input:\n");
      fflush(stdout);
      printf("\033[0m");

      fgets(input, buffer_size, stdin);
      input[strlen(input) - 1] = '\0';
    }
  }
  return input;
}




/*----------condition functions----------*/
int menuCondition(char* input){
  int num = atoi(input);
  if((num >= 1) && (num <= 3)){
    return 1;
  }
  return 0;
}

int noCondition(char* input){
	return 1;
}

int dayCondition(char* input){
	int num = atoi(input);
  if((num >= 1) && (num <= 7)){
    return 1;
  }
  return 0;
}

int nbDependenciesCondition(char* input){
	int num = atoi(input);
  if(((num >= 1) && (num <= 9) && num != 0) || (num == 0 && strcmp("0",input) == 0)){
    return 1;
  }
  return 0;
}

int oneToTenCondition(char* input){
	int num = atoi(input);
  if((num >= 1) && (num <= 10)){
    return 1;
  }
  return 0;
}





int countDigits(int n){
	if(n < 0){
		return -n;
	}
	else if(n < 10){
		return 1;
	}
	return 1 + countDigits(n / 10);
}