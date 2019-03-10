#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<pthread.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<string.h>
#include<signal.h>

struct process
{
	char pid[10];
	char grp[3];
};
int compare_upto_colon(struct process p,char *pid,char *grp)
{
	// printf("loop pids:%s %s\n",p.pid,pid);
	// printf("loop grps:%s %s\n",p.grp,grp);
	if(strcmp(p.pid,pid)!=0&&strcmp(p.grp,grp)==0)
		return 0;
	return 1;
}
void get_grp(struct process proc[],int n,char pid[], char grp[])
{
	for(int i=0;i<n;i++)
	{
		
		if(strcmp(proc[i].pid,pid)==0)
		{
			strcpy(grp,proc[i].grp);
			break;
		}
	}
}
void get_pid_grp(char r[],char pid1[])
{
	int j=0,k=0;
	while(r[j]!=':')
	{
		pid1[j]=r[j];
		j++;
	}
	pid1[j]='\0';
	
}
int main()
{
	char *uni[2] = {"g1","g2"};
	int c=2;
	for(int i=0;i<2;i++)
	{
		mkfifo(uni[i],0666);
	}
	int ufd[c];
	for(int i=0;i<c;i++)
	{
		ufd[i]=open(uni[i],O_RDONLY|O_NONBLOCK);
		//printf("%d\n",ufd[i]);
	}
	struct process proc[10];
	int pc = 0;
	//sleep(10);
	
	 for(;;)
	 {
	 	sleep(1);
	 	
		
		// sleep(1);
		for(int i=0;i<c;i++)
		{
			char r[100],w[100];
			int len = read(ufd[i],r,100);
			//printf("%d %d\n",len,ufd[i]);
			//printf("%d\n",len);
			if(len>0)
			{
				//close(ufd);
				//printf("%s\n",r);
				if(r[strlen(r)-1]==':')
				{
					int j=0,k=0;
					while(r[j]!=':')
					{
						proc[pc].pid[j]=r[j];
						j++;
					}
					proc[pc].pid[j]='\0';
					j++;
					while(r[j]!=':')
					{
						proc[pc].grp[i++]=r[j++];
					}
					proc[pc].grp[i]='\0';
					pc++;
					//printf("%s  %s\n",proc[pc].pid,proc[pc].grp);
					//printf("%d\n",mkfifo(proc[pc++].pid,0666) );
					
				}
				else
				{
					//printf("%s\n",r);
					char pid1[10];
					get_pid_grp(r,pid1);
					
					
					char grp1[10];
					
					get_grp(proc,pc,pid1,grp1);
					//printf("%s %s\n",pid1,grp1);
					for(int i=0;i<pc;i++)
					{

						int f=compare_upto_colon(proc[i],pid1,grp1);
						//printf("%d\n",f);
						if(f==0)
						{
							//printf("%s\n",proc[i].pid);
							int client_fd = open(proc[i].pid,O_RDWR);
							write(client_fd,r,strlen(r)+1);
							close(client_fd);
							kill(atoi(proc[i].pid),SIGUSR1);
						}
					}
				}
			 }
		}
	 }

	return 0;
}
