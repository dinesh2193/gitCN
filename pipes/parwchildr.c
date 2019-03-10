#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<sys/shm.h>
int main()
{
	int pp[2];
	pipe(pp);

	int c=fork();

	if(c)
	{
		while(1)
		{
			char* s="parent write.";
			close(pp[0]);
			printf("parent:\n");
			write(pp[1],s,strlen(s));
			sleep(1);
		}
		
	}
	else
	{
		while(1)
		{
			sleep(1.2);
			char buffer[50];
			close(pp[1]);
			read(pp[0],buffer,50);
			printf("child read:%s\n",buffer);
		}
	}

}