#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include <grp.h>
#include <time.h>
#include<string.h>

extern int clockf;

void clock_func(char ** str)
{
	while(clockf)
	{
		char clk[1000];
		strcpy(clk,"/sys/class/rtc/rtc0");
		FILE * dt=fopen("/sys/class/rtc/rtc0/date","r");
		char DATE[20];
		fscanf(dt,"%s",DATE);
		printf("%s ",DATE);

		FILE * tm=fopen("/sys/class/rtc/rtc0/time","r");
		char TIME[20];
		fscanf(tm,"%s",TIME);
		printf("%s\n",TIME);

		sleep(atoi(str[2]));
	}
}