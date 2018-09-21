#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

typedef struct 
{
  int id;
  char name[100];
  int status;

} Proc;

extern int proc_count;

extern Proc proc_arr[100];

extern int root_pid;


void kjob(char ** str)
{
	if (str[1] == NULL || str[2] == NULL)
	{
		perror("Too few arguments\n");
		return;
	}
	int job_id = atoi(str[1]);
	int kill_id = atoi(str[2]);
	// if (job_id <= *proc_count)
	// {
		// kill(proc_list[job_id], kill_id);
	proc_arr[job_id].status = 0;
	// }
	kill(proc_arr[job_id].id, kill_id);

	return;
}

void overkill()
{
	while (proc_count-- && proc_arr[proc_count].id != root_pid)
	{
		kill(proc_arr[proc_count].id, 9);
		proc_arr[proc_count].status = 0;
	}
	return;
}