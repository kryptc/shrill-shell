#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include<sys/stat.h>
#include<sys/types.h>
#include "headers.h"

typedef struct 
{
  int id;
  char name[100];
  int status;

} Proc;

extern int proc_count;

extern Proc proc_arr[100];

extern int root_pid;
extern int clockf;

int shrill_execute(char ** str)
{

	pid_t pid, wpid;
	int status;

	int outrednum = 0, apprednum = 0;
	char outfile[10][30], inpfile[30], appfile[10][30];
	int file, fd;
	int iflag = 0;

	//display another prompt if nothing is entered
	if (*str == NULL)
		return 1;
	
	//quits shell
	if (strcmp(str[0], "quit") == 0)
			exit(0);

	int cnt =0;
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
		cnt++;
	}
	// printf("count=%d\n",cnt );

	int sofuckingdone = 0;

	for ( int i = 0; i < cnt; i ++)
		for(int j = 0; str[i][j] != '\0'; j++)
			if (str[i][j] == '>' || str[i][j] == '<')
				sofuckingdone = 1;
			// else if (str[i][j] == '|')
			// 	sofuckingdone = 2;


	if (sofuckingdone)
	{
		pid = fork();

		if (pid == 0)
		{	
			for (int i = 0; i < cnt; i++)
			{
					if (strcmp(str[i], ">>")==0)
					{
						strcpy(appfile[apprednum], str[i+1]);
						apprednum++;
						str[i][0] = '\0';
						str[i][1] = '\0';
						str[i+1] = '\0';
						i++;

					}
					//input redirection
					else if (strcmp(str[i], "<")==0)
					{
						strcpy(inpfile, str[i+1]);
						iflag = 1;
						str[i] = '\0';
						str[i+1] = '\0';
						i++;
					}
					//output redirection
					else if (strcmp(str[i], ">")==0)
					{
						strcpy(outfile[outrednum], str[i+1]);
						outrednum++;
						str[i] = '\0';
						str[i+1] = '\0';
						i++;

					}
				
			}	


		    if (iflag)
		    {
		    	int fd;
		    	fd = open(inpfile, O_RDONLY, 0);

			    if (fd < 0) 
			     	perror("Input file doesn't exist");
			    if (dup2(fd, 0) < 0) 
			    	perror("Error - input duping");
			    close(fd);
		    }

		    for (int i = 0; i < outrednum; i++)
		    {
		    	  int file;
			      file = open(outfile[i], O_WRONLY | O_TRUNC | O_CREAT, 0644);
			      if (file < 0) 
			      {
			      	perror("Error opening the output file");
			      	exit(0);
			      }
			      if ( dup2 (file, 1) < 0) 
			      	perror("Error while appending");
			      close(file);

		    }

		    for (int i = 0; i < apprednum; i++)
		    {
		    	  int file;
			      file = open(appfile[i], O_WRONLY | O_APPEND | O_CREAT, 0644);
			      if (file < 0) 
			      	perror("Error opening the append output file");
			      if ( dup2 (file, 1) < 0) 
			      	perror("Error while appending");
			      close(file);
			 }

		    if (execvp(str[0],str)<0)	
			{
				// r=1; 
				printf("%s: Command doesn't exist\n", str[0]);
			}
		}
		else
			{
				wait(NULL);
			}
	}
	
	else
	{
		// printf("check1\n");
	  	for (int i = 0; str[i] != NULL; i++)
		{
			if (str[i][0] == '\0') 
			{
				str[i] = NULL;
			}
		}
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
			clockf = 1;
			clock_func(str);
		}

		else if (strcmp(str[0], "jobs") == 0)
		{
			jobs(str);
		}

		else if (strcmp(str[0], "kjob") == 0)
		{
			kjob(str);
		}
		else if (strcmp(str[0], "overkill") == 0)
		{
			overkill();
		}
		else if (strcmp(str[0], "fg") == 0)
		{
			fg(str);
		}
		else if (strcmp(str[0], "bg") == 0)
		{
			bg(str);
		}
		else if (strcmp(str[0], "setenv") == 0)
		{
			setenv_func(str);
		}
		else if (strcmp(str[0], "unsetenv") == 0)
		{
			unsetenv_func(str);
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
					//increment the process count
					proc_count++;
					//add process to process list
					proc_arr[proc_count].id = (int) pid;
      			    strcpy(proc_arr[proc_count].name, str[0]);
      			    proc_arr[proc_count].status = 1;
					// proc_list[*proc_count] = (int) pid;
					// strcpy(proc_name[*proc_count],str[0]);
					// proc_stat[*proc_count] = 1; //running
					
				}
			}
		}
    // printf("check2\n");

	return 0;
}
    
}