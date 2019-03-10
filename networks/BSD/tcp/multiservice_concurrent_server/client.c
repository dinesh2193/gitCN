#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<netdb.h>
#include<arpa/inet.h>
int main(int argc,char *argv[])
{
	struct hostent *server;
	struct sockaddr_in loc_addr,for_addr;
	if(argc<2)
	{
		printf("Enter port numnber\n");
		return 0;
	}
	

	int sfd = socket(AF_INET,SOCK_STREAM,0);		if(sfd==-1){perror("socket()");}
	
	
	for_addr.sin_family = AF_INET;
	for_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	// server = gethostbyname(argv[1]);				if(server == NULL){fprintf(stderr, "no such server\n" );}
	// bcopy((char *)server->h_addr,(char *)&for_addr.sin_addr.s_addr,server->h_length);
    for_addr.sin_port = htons(atoi(argv[1])); 

    if(connect(sfd,(struct sockaddr *)&for_addr,(socklen_t)sizeof(for_addr))<0)
    {
    	perror("connect()");
    }
    printf("%d\n",sfd);
    printf("Enter which server do u need:\n");
    char ser[6];
    scanf("%s",ser);
    write(sfd,ser,strlen(ser)+1);
    while(1)
    {
    	char msg[1024];
    	  scanf("%s",msg);
          printf("client:%s\n",msg);
    	  if(send(sfd,msg,strlen(msg)+1,0)<0)			{perror("write()");}
    	  bzero(msg,1024);
        //printf("ji\n" );
    	if(read(sfd,msg,8)<0){perror("read()");}
    	printf("server: %s",msg);

    	if(strcmp(msg,"close")==0)
    	{
    		break;
    	}
    }
    close(sfd);
    return 0;
}