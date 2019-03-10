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
    

    int sfd = socket(AF_INET,SOCK_STREAM,0);        if(sfd==-1){perror("socket()");}
    
    
    for_addr.sin_family = AF_INET;
    for_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // server = gethostbyname(argv[1]);             if(server == NULL){fprintf(stderr, "no such server\n" );}
    // bcopy((char *)server->h_addr,(char *)&for_addr.sin_addr.s_addr,server->h_length);
    for_addr.sin_port = htons(atoi(argv[1])); 

    if(connect(sfd,(struct sockaddr *)&for_addr,sizeof(for_addr))<0)
    {
        perror("connect()");
    }

   // while(1)
    {
        //char msg[1024];
        struct sockaddr_in s1_addr;
      //  fgets((char *)s1_addr,1024,stdin);
        //if(write(sfd,msg,strlen(msg)+1)<0)          {perror("write()");}
        //bzero(msg,1024);
        if(read(sfd,(char *)&s1_addr,1024)<0)                    {perror("read()");}
        //printf("server: %s",msg);
        printf("server ip:%s  port:%d\n",inet_ntoa(s1_addr.sin_addr),ntohs(s1_addr.sin_port) );
        //if(strcmp(msg,"close")==0)
        {
          //  break;
        }
    }
    close(sfd);


    return 0;
}