
#include "myheader.h"
#include <netdb.h>

#define SERVER_PORT    12345
#define BUFFER_LENGTH    250
#define FALSE              0
#define SERVER_NAME     "ServerHostName"

void main(int argc, char *argv[])
{

		int    sfd=-1, rc, bytesReceived;
		char   buffer[100] = "Hello from Client \n";
		char   server[BUFFER_LENGTH];
		struct sockaddr_in serveraddr;
		struct sockaddr_in host;
		int hostlen = sizeof(host);
		memset(&serveraddr, 0, sizeof(serveraddr));
		serveraddr.sin_family      = AF_INET;
		serveraddr.sin_addr.s_addr = 0x0100007f;
		serveraddr.sin_port        = htons(8080);   

		sfd = socket(AF_INET, SOCK_STREAM, 0);
			if (sfd < 0)
			{
				perror("socket() failed");
				//break;
			}
			//memset(buffer,'\0',sizeof(buffer)); 
         //rc = send(sfd, buffer, sizeof(buffer), 0);
		   rc = connect(sfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
			if (rc < 0)
			{
				perror("connect() failed");
				//break;
			}

		   if (getsockname(sfd, (struct sockaddr *)&host, (socklen_t*)&hostlen) == -1) {
				perror("getsockname() failed");
				//break;
			}

         printf("server details after getsockname\n");
	      printf("%x\n", serveraddr.sin_addr.s_addr);
	      printf("%d\n", ntohs(serveraddr.sin_port));
         printf("client details after getsockname\n");
	      printf("%x\n", host.sin_addr.s_addr);
	      printf("%d\n", ntohs(host.sin_port));
         while(1)
         {
	      printf("send some data to server\n");
	      memset(buffer,'\0',sizeof(buffer));
	      read(0,buffer,100);
			rc = send(sfd, buffer, strlen(buffer)+1, 0);
			if (rc < 0)
			{
				perror("send() failed");
			//	break;
			}

		   }


	if (sfd != -1)
		close(sfd);

		

}