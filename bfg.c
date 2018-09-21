#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

extern int root_pid;
extern int curr_pid;

typedef struct 
{
  int id;
  char name[100];
  int status;
} Proc;

int proc_count;

Proc proc_arr[100];

void fg (char ** str)
{
	if (str[1] == NULL)
	{
		printf("Too few arguments\n");
		return;
	}
	else if (str[2] != NULL)
	{
		printf("Too many arguments\n");
		return;
	}
}

void bg (char ** str)
{
	if (str[1] == NULL)
	{
		printf("Too few arguments\n");
		return;
	}
	else if (str[2] != NULL)
	{
		printf("Too many arguments\n");
		return;
	}
	kill(atoi(str[1]), SIGCONT);
	proc_arr[ atoi( str[1] ) ].status = 1;
	return;
}