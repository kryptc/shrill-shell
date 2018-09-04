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

// int is_dir(const char* path) {
//     struct stat buf;
//     stat(path, &buf);
//     return S_ISDIR(buf.st_mode);
// }

// void pinfo(int proc_id)
// {
// 	char * proc_path = malloc(1002 * sizeof(char)); // for generating path of proc/pid file
// 	char * line_buffer = malloc(1002 * sizeof(char)); // for reading file line by line
// 	char * proc_exec = malloc(1002 * sizeof(char)); // for generating executable of proc/pid file

//     //prints formatted string onto proc_path
//     sprintf(proc_path, "/proc/%d/stat", proc_id);
//     FILE* file = fopen(proc_path, "r");
//     if(!file) 
//         perror("Error: Process doesn't exist\n"); 
//     else
//     {
// 		printf("PID -- %d\n",proc_id);

// 		long unsigned int vmem = 0;
// 		char ch;
// 		int pid;
// 		char str[30];

// 		fscanf(file, "%d", &pid);
// 		fscanf(file, "%s", str);
// 		fscanf(file," %c", &ch);
// 		fscanf(file, "%lu", &vmem);

// 		//reads formatted inout from string line_buffer
//         printf("Process Status -- %c\n", ch);
// 		vmem *= 1024;
// 		printf("Virtual memory -- %lu\n", vmem);

// 		fclose(file);
//     }

//     sprintf(proc_exec, "/proc/%d/exe", proc_id);
//     long long int len = readlink(proc_exec, line_buffer, 1000);
//     if (len < 0)
//         perror("Error: Process doesn't exist\n");
//     else 
//     {
//         line_buffer[len] = '\0';
//         printf("Executable Path -- %s\n", line_buffer);
// 	}

// }

// char* permissions(char *file)
// {
//     struct stat st;
//     char * modeval = malloc(15*sizeof(char *));
//     if(stat(file, &st) == 0)
//     {
//         mode_t perm = st.st_mode;
//         if(perm && S_ISREG(perm)) 
//         	modeval[0]='-';
// 	    else if(perm && S_ISDIR(perm)) 
// 	    	modeval[0]='d';
// 	    else if(perm && S_ISFIFO(perm)) 
// 	    	modeval[0]='|';
// 	    else if(perm && S_ISSOCK(perm)) 
// 	    	modeval[0]='s';
// 	    else if(perm && S_ISCHR(perm)) 
// 	    	modeval[0]='c';
// 	    else if(perm && S_ISBLK(perm)) 
// 	    	modeval[0]='b';
// 	    else modeval[0]='l';  // S_ISLNK
//         modeval[1] = (perm & S_IRUSR) ? 'r' : '-';
//         modeval[2] = (perm & S_IWUSR) ? 'w' : '-';
//         modeval[3] = (perm & S_IXUSR) ? 'x' : '-';
//         modeval[4] = (perm & S_IRGRP) ? 'r' : '-';
//         modeval[5] = (perm & S_IWGRP) ? 'w' : '-';
//         modeval[6] = (perm & S_IXGRP) ? 'x' : '-';
//         modeval[7] = (perm & S_IROTH) ? 'r' : '-';
//         modeval[8] = (perm & S_IWOTH) ? 'w' : '-';
//         modeval[9] = (perm & S_IXOTH) ? 'x' : '-';
//         modeval[10] = '\0';
//         return modeval;     
//     }
  
// }

// void print_longlist(char * filePath, char * fileName)
// {
// 	struct stat st;
// 	char *file_perm = malloc(15 * sizeof(char*));
// 	int file_links;
// 	long long int file_bytes;

//     char string[100];

// 	strcpy(file_perm,permissions(filePath));

// 	if(stat(filePath, &st) == 0)
//     {
// 		file_links = st.st_nlink;

// 		file_bytes = st.st_size;

// 		struct passwd * file_usr;
// 		struct group * file_grp;

// 		file_usr = getpwuid(st.st_uid);
// 		file_grp = getgrgid(st.st_gid);

// 		struct tm * time; 
// 		time = localtime(&st.st_mtime);
// 		strftime(string, 10,"%b",time);

// 		//printing ls output
// 		printf("%s  %d ",file_perm, file_links);
// 		printf("%7s %7s %8lld", file_usr->pw_name, file_grp->gr_name, file_bytes);
// 		printf(" %3s %2d",string, time->tm_mday);
// 		printf(" %2d:%2d",time->tm_hour, time->tm_min);
// 		if (is_dir(filePath))
// 			printf(" %s%10s%s\n","\033[0;33m",fileName,"\033[0m" );
// 		else
// 			printf(" %10s\n",fileName );

// 	}
	
