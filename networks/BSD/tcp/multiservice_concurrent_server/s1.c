#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
int main()
{
	
	while(1)
	{
		char buf[100];
		read(2,buf,100);
		printf("%s\n",buf );
		write(3,buf,strlen(buf)+1);
		
	}
}