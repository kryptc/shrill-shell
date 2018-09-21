#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<sys/stat.h>

// extern int root_pid;
// extern int curr_pid;
// extern int * proc_stat;
// extern int * proc_list;
// extern char * proc_name;
// extern int proc_count;

void signalHandler(int sig, siginfo_t *si, void *context)
{
	printf("anyime?\n");
	int status, pid, pos;
	// switch (sig)
	// {
	// 	case SIGINT: if ( (int) (getpid()) == root_pid )
	// 				 {
	// 				 	perror("hi wassup\n");
	// 					signal(SIGINT, SIG_IGN);
	// 					printf("\n");
	// 					return;
	// 				 }
	// 				 else
	// 				 {
	// 				 	if (kill(getpid(), sig) < 0 )
	// 				 		perror("Ctrl + C detected");
	// 				 }
	// 				 break;

	// 	case SIGTSTP: if ( (int) (getpid()) == root_pid )
	// 				  {
	// 				 	perror("hi wassupbby2\n");

	// 					signal(SIGINT, SIG_IGN);
	// 					return;
	// 				  }
	// 				  else
	// 				  {
	// 				  	//add process to process list
	// 					proc_list[proc_count] = (int) getpid();
	// 					// strcpy(proc_name[*proc_count],str[0]);
	// 					proc_stat[proc_count] = 1; //running
	// 					//increment the process count
	// 					(proc_count)++;
	// 				 	if (kill(getpid(), sig) < 0 )
	// 				 		perror("Ctrl + Z detected");
	// 				  }
	// 				  break;

	// 	case SIGCHLD:   while((pid = waitpid(-1, &status, WNOHANG)) > 0) 
	// 					{
	// 				     	//here we remove the pid from the jobs list
	// 				     	char pname[100];
	// 						for (int k = 0; k < proc_count; k++)
	// 							if (proc_list[k] == pid && proc_stat[k] == 1)
	// 							{
	// 								strcpy(pname, &proc_name[k]);
	// 								proc_stat[k] = 0; //stopped
	// 							}

	// 						if (WEXITSTATUS(status) == 0)
	// 							printf("%s with pid %d exited normally\n",pname, pid);
	// 						else
	// 							printf("%s with pid %d exited abnormally\n",pname, pid);
	// 				    }
	// 				    break;

	// }

	
}