// 	free(file_perm);
// }

// int shrill_execute(char ** str, int * proc_list, char ** proc_name, int *proc_count)
// {

// 	//display another prompt if nothing is entered
// 	if (*str == NULL)
// 		return 1;
	
// 	//quits shell
// 	if (strcmp(str[0], "quit") == 0)
// 			exit(0);

// 	int background = 0;
// 	for (int i = 0; str[i] != NULL; i++)
// 	{
// 		for (int j = 0; str[i][j] != '\0'; j++)
// 			if (str[i][j] == '&') 
// 			{
// 				background = 1;
// 				str[i][j] = '\0';
// 				break;
// 			}
// 	}


// 	pid_t pid, wpid;
// 	int status;

// 		//gives current working directory
// 		if (strcmp(str[0], "pwd") == 0)
// 		{
// 			char *currentdir = malloc (1000 * sizeof(char));
// 			getcwd(currentdir, 1000);
// 			printf("%s\n",currentdir);
// 			free (currentdir);
// 		}

// 		//changes directory
// 		else if (strcmp(str[0], "cd") == 0)
// 		{
// 				struct stat buf;
// 			    stat(str[1], &buf);
// 			    if (S_ISDIR(buf.st_mode))
// 					chdir(str[1]);
// 				else
// 					printf("%s is not a directory\n",str[1]);
// 		}


// 		//echoes whatever is typed
// 		else if (strcmp(str[0], "echo") == 0)
// 		{
// 			int i = 1;
// 			while (str[i] != NULL)
// 			{
// 				for (int j = 0; j < strlen(str[i]); j++)
// 				{
// 					if (str[i][j] != '"' && str[i][j] != '\'')
// 						printf("%c",str[i][j] );
// 				}
// 				printf(" ");
// 				i++;
// 			}
// 			printf("\n");
// 		}

// 		//lists all files and directories in folder
// 		else if (strcmp(str[0], "ls") == 0)
// 		{
// 			int lflag = 0, aflag = 0, extraArg = 0;
// 			int dir_num = 0;
// 			// char ** dir_list = malloc(50 * sizeof(char));
// 			char dir_list[50][50];
// 			for (int i = 1; str[i] != NULL; i++)
// 			{
// 				if (str[i][0] == '-')
// 				{
// 					if (strcmp(str[i],"-a") == 0)
// 						aflag = 1;
// 					else if (strcmp(str[i], "-l") == 0)
// 						lflag = 1;
// 					else if (strcmp(str[i], "-la") == 0 || strcmp(str[i], "-al") == 0)
// 					{
// 						lflag = 1;
// 						aflag = 1;
// 					}
// 				}
// 				else
// 				{
// 					strcpy(dir_list[dir_num], str[i]);
// 					dir_num ++;
// 				}
// 			}

// 			if (dir_num == 0)
// 			{
// 				strcpy(dir_list[0], ".");
// 				dir_num++;
// 			}
// 			if (dir_num > 1)
// 				extraArg = 1;

// 			for (int i = 0; i < dir_num; i++)
// 			{
// 				// Pointer for directory entry
// 				struct dirent *de; 
// 				DIR *dr;
// 				// char * pathToDir = malloc(50*sizeof(char));
// 				char pathToDir[100];
// 				strcpy(pathToDir, dir_list[i]);
// 		    	dr = opendir(pathToDir);

// 			 	// opendir returns NULL if couldn't open directory
// 			    if (dr == NULL)  
// 			    {
// 			        printf("Could not open directory %s\n", pathToDir);
// 			        continue;
// 			    }

// 			    if (extraArg == 1)
// 			    	printf("Files in %s\n",pathToDir);

// 			    if (aflag == 1)
// 			    {
// 		    		while ((de = readdir(dr)) != NULL)
// 		    		{
// 		    			if (lflag == 0)
// 		    			{
// 		    				if (is_dir(de->d_name))
// 								printf(" %s%10s%s\n","\033[0;33m",de->d_name,"\033[0m" );
// 							else
// 								printf(" %10s\n",de->d_name );
// 		    			}
// 		    			else if (lflag == 1)
// 		    			{
// 		    				char str[100];
// 		    				strcpy(str, pathToDir);
// 		    				strcat(str, "/");
// 		    				strcat(str, de->d_name);
// 		    				print_longlist(str, de->d_name);
// 		    			}
// 		    		}
// 			    }

