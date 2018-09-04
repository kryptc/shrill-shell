#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include<sys/stat.h>
#include<sys/types.h>
#include "headers.h"


int shrill_execute(char ** str, int * proc_list, char ** proc_name, int *proc_count)
{

	//display another prompt if nothing is entered
	if (*str == NULL)
		return 1;
	
	//quits shell
	if (strcmp(str[0], "quit") == 0)
			exit(0);

	int background = 0;
	for (int i = 0; str[i] != NULL; i++)
	{
		for (int j = 0; str[i][j] != '\0'; j++)
			if (str[i][j] == '&') 
			{
				background = 1;
				str[i][j] = '\0';
				break;
			}
	}


	pid_t pid, wpid;
	int status;

		//gives current working directory
		if (strcmp(str[0], "pwd") == 0)
		{
			pwd();
		}

		//changes directory
		else if (strcmp(str[0], "cd") == 0)
		{
			cd(str);
		}


		//echoes whatever is typed
		else if (strcmp(str[0], "echo") == 0)
		{
			echo_func(str);
		}

		//lists all files and directories in folder
		else if (strcmp(str[0], "ls") == 0)
		{
			ls(str);
		}

		//calls UDF pinfo()
		else if (strcmp(str[0], "pinfo") == 0)
		{
			if (str[1] == NULL)
				pinfo(getpid());
			else
				pinfo(atoi(str[1]));
		}

		//reminds user after given time
		else if (strcmp(str[0], "remindme") == 0)
		{
			remindme(str);
		}

		else if (strcmp(str[0], "clock") == 0)
		{
			clock_func(str);
		}

		//execute commands with execvp here
		else
		{
			pid = fork();
			if (pid == 0)
			{
				if(execvp(str[0], str) == -1)
			       printf("%s: command not found\n",str[0]);
				    _exit(0);
			}
			else if (pid < 0)
			//error in forking
			{
				perror("Error in forking");
				exit(0);
			}

			else
			{
				//parent process
				if (background == 0)
				{
					do
					{
				  		wpid = waitpid(pid, &status, WUNTRACED);
					}
					while (!WIFEXITED(status) && !WIFSIGNALED(status));
					// exit(0);
				}

				else
				{
					//add process to process list
					proc_list[*proc_count] = (int) pid;
					strcpy(proc_name[*proc_count],str[0]);
					//increment the process count
					(*proc_count)++;
				}
			}
		}

	return 0;
}