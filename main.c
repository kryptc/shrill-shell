#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pwd.h>
#include<string.h>
#include<dirent.h>

#include <sys/wait.h>
#include <signal.h>
#include<sys/stat.h>
#include<sys/types.h>
#include <grp.h>
#include <time.h>
#include "headers.h"

char homedir[1004];
char prev_dir[1004];
int root_pid;
int clockf = 0;

typedef struct 
{
  int id;
  char name[100];
  int status;
} Proc;

int proc_count = 0;

Proc proc_arr[100];

void display_prompt(char * homedir)
{
	char dirhandle[1005];
	dirhandle[0] = '~';
	dirhandle[1] = '\0';
	char currentdir[1004];
	//change handle name
	getcwd(currentdir, 1000);

	int i, j, k = 0, flag = 0;
	int current_len = strlen(dirhandle);

	//checks if current directory is before the home dir
	for (i = 0; i < strlen(homedir); i++)
		if (currentdir[i] != homedir[i])
		{
			flag = 1;
			break;
		}

	if (flag == 0)
	{
		for (i = 0, j = 0; i < strlen(currentdir); i++)
			if (currentdir[i] == homedir[j])
				j++;
			else
			{
				dirhandle[current_len + k] = currentdir[i];
				k++;
			}
		dirhandle[++k] = '\0';
	}
	else 
		strcpy(dirhandle, currentdir);

	//username stores env variable USER as username for display
    char *username=getenv("USER"); 

	//sysname stores name of system
	char sysname[104];
	gethostname(sysname, 100);
	printf("%s%s@%s%s:%s%s>","\033[0;31m",username,sysname,"\033[0;36m",dirhandle,"\033[0m");
}


//signal handlers

void interruptHandler()
{
	clockf = 0;

	if (getpid() != root_pid)
	{
		// printf("\n");
		// display_prompt(homedir);
		return;
	}
	signal(SIGINT, interruptHandler);
	fflush(stdout); 
}

//FIX THISSSSS!!!
void stopHandler()
{
	clockf = 0;
	if (getpid() != root_pid)
		return;
	signal(SIGTSTP, SIG_IGN);

	// signal(SIGTSTP, stopHandler);
 	// perror("Ctrl + Z detected");
 	return;
}


void shrill_loop()
{
  char *line;
  char **args, **c_args, **p_args;
  int loop_status;

  //pwd stores path of current directory
  getcwd(homedir, 1000);

  strcpy(prev_dir, homedir);

  int flag = 1;
  char str[1005];


  int status;
  pid_t pid;

  //ctrl+c
  signal(SIGINT, interruptHandler);
   //idk some signal
  // signal(SIGQUIT, SIG_IGN);
  //don't comment this out in case everything goes to hell
  //ctrl+z
  signal(SIGTSTP, stopHandler);

  signal(SIGTTOU, SIG_IGN);

  do {
 
	    //call print prompt function
	    display_prompt(homedir);

	    line = shrill_read_line();
	    c_args = shrill_split_cmd(line);
	    int j = 0;
	    while (c_args[j] != NULL)
	    {
			while((pid = waitpid(-1, &status, WNOHANG)) > 0) 
			{
		     	//here we remove the pid from the jobs list
		     	char pname[100];
				for (int k = 1; k <= proc_count; k++)
					// if (proc_arr[k].id == pid && proc_arr[k].status == 1)
					if (proc_arr[k].id == pid)

					{
						strcpy(pname, proc_arr[k].name);
						proc_arr[k].status = 0; //stopped
					}


				if (WEXITSTATUS(status) == 0)
					printf("%s with pid %d exited normally\n",pname, pid);
				else
					printf("%s with pid %d exited abnormally\n",pname, pid);
		    }

		    int endthismisery = 0;

		    for ( int i = 0; c_args[i] != NULL; i ++)
				for(int j = 0; c_args[i][j] != '\0'; j++)
					if (c_args[i][j] == '|' )
						endthismisery = 1;

			if (endthismisery)
			{
				int user_pipe[2];

				if (pipe(user_pipe) != 0)
			    	perror("Pipe not created properly");

				pid_t pidin = 0, pidout = 1, pipe_proc;
				int yeet = 0;
				p_args = shrill_split_pip(c_args[j]);
			   
			    for (int p = 0; p_args[p] != NULL; p++)
			    {
			    	args = shrill_split_line(p_args[p]);
					pipe(user_pipe);

			    	pipe_proc = fork();
		    	    if (pipe_proc == 0) 
		    	    {
				    	// Child process
				    	dup2(yeet, 0);
				        // close(0); // Release fd no - 0
				        if (p_args[p + 1] != NULL)
				        	dup2(user_pipe[1], 1);
				        close(user_pipe[0]); // Close pipe fds since useful one is duplicated
			    		loop_status = shrill_execute(args);
			    		free(args);

			    		exit(0);

				    } 
				    else if (pipe_proc < 0)
				    {
				    	perror("Forking went wrong");
				    	exit(0);
				    }
				    else
				    {
				    	do
						{
					  		waitpid(pid, &status, WUNTRACED);
						}
						while (!WIFEXITED(status) && !WIFSIGNALED(status));
						close(user_pipe[1]);
						yeet = user_pipe[0];
						j++;

				    }

			    }

			}
			else
			{
				args = shrill_split_line(c_args[j]);
		    	loop_status = shrill_execute(args);
		    	free(args);
			}
		    
		    j++;
	    	
	    }

	    free(line);

    } while(1);
}


int main(int argc, char **argv)
{
	root_pid = getpid();
	shrill_loop();
	return 0;
}
