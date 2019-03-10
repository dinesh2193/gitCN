#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<sys/shm.h>
int main()
{
	int pp[2];
	char buffer[50];
	char* s="hello world";
	pipe(pp);
	write(pp[1],s,strlen(s));
	read(pp[0],buffer,50);
	printf("read string:%s\n",buffer);
	return 0;
}