#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<pthread.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<signal.h>
char *uni = "98766";
int pfd;
void fn()
{
	printf("h1\n");
	
	 char r[100];
	 read(pfd,r,100);
	 printf("%s\n",r);
	 //close(pfd);
	printf("h2\n");
}
int main()
{
	signal(SIGUSR1,fn);
	printf("%d\n",getpid());

	
	
	mkfifo(uni,0666);
	pfd = open(uni,O_RDONLY|O_NONBLOCK);
	while(1)
	{
		char ch[100];
		printf("enter input:\n");
		scanf("%s",ch);
		printf("%s\n",ch );
	}
}