// 			    else if (aflag == 0)
// 			    {
// 			    	while ((de = readdir(dr)) != NULL)
// 			    	{
// 				    	if (de->d_name[0] != '.')
// 				    		if (lflag == 0)
// 				    		{
// 					            if (is_dir(de->d_name))
// 									printf(" %s%10s%s\n","\033[0;33m",de->d_name,"\033[0m" );
// 								else
// 									printf(" %10s\n",de->d_name );
// 							}
// 	   					else if (lflag == 1)
// 		    			{
// 		    				char str[100];
// 		    				strcpy(str, pathToDir);
// 		    				strcat(str, "/");
// 		    				strcat(str, de->d_name);
// 		    				print_longlist(str, de->d_name);
// 		    			}
// 			    	}
// 			    }
// 			    closedir(dr);
// 			    printf("\n");

	
// 			}
// 		}

// 		//calls UDF pinfo()
// 		else if (strcmp(str[0], "pinfo") == 0)
// 		{
// 			if (str[1] == NULL)
// 				pinfo(getpid());
// 			else
// 				pinfo(atoi(str[1]));
// 		}

// 		//reminds user after given time
// 		else if (strcmp(str[0], "remindme") == 0)
// 		{
// 			pid = fork();
// 			if (pid == 0)
// 			{
// 				sleep(atoi(str[1]));
// 				printf("Reminder: ");
// 				for (int j = 2; str[j] != NULL; j++)
// 				{
// 					for (int k = 0; k < strlen(str[j]); k++)
// 						if (str[j][k] != '"')
// 							printf("%c",str[j][k]);
// 					printf(" ");
// 				}
// 				printf("\n");
// 			}
// 			else if (pid < 0)
// 				perror("Error in forking");
// 			else
// 				return 0;
// 		}

// 		else if (strcmp(str[0], "clock") == 0)
// 		{
// 			while(1)
// 			{
// 				char clk[1000];
// 				strcpy(clk,"/sys/class/rtc/rtc0");
// 				FILE * dt=fopen("/sys/class/rtc/rtc0/date","r");
// 				char DATE[20];
// 				fscanf(dt,"%s",DATE);
// 				printf("%s ",DATE);

// 				FILE * tm=fopen("/sys/class/rtc/rtc0/time","r");
// 				char TIME[20];
// 				fscanf(tm,"%s",TIME);
// 				printf("%s\n",TIME);

// 				sleep(atoi(str[2]));
// 			}
// 		}

// 		//execute commands with execvp here
// 		else
// 		{
// 			pid = fork();
// 			if (pid == 0)
// 			{
// 				if(execvp(str[0], str) == -1)
// 			       printf("%s: command not found\n",str[0]);
// 				    // _exit(0);
// 			}
// 			else if (pid < 0)
// 			//error in forking
// 			{
// 				perror("Error in forking");
// 				exit(0);
// 			}

// 			else
// 			{
// 				//parent process
// 				if (background == 0)
// 				{
// 					do
// 					{
// 				  		wpid = waitpid(pid, &status, WUNTRACED);
// 					}
// 					while (!WIFEXITED(status) && !WIFSIGNALED(status));
// 					// exit(0);
// 				}

// 				else
// 				{
// 					//add process to process list
// 					proc_list[*proc_count] = (int) pid;
// 					strcpy(proc_name[*proc_count],str[0]);
// 					//increment the process count
// 					(*proc_count)++;
// 				}

// 			}
// 		}

// 	return 0;
// }


//next we have executeeeee

// #define SHRILL_TOK_DELIM " \t\r\n\a"
// #define SHRILL_CMD_DELIM ";"

// char **shrill_split_cmd(char *line)
// {
//   int i = 0;
//   char **tokens = malloc(2000 * sizeof(char*));
//   char *token;

//   token = strtok(line, SHRILL_CMD_DELIM);
//   while (token != NULL) 
//   {
//     tokens[i] = token;
//     i++;
//     token = strtok(NULL, SHRILL_CMD_DELIM);
//   }
//   tokens[i] = NULL;
//   return tokens;
// }

// char **shrill_split_line(char *line)
// {
//   int i = 0;
//   char **tokens = malloc(2000 * sizeof(char*));
//   char *token;

//   token = strtok(line, SHRILL_TOK_DELIM);
//   while (token != NULL) 
//   {
//     tokens[i] = token;
//     i++;
//     token = strtok(NULL, SHRILL_TOK_DELIM);
//   }
//   tokens[i] = NULL;
//   return tokens;
// }


// char *shrill_read_line(void)
// {
//   char *line = NULL;
//   size_t bufsize = 0; // have getline allocate a buffer for us
//   getline(&line, &bufsize, stdin);
//   return line;
// }

//borderrrrrrrrr - input.c

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
  char homedir[1004];
  getcwd(homedir, 1000);


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
    	printf("\n");
    }

    free(line);

    } while(1);
}


int main(int argc, char **argv)
{
	shrill_loop();
	return 0;
}
