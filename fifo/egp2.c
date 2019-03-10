#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include <stdlib.h>
#include<sys/types.h>
#include <sys/stat.h>
int main()
{
	mkfifo("eg1",0666);

	while(1)
	{
		int fd = open("eg1",O_RDONLY);

		char buffer[100];

		read(fd,buffer,100);

		printf("in p2:%s\n",buffer);

		close(fd);
		sleep(1);
	}
}