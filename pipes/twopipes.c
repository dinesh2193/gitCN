#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<sys/shm.h>
int main()
{
	int pp1[2];
	int pp2[2];
	pipe(pp1);
	pipe(pp2);
	int c=fork();

	if(c)
	{
		while(1)
		{
			char* s="parent written.";
			close(pp1[0]);
			printf("parent write:\n");
			write(pp1[1],s,strlen(s));
			sleep(1);
			close(pp2[1]);
			char buffer[50];
			read(pp2[0],buffer,50);
			printf("parent read:%s\n",buffer);
			//sleep(1);
		}
		
	}
	else
	{
		while(1)
		{
			//sleep(1.2);
			char buffer[50];
			close(pp1[1]);
			read(pp1[0],buffer,50);
			printf("child read:%s\n",buffer);
			char* s="child written.";
			
			close(pp2[0]);
			printf("child write:\n");
			write(pp2[1],s,strlen(s));
			
		}
	}

}