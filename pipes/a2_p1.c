#include<stdio.h>
#include <stdlib.h>
#include <poll.h>
#include <unistd.h>
int main(int argc, char const *argv[])
{
	
	int fd1,fd2,fd3,fd4,fd5;

	fd2=fileno(popen("./a2_p2","r"));
	fd3=fileno(popen("./a2_p3","r"));
	fd4=fileno(popen("./a2_p4","r"));
	fd5=fileno(popen("./a2_p5","r"));

	struct pollfd pfd[4];

	pfd[0].fd=fd2;
	pfd[1].fd=fd3;
	pfd[2].fd=fd4;
	pfd[3].fd=fd5;

	pfd[0].events = POLLIN;
	pfd[1].events = POLLIN;
	pfd[2].events = POLLIN;
	pfd[3].events = POLLIN;

	while(1)
	{
		//printf("ji\n");
		int res = poll(pfd,4,10);
		//printf("%d\n",res );
		if(res)
		{
			for(int i=0;i<4;i++)
			{
				if(pfd[i].revents&POLLIN)
				{
					//printf("process-%d is ready\n",i+1 );
					char buffer[100];
					read(pfd[i].fd,buffer,100);

					fd1 = fileno(popen("./a2_p6","w"));
					dup2(fd1,1);
					printf("%s\n",buffer);
				}
			}
		}
		else
		{
			fd1 = fileno(popen("./a2_p6","w"));
			dup2(fd1,1);
			printf("process:1");
		}
		//sleep(1);
	}
	return 0;
}