#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pwd.h>
#include<string.h>
#include<dirent.h>

int main()
{
	//pwd stores path of current directory
	char homedir[1004];
	char currentdir[1004];
	getcwd(homedir, 1000);

	//username stores env variable USER as username for display
    char *username=getenv("USER"); 

	//sysname stores name of system
	char sysname[104];
	gethostname(sysname, 100);

	int flag = 1;
	char str[1005];

	char dirhandle[1005];
	dirhandle[0] = '~';
	dirhandle[1] = '\0';

	while(flag)
	{
		printf("%s@%s:%s>",username,sysname,dirhandle);
		// scanf("%s",str);
		gets(str);
		char sub4[5], sub2[3];
		char subcmd[1000];
		strncpy(sub4, str, 4);
		strncpy(sub2, str, 2);

		// char token[2] = " ";
		// char * cmdtoken;
		// cmdtoken = strtok(str, token);
		// printf("%s\n",cmdtoken);
		// int len = strlen(str);

		//quits shell
		if (strcmp(str, "quit") == 0)
		{
			flag = 0;
		}
		//gives current working directory
		else if (strcmp(str, "pwd") == 0)
		{
			getcwd(currentdir, 1000);
			printf("%s\n",currentdir);
		}
		//changes directory
		else if (strcmp(sub2, "cd") == 0)
		{
			memset(subcmd, 0, strlen(subcmd));
			for (int i = 0; i < strlen(str) - 3; i++)
				subcmd[i] = str[i + 3];
			chdir(subcmd);

			//change handle name
			getcwd(currentdir, 1000);

			int i , j, k = 0;
			int current_len = strlen(dirhandle);
			// dirhandle[current_len] = '/';
			for (i = 0, j = 0; i < strlen(currentdir); i++)
			{
				if (currentdir[i] == homedir[j])
					j++;
				else
				{
					dirhandle[current_len + k] = currentdir[i];
					k++;
				}

			}
			dirhandle[++k] = '\0';
		}	
		//echoes whatever is typed
		else if (strcmp(sub4, "echo") == 0)
		{
			memset(subcmd, 0, strlen(subcmd));
			int i, j, flag = 1;
			for (i = 0, j = 0; i < strlen(str) - 5; i++)
			{
				if (str[i + 5] == '"' || str[i + 5] == '\'')
				{
					flag *= (-1);
				}
				if (str[i + 5] == ' ' && str[i + 4] != ' ' && flag > 0)
				{
					subcmd[j] = str[i + 5];
					j++;
				}
				else if (str[i + 5] != '"' && (str[i+ 5] != ' ' || flag < 0))
				{
					subcmd[j] = str[i + 5];
					j++;
				}
			}
				
			//strips away apostrophes
			// if (subcmd[0] == '"' && subcmd[strlen(subcmd) - 1] == '"')
			// {
			// 	int j;
			// 	for (j = 0; j < strlen(subcmd) - 2; j++)
			// 		subcmd[j] = subcmd[j+1];
			// 	subcmd[j] = '\0';
			// }
			printf("%s\n",subcmd);
		}

		//lists all files and directories in folder
		else if (strcmp(sub2, "ls") == 0)
		{
			memset(subcmd, 0, strlen(subcmd));
			for (int i = 3; i < strlen(str); i++)
				subcmd[i-3] = str[i];
			// printf("%s\n", subcmd);

			// Pointer for directory entry
			struct dirent *de;  
		    DIR *dr = opendir(".");

		 	// opendir returns NULL if couldn't open directory
		    if (dr == NULL)  
		    {
		        printf("Could not open current directory" );
		        return 0;
		    }

			if (strcmp(str, "ls") == 0)
			{
			    while ((de = readdir(dr)) != NULL)
			    	if (de->d_name[0] != '.')
			            printf("%s\n", de->d_name);
			}

			else if (strcmp(subcmd, "-a") == 0)
			{
				while ((de = readdir(dr)) != NULL)
		            printf("%s\n", de->d_name);
			}

			closedir(dr);    
		}
		
	}



	return 0;
}


		//echoes whatever is typed
		else if (strcmp(str[0], "echo") == 0)
		{
			int i = 1;
			while (str[i] != NULL)
				printf("%s ",str[i]);
		}

		//cd
			char * default_dir = ".";
			if (str[1] == NULL)
				chdir(default_dir);

			else if (strcmp(str[1], "..") == 0)
			{
				char *currentdir = malloc (1000 * sizeof(char));
				char *newdir = malloc (1000 * sizeof(char));
				getcwd(currentdir, 1000);
				int count = 0;
				for (int j = strlen(currentdir) - 1; j >= 0; j--)
				{
					if (currentdir[j] != '/')
						count++;
					else
					{
						strncpy(newdir, currentdir, strlen(currentdir) - count);
						break;
					}
				}
				chdir(newdir);
			}
			// else

		// else if (strcmp(str[0], "ls") == 0)
		// {
		// 	// Pointer for directory entry
		// 	struct dirent *de; 
		// 	DIR *dr;
		// 	char * pathToDir;

		//     if (str[1] != NULL && strcmp(str[1],"-a")!=0 && strcmp(str[1],"-l")!=0 && 
		//     	strcmp(str[1],"-la")!=0 && strcmp(str[1],"-al")!=0)
		//     {
		//     	strcpy(pathToDir, str[1]);
		//     	dr = opendir(pathToDir);
		//     }
		//     else if (str[2] != NULL)
		//     {
		//     	strcpy(pathToDir, str[2]);
		//     	dr = opendir(pathToDir);
		//     }
		//     else
		//     	dr = opendir(".");


		//  	// opendir returns NULL if couldn't open directory
		//     if (dr == NULL)  
		//     {
		//         printf("Could not open directory %s\n", pathToDir);
		//     }

		//     //checks all flags and possible paths
		//     if (strcmp(str[0], "ls") == 0 && str[1] == NULL)
		// 	{
		// 	    while ((de = readdir(dr)) != NULL)
		// 	    	if (de->d_name[0] != '.')
		// 	            // printf("%s\n", de->d_name);
		// 	            if (is_dir(de->d_name))
		// 					printf(" %s%10s%s\n","\033[0;33m",de->d_name,"\033[0m" );
		// 				else
		// 					printf(" %10s\n",de->d_name );
		// 	}
		// 	else if (strcmp(str[1], "-a") == 0 && str[2] == NULL)
		// 	{
		// 		while ((de = readdir(dr)) != NULL)
		//             // printf("%s\n", de->d_name);
		//             if (is_dir(de->d_name))
		// 					printf(" %s%10s%s\n","\033[0;33m",de->d_name,"\033[0m" );
		// 				else
		// 					printf(" %10s\n",de->d_name );
		// 	}

		// 	else if (strcmp(str[1], "-l") == 0 && str[2] == NULL)
		// 	{
		// 		while ((de = readdir(dr)) != NULL)
		// 			if (de->d_name[0] != '.')
		// 				print_longlist(de->d_name);
		// 	}
		// 	else if ((strcmp(str[1], "-la") == 0 || strcmp(str[1], "-al") == 0)  && str[2] == NULL)
		// 	{
		// 		while ((de = readdir(dr)) != NULL)
		// 			print_longlist(de->d_name);
		// 	}
			
		// 	else if (strcmp(str[1], "-a") == 0)
		// 	{
		// 		while ((de = readdir(dr)) != NULL)
		// 			if (is_dir(de->d_name))
		// 					printf(" %s%10s%s\n","\033[0;33m",de->d_name,"\033[0m" );
		// 				else
		// 					printf(" %10s\n",de->d_name );
		//             // printf("%s\n", de->d_name);
		// 	}

		// 	else if (strcmp(str[1], "-l") == 0)
		// 	{
		// 		while ((de = readdir(dr)) != NULL)
		// 			if (de->d_name[0] != '.')
		// 				//something's wrong here
		// 				print_longlist(de->d_name);
		// 	}
		// 	else if ((strcmp(str[1], "-la") == 0 || strcmp(str[1], "-al") == 0))
		// 	{
		// 		while ((de = readdir(dr)) != NULL)
		// 			print_longlist(de->d_name);
		// 	}
		// 	else 
		// 	{
		// 	    while ((de = readdir(dr)) != NULL)
		// 	    	if (de->d_name[0] != '.')
		// 	    		if (is_dir(de->d_name))
		// 					printf(" %s%10s%s\n","\033[0;33m",de->d_name,"\033[0m" );
		// 				else
		// 					printf(" %10s\n",de->d_name );
		// 	            // printf("%s\n", de->d_name);
		// 	}

		// 	closedir(dr);    
		// }