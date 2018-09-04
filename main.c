#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pwd.h>
#include<string.h>
#include<dirent.h>

#include <sys/wait.h>

#include<sys/stat.h>
#include<sys/types.h>
#include <grp.h>
#include <time.h>
#include "headers.h"

char homedir[1004];
char prev_dir[1004];

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

void shrill_loop()
{
  char *line;
  char **args, **c_args;
  int loop_status;

  //pwd stores path of current directory
  getcwd(homedir, 1000);

  strcpy(prev_dir, homedir);

  int flag = 1;
  char str[1005];


  int status;
  pid_t pid;

  int * proc_list = malloc(100 * sizeof(int));
  char * proc_name = malloc(100 * sizeof(char));
  int proc_count = 0;



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
			for (int k = 0; k < proc_count; k++)
				if (proc_list[k] == pid)
				{
					strcpy(pname, &proc_name[k]);
					proc_list[k] = -1;
				}

			if (WEXITSTATUS(status) == 0)
				printf("%s with pid %d exited normally\n",pname, pid);
			else
				printf("%s with pid %d exited abnormally\n",pname, pid);
	    }

    	args = shrill_split_line(c_args[j]);
    	loop_status = shrill_execute(args, proc_list, &proc_name, &proc_count);
    	j++;
    	free(args);
    	// printf("\n");
    }

    free(line);

    } while(1);
}


int main(int argc, char **argv)
{
	shrill_loop();
	return 0;
}
