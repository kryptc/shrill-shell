#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void setenv_func(char ** str)
{
	if (str[1] == NULL)
	{
		perror("Too few arguments");
		return;
	}
	else if (str[3] != NULL)
	{
		perror("Too many arguments");
		return;
	}
	if (str[2] == NULL)
		setenv(str[1], "", 1);
	else
		setenv(str[1], str[2], 1);
	return;
}

void unsetenv_func(char ** str)
{
	if (str[1] == NULL)
	{
		perror("Too few arguments");
		return;
	}
	unsetenv(str[1]);
	return;
}