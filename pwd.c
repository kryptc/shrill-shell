#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pwd.h>

void pwd()
{
	char *currentdir = malloc (1000 * sizeof(char));
	getcwd(currentdir, 1000);
	printf("%s\n",currentdir);
	free (currentdir);
}