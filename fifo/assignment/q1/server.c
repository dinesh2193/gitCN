#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<pthread.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<string.h>
#include<signal.h>
int compare_upto_colon(char *a,char *b)
{
	int i=0;
	while(b[i]!=':')
	{
		if(a[i]!=b[i])
		{
			return 0;
		}
		i++;
	}
	return 1;
}



int main()
{
	int ufd ;
	char *uni = "universal";
	mkfifo(uni,0666);
	char proc[10][10];int pc = 0;
	while(1)
	{
		ufd = open(uni,O_RDONLY);
		char r[100],w[100];

		if(read(ufd,r,100))
		{
			close(ufd);
			if(r[strlen(r)-1]==':')
			{
				for(int j=0;j<strlen(r)-1;j++)
				{
					proc[pc][j]=r[j];
				}
				proc[pc++][strlen(r)-1]='\0';
				//printf("%d\n",mkfifo(proc[pc++],0666) );
				
			}
			else
			{
				
				for(int i=0;i<pc;i++)
				{
					int f=compare_upto_colon(proc[i],r);

					if(f==0)
					{
						int client_fd = open(proc[i],O_WRONLY);
						write(client_fd,r,strlen(r)+1);
						close(client_fd);
						kill(atoi(proc[i]),SIGUSR1);
					}
				}
			}
		}

		
	}

	return 0;
}
