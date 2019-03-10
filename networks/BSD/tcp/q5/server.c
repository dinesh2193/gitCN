#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/select.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<netdb.h>
#include<arpa/inet.h>

int main(int argc, char const *argv[])
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
    

    
    while(1)
    {
    	int for_length = sizeof(for_addr);
        int nsfd = accept(sfd,(struct sockaddr *)&for_addr,&for_length);            if(nsfd<0){perror("accept()");exit(EXIT_FAILURE); }

        int c = fork();
        if(c)
        {
            close(nsfd);
        }   
        
        else
        {

            close(sfd);

            
            int ssfd = socket(AF_INET,SOCK_STREAM,0);

			if(ssfd==-1)
			{
				perror("socket()");
			}

			struct sockaddr_in loc_addr1,for_addr1;
			for_addr1.sin_family = AF_INET;
			for_addr1.sin_addr.s_addr = inet_addr("127.0.0.1"); 
		    for_addr1.sin_port = htons(atoi(argv[1])+1); 

		    if(connect(ssfd,(struct sockaddr *)&for_addr1,(socklen_t)sizeof(for_addr1))<0)
		    {
		    	perror("connect()");
		    }
		    
		    //char r[100];
		    
		    //printf("%s\n",r);	
		    //dup2(nsfd,ssfd);
		    //while(1)
		    
            {
            	char r[1024];
             	write(ssfd,"ji",strlen("hi")+1);
		    	read(ssfd,r,1024);
		    	//printf("client:%s\n",r);
		    	//write(ssfd,r,strlen(r)+1);
		    	//bzero(r,100);
		    	//read(ssfd,r,100);
		    	write(nsfd,r,strlen(r)+1);
		    	//printf("server1:%s\n",r);
            }
            close(ssfd);
            close(nsfd);
		}
        
       
    }
}