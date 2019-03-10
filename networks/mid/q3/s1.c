#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
int main()
{
	while(1)
	{
		char msg[100];
		read(2,msg,100);
		printf("%s",msg);
		scanf("%s",msg);
		write(3,msg,strlen(msg)+1);
	}
}