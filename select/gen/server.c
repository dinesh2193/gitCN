#include<stdio.h>
#include<stdlib.h>
#include<sys/select.h>
#include<unistd.h>
#include<string.h>
int main()
{
	fd_set readfds;
	struct timeval tv;
	int retval;
	int fd[2];
	int c=2;

	fd[0]=fileno(popen("./p1","r"));
	fd[1]=fileno(popen("./p2","r"));

	while(1)
	{
		FD_ZERO(&readfds);
		for(int i=0;i<c;i++)
		FD_SET(fd[i],&readfds);

		tv.tv_sec = 5;
		tv.tv_usec = 0;

		retval = select(fd[1]+1,&readfds,NULL,NULL,&tv);

		if (retval == -1)
            perror("select()");
        else if (retval)
         {
         	if(FD_ISSET(fd[0],&readfds))
         	{
         		int pfd = fileno(popen("./p6","w"));
         		char msg[8];
         		read(fd[0],msg,7);
         		write(pfd,msg,strlen(msg)+1);
         		close(pfd);
         	}
         	if(FD_ISSET(fd[1],&readfds))
         	{
         		int pfd = fileno(popen("./p6","w"));
         		char msg[8];
         		read(fd[1],msg,7);
         		write(pfd,msg,strlen(msg)+1);
         		close(pfd);
         	}
         }
         else
         {
         	printf("No data within five seconds.\n");
         }
         sleep(1);
	}

}
