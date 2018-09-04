#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<dirent.h>

#include<sys/stat.h>
#include<sys/types.h>

void cd(char ** str)
{
	struct stat buf;
    stat(str[1], &buf);
    if (S_ISDIR(buf.st_mode))
		chdir(str[1]);
	else
		printf("%s is not a directory\n",str[1]);
}