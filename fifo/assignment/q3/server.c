#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
struct  datasource {
char pid[10];
char name[3];
int fd;
};

void parse_str(char r[],char pid[],char d[])
{
	int i = 0,j = 0;

	while(r[i]!=':')
	{
		pid[i] = r[i];
		i++;
	}
	pid[i]='\0';

	i++;

	while(i<strlen(r))
	{
		d[j++]=r[i++];
	}
	d[j]='\0';

}
int search(struct datasource ds[],int dc,char d[])
{
	for(int i=0;i<dc;i++)
	{
		if(strcmp(ds[i].pid,d)==0)
		{
			return i;
		}
	}
	return -1;
}
int main()
{
	mkfifo("famous",0666);
	
	struct datasource ds[3];
	int dc = 0;

	while(1)
	{
		//printf("ji\n" );
		int sfd  = open("famous",O_RDONLY|O_NONBLOCK);
		char r[100];
		//printf("ha\n");
		int f;
		f=read(sfd,r,100);
		close(sfd);
		//r[17]='\0';
		printf("%s\n",r);
		if(f<=0){
			//printf("cannot read\n");
		}
		else
		{
			char pid[10],d[10];
			//printf("%s\n",r );

			parse_str(r,pid,d);
			//printf("%s\n%s\n",pid,d);
			int index = search(ds,dc,d);
			printf("%d\n",index);
			if(index==-1)
			{
				char data[6]="./";
				strcat(data,d);
				int fd = fileno(popen(data,"r"));
				//printf("opened:%d\n",fd);
				strcpy(ds[dc].name,d);
				strcpy(ds[dc].pid,pid);
				ds[dc++].fd=fd;

			}
			
		}
		//printf("ji2\n");
		for(int i=0;i<dc;i++)
		{
			//printf("%d\n",i);
			int cfd = open(ds[i].pid,O_RDWR);
			//printf("%d\n",cfd);
			char msg1[18];
			read(ds[i].fd,msg1,17);
			msg1[17]='\0';
			//printf("%s\n",msg1);
			int a =	write(cfd,msg1,strlen(msg1)+1);
			//printf("%d\n",a);
			close(cfd);
		}
		
		sleep(1);

	}
}