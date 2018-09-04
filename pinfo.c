#include<sys/stat.h>
#include<sys/types.h>
#include <grp.h>
#include <time.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

void pinfo(int proc_id)
{
	char * proc_path = malloc(1002 * sizeof(char)); // for generating path of proc/pid file
	char * line_buffer = malloc(1002 * sizeof(char)); // for reading file line by line
	char * proc_exec = malloc(1002 * sizeof(char)); // for generating executable of proc/pid file

    //prints formatted string onto proc_path
    sprintf(proc_path, "/proc/%d/stat", proc_id);
    FILE* file = fopen(proc_path, "r");
    if(!file) 
        perror("Error: Process doesn't exist\n"); 
    else
    {
		printf("PID -- %d\n",proc_id);

		long unsigned int vmem = 0;
		char ch;
		int pid;
		char str[30];

		fscanf(file, "%d", &pid);
		fscanf(file, "%s", str);
		fscanf(file," %c", &ch);
		fscanf(file, "%lu", &vmem);

		//reads formatted inout from string line_buffer
        printf("Process Status -- %c\n", ch);
		vmem *= 1024;
		printf("Virtual memory -- %lu\n", vmem);

		fclose(file);
    }

    sprintf(proc_exec, "/proc/%d/exe", proc_id);
    long long int len = readlink(proc_exec, line_buffer, 1000);
    if (len < 0)
        perror("Error: Process doesn't exist\n");
    else 
    {
        line_buffer[len] = '\0';
        printf("Executable Path -- %s\n", line_buffer);
	}

}