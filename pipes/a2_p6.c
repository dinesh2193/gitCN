#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
	while(1)
	{
		//sleep(1);
		char buffer[100];
		scanf("%s",buffer);
		printf("process 6 info :%s\n",buffer);
		sleep(1);
	}
	return 0;
}