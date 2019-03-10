#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>

int main()
{
	char pid_in_char[100];							//get pid
	sprintf(pid_in_char,"%d",getpid());				//convert into char array

	mkfifo(pid_in_char,0666);
	int cfd=open(pid_in_char,O_RDONLY|O_NONBLOCK);   //open read end of client fifo


	printf("Enter service needed(d1/d2/d3):\n");	//request for service
	char service[10];
	scanf("%s",service);

	strcat(pid_in_char,":");
	strcat(pid_in_char,service);					//packing pid and service into pid_in_char

	mkfifo("famous",0666);
	int fd = open("famous",O_RDWR);
	printf("%s\n",pid_in_char);		
	printf("%d\n",fd);	
	write(fd,pid_in_char,strlen(pid_in_char)+1);
	//close(fd);										//write in famous fifo
	printf("%d\n",cfd);
	sleep(1);

	while(1)
	{
		char msg[100];
		int f =read(cfd,msg,100);
		
		if(f)
		printf("%s\n",msg);

		sleep(1);
	}

	return 0;

}