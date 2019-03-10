#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<pthread.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<string.h>
#include<signal.h>
char pid_in_char[10];
int pfd;
void fn()
{
	//printf("h1\n");
	
	 char r[100];
	 read(pfd,r,100);
	 printf("%s\n",r);
	 //close(pfd);
	//printf("h2\n");
}
int main()
{
	signal(SIGUSR1,fn);
	//open universal pipe
	
	char *uni = "universal";
	mkfifo(uni,0666);
	char r[100],w[100];
	char buff[10];
	int pid=getpid();
	sprintf(buff,"%d:",pid);
	sprintf(pid_in_char,"%d",pid);
	
	int ufd = open(uni,O_WRONLY);
	write(ufd,buff,strlen(buff)+1);
	close(ufd);

	
	//open process pipe
	mkfifo(pid_in_char,0666);
	pfd = open(pid_in_char,O_RDONLY|O_NONBLOCK);


	
	sleep(1);
	while(1)
	{
		printf("Enter input:\n");
		scanf("%s",r);

		char buffer[100];
		strcpy(buffer,buff);
		strcat(buffer,r);
		
		int ufd = open(uni,O_WRONLY);
		write(ufd,buffer,strlen(buffer)+1);
		close(ufd);
	}

}
