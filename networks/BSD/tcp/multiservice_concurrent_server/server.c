#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/select.h>
#include<netinet/in.h>
#include<sys/socket.h>

int main(int argc, char const *argv[])
{

	if(argc<=3)
	{
		printf("Enter 3 port numnber:%d\n",argc);
		return 0;
	}

	int sfd[3],n=3;
	struct sockaddr_in loc_addr[3];
	struct sockaddr_in for_addr;
	for(int i=0;i<n;i++)
	{
		sfd[i] = socket(AF_INET,SOCK_STREAM,0);			if(sfd[i]<0){perror("socket()\n");}
		
		loc_addr[i].sin_family = AF_INET;
		loc_addr[i].sin_port = htons(atoi(argv[i+1]));
		loc_addr[i].sin_addr.s_addr = INADDR_ANY;

		if(bind(sfd[i],(struct sockaddr *)&loc_addr[i],sizeof(loc_addr[i]))<0){perror("bind()\n");}
	
		if(listen(sfd[i],10)<0)								{perror("listen()\n");}
	
	}

	fd_set rfds;
	struct timeval tv;
	int retval;
	while(1)
	{
		FD_ZERO(&rfds);
		for(int i=0;i<n;i++)
		{
			FD_SET(sfd[i],&rfds);

		}
		

		retval = select(FD_SETSIZE,&rfds,NULL,NULL,NULL);			
		if(retval==-1){perror("select()");}
		else if(retval)
		{
			for(int i=0;i<n;i++)
			{
				if(FD_ISSET(sfd[i],&rfds))
				{
					int for_length = sizeof(for_addr);
					int nsfd = accept(sfd[i],(struct sockaddr *)&for_addr,(socklen_t *)&for_length);

					int c=fork();
					if(c)
					{
						close(nsfd);
					}
					else
					{
						
						//for(int j=0;j<n;j++)
						{
							close(sfd[i]);
						}

						

						char msg[1024];
		                if(read(nsfd,msg,1024)<0)               {perror("read()");}
		                printf("%s\n",msg);
		                char p[]="./";
		                strcat(p,msg);
		                printf("%s\n",p);
		                char *tem[]={"jhdsw",NULL};
		                dup2(nsfd,2);
						dup2(nsfd,3);
						execvp(p,tem);
						
					}
				}
			}
		}
		else
		{
			printf("no data\n");
		}
	}



	return 0;
}
