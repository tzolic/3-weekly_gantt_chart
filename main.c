/*
=========================================================================================================================================
Name        : Weekly Gantt Chart
Author      : tzolic
Description : A gantt chart generator that helps you visualize and manage the schedule and dependencies of tasks within a weekly project.
=========================================================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gantt.h"

int main(void)
{
	struct task example_find_job[] =
		{
				{"Define event objectives",1,1,0,{}},
				{"Create a budget plan",1,2,1,{1}},
				{"Research venues & availability",2,3,1,{2}},
				{"Select & book venue",3,4,1,{3}},
				{"Draft guest list",3,3,0,{}},
				{"Send invitations",4,4,2,{4,5}},
				{"Arrange catering options",4,5,1,{5}},
				{"Book entertainment",5,6,1,{5}},
				{"Confirm all bookings",6,6,2,{7,8}},
				{"Finalize event details",7,7,1,{9}}
		};

	struct task null_input[10];

	char* choice = inputHandler("1-Use our gantt test example\n2-Create your own gantt from scratch\n3-Exit\nEnter your choice:\n", "Input error! Enter a valid choice (1-3):\n", menuCondition);
	
	if(strcmp("1", choice) == 0){
		drawGantt(example_find_job, 10);
		editGantt(example_find_job, 10);
		}
	else if(strcmp("2", choice) == 0){
		inputGantt(null_input);
	}
	else{
		printf("\033[1;32m");
    printf("Thanks for using our weekly gantt chart!");
		printf("\033[0m");
	}
	
	return 0;
}