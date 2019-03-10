#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<sys/shm.h>
#include <signal.h>
int pp[2];
int c;
void fnp()
{
	char* s="parent write.";
	close(pp[0]);
	printf("parent:\n");
	write(pp[1],s,strlen(s));
	kill(c,SIGUSR2);
	sleep(1);
}
void fnc()
{
	char buffer[50];
	close(pp[1]);
	read(pp[0],buffer,50);
	printf("child read:%s\n",buffer);
	kill(getppid(),SIGUSR1);
	sleep(1);
}
int main()
{
	
	pipe(pp);
	signal(SIGUSR1,fnp);
	signal(SIGUSR2,fnc);
	 c=fork();

	if(c)
	{
		sleep(1);
		//kill(c,SIGUSR2);
		while(1)
		{
			
			//sleep(1);
		}
		
	}
	else
	{
		kill(getppid(),SIGUSR1);
		while(1)
		{
			//sleep(1);
			
		}
	}

}