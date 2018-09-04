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
			// char *currentdir = malloc (1000 * sizeof(char));
			// getcwd(currentdir, 1000);
			// printf("%s\n",currentdir);
			// free (currentdir);
		}

		//changes directory
		else if (strcmp(str[0], "cd") == 0)
		{
			cd(str);
				// struct stat buf;
			 //    stat(str[1], &buf);
			 //    if (S_ISDIR(buf.st_mode))
				// 	chdir(str[1]);
				// else
				// 	printf("%s is not a directory\n",str[1]);
		}


		//echoes whatever is typed
		else if (strcmp(str[0], "echo") == 0)
		{
			echo_func(str);
			// int i = 1;
			// while (str[i] != NULL)
			// {
			// 	for (int j = 0; j < strlen(str[i]); j++)
			// 	{
			// 		if (str[i][j] != '"' && str[i][j] != '\'')
			// 			printf("%c",str[i][j] );
			// 	}
			// 	printf(" ");
			// 	i++;
			// }
			// printf("\n");
		}

		//lists all files and directories in folder
		else if (strcmp(str[0], "ls") == 0)
		{
			ls(str);
			// int lflag = 0, aflag = 0, extraArg = 0;
			// int dir_num = 0;
			// // char ** dir_list = malloc(50 * sizeof(char));
			// char dir_list[50][50];
			// for (int i = 1; str[i] != NULL; i++)
			// {
			// 	if (str[i][0] == '-')
			// 	{
			// 		if (strcmp(str[i],"-a") == 0)
			// 			aflag = 1;
			// 		else if (strcmp(str[i], "-l") == 0)
			// 			lflag = 1;
			// 		else if (strcmp(str[i], "-la") == 0 || strcmp(str[i], "-al") == 0)
			// 		{
			// 			lflag = 1;
			// 			aflag = 1;
			// 		}
			// 	}
			// 	else
			// 	{
			// 		strcpy(dir_list[dir_num], str[i]);
			// 		dir_num ++;
			// 	}
			// }

			// if (dir_num == 0)
			// {
			// 	strcpy(dir_list[0], ".");
			// 	dir_num++;
			// }
			// if (dir_num > 1)
			// 	extraArg = 1;

			// for (int i = 0; i < dir_num; i++)
			// {
			// 	// Pointer for directory entry
			// 	struct dirent *de; 
			// 	DIR *dr;
			// 	// char * pathToDir = malloc(50*sizeof(char));
			// 	char pathToDir[100];
			// 	strcpy(pathToDir, dir_list[i]);
		 //    	dr = opendir(pathToDir);

			//  	// opendir returns NULL if couldn't open directory
			//     if (dr == NULL)  
			//     {
			//         printf("Could not open directory %s\n", pathToDir);
			//         continue;
			//     }

			//     if (extraArg == 1)
			//     	printf("Files in %s\n",pathToDir);

			//     if (aflag == 1)
			//     {
		 //    		while ((de = readdir(dr)) != NULL)
		 //    		{
		 //    			if (lflag == 0)
		 //    			{
		 //    				if (is_dir(de->d_name))
			// 					printf(" %s%10s%s\n","\033[0;33m",de->d_name,"\033[0m" );
			// 				else
			// 					printf(" %10s\n",de->d_name );
		 //    			}
		 //    			else if (lflag == 1)
		 //    			{
		 //    				char str[100];
		 //    				strcpy(str, pathToDir);
		 //    				strcat(str, "/");
		 //    				strcat(str, de->d_name);
		 //    				print_longlist(str, de->d_name);
		 //    			}
		 //    		}
			//     }

			//     else if (aflag == 0)
			//     {
			//     	while ((de = readdir(dr)) != NULL)
			//     	{
			// 	    	if (de->d_name[0] != '.')
			// 	    		if (lflag == 0)
			// 	    		{
			// 		            if (is_dir(de->d_name))
			// 						printf(" %s%10s%s\n","\033[0;33m",de->d_name,"\033[0m" );
			// 					else
			// 						printf(" %10s\n",de->d_name );
			// 				}
	  //  					else if (lflag == 1)
		 //    			{
		 //    				char str[100];
		 //    				strcpy(str, pathToDir);
		 //    				strcat(str, "/");
		 //    				strcat(str, de->d_name);
		 //    				print_longlist(str, de->d_name);
		 //    			}
			//     	}
			//     }
			//     closedir(dr);
			//     printf("\n");


			// }
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
			// pid = fork();
			// if (pid == 0)
			// {
			// 	sleep(atoi(str[1]));
			// 	printf("Reminder: ");
			// 	for (int j = 2; str[j] != NULL; j++)
			// 	{
			// 		for (int k = 0; k < strlen(str[j]); k++)
			// 			if (str[j][k] != '"')
			// 				printf("%c",str[j][k]);
			// 		printf(" ");
			// 	}
			// 	printf("\n");
			// }
			// else if (pid < 0)
			// 	perror("Error in forking");
			// else
			// 	return 0;
		}

		else if (strcmp(str[0], "clock") == 0)
		{
			clock_func(str);
			// while(1)
			// {
			// 	char clk[1000];
			// 	strcpy(clk,"/sys/class/rtc/rtc0");
			// 	FILE * dt=fopen("/sys/class/rtc/rtc0/date","r");
			// 	char DATE[20];
			// 	fscanf(dt,"%s",DATE);
			// 	printf("%s ",DATE);

			// 	FILE * tm=fopen("/sys/class/rtc/rtc0/time","r");
			// 	char TIME[20];
			// 	fscanf(tm,"%s",TIME);
			// 	printf("%s\n",TIME);

			// 	sleep(atoi(str[2]));
			// }
		}

		//execute commands with execvp here
		else
		{
			pid = fork();
			if (pid == 0)
			{
				if(execvp(str[0], str) == -1)
			       printf("%s: command not found\n",str[0]);
				    // _exit(0);
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