#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/select.h>
#include<netinet/in.h>
#include<sys/socket.h>
struct service_port{
	int port;
	int sfd;
	char description[100];
	char path[100];
}s_ports[25];
int s_ports_count = 0 ;
void create_service_port()
{

}
int main(int argc,char const *argv[])
{
	signal(SIGUSR1,create_service_port);
	if(argc<2)
    {
        printf("Enter port number in command line.\n");
        return 0;
    }
    int connectionless_sfd;
    struct sockaddr_in loc_addr,for_addr;

    if((connectionless_sfd = socket(AF_INET,SOCK_DGRAM,0))<0){perror("connectionless socket()");exit(EXIT_FAILURE);}

    loc_addr.sin_family = AF_INET;
    loc_addr.sin_addr.s_addr = INADDR_ANY;
    loc_addr.sin_port = htons(atoi(argv[1]));

    if(bind(connectionless_sfd,(const struct sockaddr *)&loc_addr,sizeof(loc_addr))<0)
    {
    	perror("connectionless bind failed.");
    	exit(EXIT_FAILURE);
    }
    
    fd_set rfds;
    int retval;
    while(1)
    {
    	FD_ZERO(&rfds);
		for(int i=0;i<s_ports_count;i++)
		{
			FD_SET(s_ports[i].sfd,&rfds);
		}

		retval = select(FD_SETSIZE,&rfds,NULL,NULL,NULL);

		if(retval==-1){perror("select()");exit(EXIT_FAILURE);}
		else if(retval)
		{
			for(int i=0;i<s_ports_count;i++)
			{
				if(FD_ISSET(s_ports[i].sfd,&rfds))
				{
					int for_length = sizeof(for_addr);
					int nsfd = accept(s_ports[i].sfd,(struct sockaddr *)&for_addr,(socklen_t *)&for_length);

					int c=fork();
					if(c)
					{
						close(nsfd);
					}
					else
					{
						
						for(int j=0;j<s_ports_count;j++)
						{
							close(s_ports[i].sfd);
						}
		                dup2(nsfd,2);
						dup2(nsfd,3);
						char *tem[]={"jhdsw",NULL};
						execvp(s_ports[i].path,tem);
					}
				}
			}
		}
    }

}