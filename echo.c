#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

void echo_func(char ** str)
{
	int i = 1;
	while (str[i] != NULL)
	{
		if(str[i][0]=='$')
  		{
  			if(getenv(str[i]+1) != NULL)
  				printf("%s", getenv(str[i]+1));
  		}
  		else
  		{
  			for (int j = 0; j < strlen(str[i]); j++)
			{
				if (str[i][j] != '"' && str[i][j] != '\'')
					printf("%c",str[i][j] );
			}
  		}
		
		printf(" ");
		i++;
	}
	printf("\n");
}