#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<poll.h>
#include<stdlib.h>
#include<wait.h>
int main(int argc,char *argv[])
{
	int pfd[2];
	pipe(pfd);

	

	for(int i=1;i<argc;i++)
	{
		//printf("%d\n",argc);
		int c=fork();
		if(c)
		{
			wait(NULL);
			close(pfd[1]);
		}
		else
		{
			//printf("child:%d\n",i);
			if(i==1)
			{
				dup2(pfd[1],1);
			}
			else if(i==argc-1)
			{
				dup2(pfd[0],0);
			}
			else
			{
				dup2(pfd[0],0);
				dup2(pfd[1],1);
			}
			char a[100]="./a1_";
			strcat(a,argv[i]);
			char *arg[]={"ji",NULL};
			execvp(a,arg);
		}
	}
	return 0;
}