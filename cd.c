#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<dirent.h>
#include <string.h>
#include<sys/stat.h>
#include<sys/types.h>

extern char homedir[1004];
extern char prev_dir[1004];

void cd(char ** str)
{
	char gotodir[100];
	if (str[1] == NULL)
		strcpy(gotodir, ".");
	else if (strcmp(str[1], "~") == 0 || strcmp(str[1], " ") == 0)
		strcpy(str[1], homedir);
	else if (strcmp(str[1], "-") == 0 )
		strcpy(str[1], prev_dir);

	if (str[1] != NULL)
		strcpy(gotodir, str[1]);

	struct stat buf;
    stat(gotodir, &buf);
    if (S_ISDIR(buf.st_mode))
    {
  		getcwd(prev_dir, 1000);
		chdir(gotodir);
    }
	else
		printf("%s is not a directory\n",gotodir);
}