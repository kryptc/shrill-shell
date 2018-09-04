#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int remindme(char ** str)
{
	pid_t pid;
	pid = fork();
	if (pid == 0)
	{
		sleep(atoi(str[1]));
		printf("Reminder: ");
		for (int j = 2; str[j] != NULL; j++)
		{
			for (int k = 0; k < strlen(str[j]); k++)
				if (str[j][k] != '"')
					printf("%c",str[j][k]);
			printf(" ");
		}
		printf("\n");
	}
	else if (pid < 0)
		perror("Error in forking");
	else
		return 0;
}