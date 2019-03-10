#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include <sys/stat.h>
int main()
{
	mkfifo("eg1",0666);
	int i=0;
	while(1)
	{
		int fd = open("eg1",O_WRONLY);

		char buffer[100];
		fgets(buffer,100, stdin); 
  
        // Write the input arr2ing on FIFO 
        // and close it 
        write(fd,buffer,strlen(buffer)+1);

		close(fd);
	}
}