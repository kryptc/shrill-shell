#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


void jobs (char ** str)
{
	char statusv[20];
	for (int i = 1; i <= proc_count; i++)
	{
			if (proc_arr[i].status == 1)
				strcpy(statusv, "Running");
			else if (proc_arr[i].status == 2)
				strcpy(statusv, "Stopped");
			else if (proc_arr[i].status == 0)
				return;
			//reads formatted inout from string line_buffer
			printf("[%d] %s %s [%d]\n", i, statusv, proc_arr[i].name, proc_arr[i].id);
			// printf("%s\n",statusarr[i] );
	}

}