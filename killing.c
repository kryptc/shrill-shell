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
	if (atoi(str[1]) > proc_count)
	{
		printf("Not a valid job id\n");
		return;
	}
	int job_id = atoi(str[1]);
	int kill_id = atoi(str[2]);
	// if (job_id <= *proc_count)
	// {
		// kill(proc_list[job_id], kill_id);
	if (kill_id == 9)
		proc_arr[job_id].status = 0;
	else if (kill_id == 17 || kill_id == 20 ||kill_id == 23 ||kill_id == 24)
		proc_arr[job_id].status = 2;
	else if (kill_id == 25)
		proc_arr[job_id].status = 1;



	// }
	kill(proc_arr[job_id].id, kill_id);

	return;
}

void overkill()
{
	while (proc_arr[proc_count].id != root_pid && proc_count != 0)
	{
		if (proc_arr[proc_count].status != 0)
		{
			printf("Process %d killed\n", proc_arr[proc_count].id);
			kill(proc_arr[proc_count].id, 9);
			proc_arr[proc_count].status = 0;
		}
		proc_count--;
		
	}
	return;
}