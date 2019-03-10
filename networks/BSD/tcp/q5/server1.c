#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>
int main(int argc,char *argv[])
{
    printf("run server1 with port p and then run server with port p-1\n");
	if(argc!=2)
	{
		printf("Enter port numnber\n");
		return 0;
	}

	int sfd = socket(AF_INET,SOCK_STREAM,0);

	if(sfd==-1)
	{
		perror("socket()");
	}

	struct sockaddr_in loc_addr,for_addr;
	loc_addr.sin_family = AF_INET;
	loc_addr.sin_addr.s_addr = INADDR_ANY; 
    loc_addr.sin_port = htons(atoi(argv[1])); 

    if(bind(sfd,(struct sockaddr *)&loc_addr,(socklen_t)sizeof(loc_addr))<0)				{perror("bind()");}

    if (listen(sfd,4) < 0) 														{perror("listen"); } 
    

    int for_length = sizeof(for_addr);
    
    while(1)
    {
        int nsfd = accept(sfd,(struct sockaddr *)&for_addr,&for_length);            if(nsfd<0){perror("accept()"); }

        int c = fork();
        if(c)
        {
            close(nsfd);
        }   
        
        else
        {

            close(sfd);
            struct sockaddr_in serv;
            int serv_len;
            getsockname(nsfd,(struct sockaddr *)&serv,(socklen_t *)&serv_len);
            printf("server ip:%s  port:%d\n",inet_ntoa(serv.sin_addr),ntohs(serv.sin_port) );
            char msg1[100];
            read(nsfd,msg1,100);
            write(nsfd,(char *)&serv,sizeof(serv));
            while(1)
            {
                char msg[1024];
                if(read(nsfd,msg,1024)<0)               {perror("read()");}
                printf("client:%s\n",msg);
                fgets(msg,1024,stdin);
                if(write(nsfd,msg,strlen(msg)+1)<0)     {perror("write()");}
                if(strcmp(msg,"close")==0)
                {
                    break;
                }
            }
             close(nsfd);
            close(sfd);
        }
        
       
    }
   
    return 0;


}