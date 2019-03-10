#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<pthread.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<string.h>
#include<signal.h>
#include<sys/select.h>
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
	//signal(SIGUSR1,fn);
	//open universal pipe
	
	char *uni = "universal";
	mkfifo(uni,0666);
	char r[100],w[100];
	char buff[10];
	int pid=getpid();
	sprintf(buff,"%d:",pid);
	sprintf(pid_in_char,"%d",pid);
	printf("%s\n",buff);
	int ufd = open(uni,O_WRONLY);
	write(ufd,buff,strlen(buff)+1);
	close(ufd);

	mkfifo(pid_in_char,0666);
	
	//open process pipe
	
	fd_set rfds,wfds;
	struct timeval tv;
	int retval;

	
	sleep(1);
	while(1)
	{
		pfd = open(pid_in_char,O_RDONLY|O_NONBLOCK);

		FD_ZERO(&rfds);
		FD_SET(0,&rfds);
		FD_SET(pfd,&rfds);
		tv.tv_sec = 3;
		tv.tv_usec = 0;
		retval  = select(pfd+1,&rfds,NULL,NULL,&tv);

		if(retval==-1)
		{
			perror("select()");
		}
		else if(retval)
		{
			if(FD_ISSET(0,&rfds))
			{
				scanf("%s",r);
				char buffer[100];
				strcpy(buffer,buff);
				strcat(buffer,r);
				
				int ufd = open(uni,O_RDWR);
				write(ufd,buffer,strlen(buffer)+1);
				close(ufd);

			}
			if(FD_ISSET(pfd,&rfds))
			{
				char r1[100];
				read(pfd,r1,100);
				printf("%s\n",r1);
				close(pfd);
				
			}
		}
		else 
		{
			printf("no text\n");
		}

		
	}

}