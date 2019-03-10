#include<stdio.h>
#include<stdlib.h>
#include<sys/select.h>
#include<unistd.h>
#include<string.h>
#include<poll.h>
int main()
{
	struct pollfd pfd[2];
	int tv;
	int retval;
	int fd[2];
	int c=2;

	pfd[0].fd=fileno(popen("./p1","r"));
	pfd[0].events|=POLLIN;
	pfd[1].fd=fileno(popen("./p2","r"));
	pfd[1].events|=POLLIN;
	tv= 5000;
	while(1)
	{
		
		
		

		retval = poll(pfd,2,tv);

		if (retval == -1)
            perror("select()");
        else if (retval)
         {
         	if(pfd[0].revents&POLLIN)
         	{
         		int pfd1 = fileno(popen("./p6","w"));
         		char msg[8];
         		read(pfd[0].fd,msg,7);
         		write(pfd1,msg,strlen(msg)+1);
         		close(pfd1);
         	}
         	if(pfd[1].revents&POLLIN)
         	{
         		int pfd1 = fileno(popen("./p6","w"));
         		char msg[8];
         		read(pfd[1].fd,msg,7);
         		write(pfd1,msg,strlen(msg)+1);
         		close(pfd1);
         	}
         }
         else
         {
         	printf("No data within five seconds.\n");
         }
         sleep(1);
	}

}