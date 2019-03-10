#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#define MAXLINE 1024 
  
// Driver code 
int main(int argc,char *argv[]) { 
    if(argc<2)
    {
        printf("Enter port\n");
        return 0;
    }
    int sfd; 
    char buffer[MAXLINE]; 
    char *hello = "Hello from server"; 
    struct sockaddr_in loc_addr, for_addr; 
      
    // Creating socket file descriptor 
    if ( (sfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    // memset(&servaddr, 0, sizeof(servaddr)); 
    // memset(&cliaddr, 0, sizeof(cliaddr)); 
      
    // Filling server information 
    loc_addr.sin_family    = AF_INET; // IPv4 
    loc_addr.sin_addr.s_addr = INADDR_ANY; 
    loc_addr.sin_port = htons(atoi(argv[1])); 
      
    // Bind the socket with the server address 
    if ( bind(sfd, (const struct sockaddr *)&loc_addr,  
            sizeof(loc_addr)) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    while(1)
    {
        bzero(buffer,MAXLINE);
        int len, n; 
        n = recvfrom(sfd, (char *)buffer, MAXLINE,  
                    MSG_WAITALL, ( struct sockaddr *) &for_addr, 
                    &len); 
        buffer[n] = '\0'; 
        printf("Client : %s\n", buffer); 
        bzero(buffer,MAXLINE);
        fgets(buffer,MAXLINE,stdin);
        sendto(sfd, buffer, strlen(buffer)+1,  
            MSG_CONFIRM, (const struct sockaddr *) &for_addr, 
                len); 
        //printf("Hello message sent.\n"); 
    } 
     
      
    return 0; 
} 