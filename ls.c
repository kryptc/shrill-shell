#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pwd.h>
#include<string.h>
#include<dirent.h>
#include <grp.h>
#include<sys/stat.h>
#include<sys/types.h>
#include <time.h>

int is_dir(const char* path) 
{
    struct stat buf;
    stat(path, &buf);
    return S_ISDIR(buf.st_mode);
}

char* permissions(char *file)
{
    struct stat st;
    char * modeval = malloc(15*sizeof(char *));
    if(stat(file, &st) == 0)
    {
        mode_t perm = st.st_mode;
        if(perm && S_ISREG(perm)) 
        	modeval[0]='-';
	    else if(perm && S_ISDIR(perm)) 
	    	modeval[0]='d';
	    else if(perm && S_ISFIFO(perm)) 
	    	modeval[0]='|';
	    else if(perm && S_ISSOCK(perm)) 
	    	modeval[0]='s';
	    else if(perm && S_ISCHR(perm)) 
	    	modeval[0]='c';
	    else if(perm && S_ISBLK(perm)) 
	    	modeval[0]='b';
	    else modeval[0]='l';  // S_ISLNK
        modeval[1] = (perm & S_IRUSR) ? 'r' : '-';
        modeval[2] = (perm & S_IWUSR) ? 'w' : '-';
        modeval[3] = (perm & S_IXUSR) ? 'x' : '-';
        modeval[4] = (perm & S_IRGRP) ? 'r' : '-';
        modeval[5] = (perm & S_IWGRP) ? 'w' : '-';
        modeval[6] = (perm & S_IXGRP) ? 'x' : '-';
        modeval[7] = (perm & S_IROTH) ? 'r' : '-';
        modeval[8] = (perm & S_IWOTH) ? 'w' : '-';
        modeval[9] = (perm & S_IXOTH) ? 'x' : '-';
        modeval[10] = '\0';
        return modeval;     
    }
  
}

void print_longlist(char * filePath, char * fileName)
{
	struct stat st;
	char *file_perm = malloc(15 * sizeof(char*));
	int file_links;
	long long int file_bytes;

    char string[100];

	strcpy(file_perm,permissions(filePath));

	if(stat(filePath, &st) == 0)
    {
		file_links = st.st_nlink;

		file_bytes = st.st_size;

		struct passwd * file_usr;
		struct group * file_grp;

		file_usr = getpwuid(st.st_uid);
		file_grp = getgrgid(st.st_gid);

		struct tm * time; 
		time = localtime(&st.st_mtime);
		strftime(string, 10,"%b",time);

		//printing ls output
		printf("%s  %d ",file_perm, file_links);
		printf("%7s %7s %8lld", file_usr->pw_name, file_grp->gr_name, file_bytes);
		printf(" %3s %2d",string, time->tm_mday);
		printf(" %2d:%2d",time->tm_hour, time->tm_min);
		if (is_dir(filePath))
			printf(" %s%10s%s\n","\033[0;33m",fileName,"\033[0m" );
		else
			printf(" %10s\n",fileName );

	}
	
	free(file_perm);
}

void ls(char ** str)
{
	int lflag = 0, aflag = 0, extraArg = 0;
	int dir_num = 0;
	// char ** dir_list = malloc(50 * sizeof(char));
	char dir_list[50][50];
	for (int i = 1; str[i] != NULL; i++)
	{
		if (str[i][0] == '-')
		{
			if (strcmp(str[i],"-a") == 0)
				aflag = 1;
			else if (strcmp(str[i], "-l") == 0)
				lflag = 1;
			else if (strcmp(str[i], "-la") == 0 || strcmp(str[i], "-al") == 0)
			{
				lflag = 1;
				aflag = 1;
			}
		}
		else
		{
			strcpy(dir_list[dir_num], str[i]);
			dir_num ++;
		}
	}

	if (dir_num == 0)
	{
		strcpy(dir_list[0], ".");
		dir_num++;
	}
	if (dir_num > 1)
		extraArg = 1;

	for (int i = 0; i < dir_num; i++)
	{
		// Pointer for directory entry
		struct dirent *de; 
		DIR *dr;
		// char * pathToDir = malloc(50*sizeof(char));
		char pathToDir[100];
		strcpy(pathToDir, dir_list[i]);
    	dr = opendir(pathToDir);

	 	// opendir returns NULL if couldn't open directory
	    if (dr == NULL)  
	    {
	        printf("Could not open directory %s\n", pathToDir);
	        continue;
	    }

	    if (extraArg == 1)
	    	printf("Files in %s\n",pathToDir);

	    if (aflag == 1)
	    {
    		while ((de = readdir(dr)) != NULL)
    		{
    			if (lflag == 0)
    			{
    				if (is_dir(de->d_name))
						printf(" %s%10s%s\n","\033[0;33m",de->d_name,"\033[0m" );
					else
						printf(" %10s\n",de->d_name );
    			}
    			else if (lflag == 1)
    			{
    				char str[100];
    				strcpy(str, pathToDir);
    				strcat(str, "/");
    				strcat(str, de->d_name);
    				print_longlist(str, de->d_name);
    			}
    		}
	    }

	    else if (aflag == 0)
	    {
	    	while ((de = readdir(dr)) != NULL)
	    	{
		    	if (de->d_name[0] != '.')
		    		if (lflag == 0)
		    		{
			            if (is_dir(de->d_name))
							printf(" %s%10s%s\n","\033[0;33m",de->d_name,"\033[0m" );
						else
							printf(" %10s\n",de->d_name );
					}
					else if (lflag == 1)
    			{
    				char str[100];
    				strcpy(str, pathToDir);
    				strcat(str, "/");
    				strcat(str, de->d_name);
    				print_longlist(str, de->d_name);
    			}
	    	}
	    }
	    closedir(dr);
	    printf("\n");


	}
}