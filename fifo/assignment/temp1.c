#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<pthread.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<signal.h>
#include<string.h>
int main()
{

	char *uni = "98766";
	mkfifo(uni,0666);

	int ufd = open(uni,O_RDWR);


	char* s = "from server";

	write(ufd,s,strlen(s)+1);
	close(ufd);

	int p = 3864;

	kill(p,SIGUSR1);

	return 0;
}