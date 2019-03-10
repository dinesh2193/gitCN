#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
  
#define PORT     8080 
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
    char *hello = "Hello from client"; 
    struct sockaddr_in  for_addr; 
  
    // Creating socket file descriptor 
    if ( (sfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
  
  //  memset(&servaddr, 0, sizeof(servaddr)); 
      
    // Filling server information 
    for_addr.sin_family = AF_INET; 
    for_addr.sin_port = htons(atoi(argv[1])); 
    for_addr.sin_addr.s_addr = INADDR_ANY; 
    printf("Enter messages:\n"); 
    while(1)
    {
        int n, len; 
        bzero(buffer,MAXLINE);
        fgets(buffer,MAXLINE,stdin);
        sendto(sfd, buffer, strlen(buffer)+1, 
            MSG_CONFIRM, (const struct sockaddr *) &for_addr,  
                sizeof(for_addr)); 
        
        bzero(buffer,MAXLINE);
        n = recvfrom(sfd, (char *)buffer, MAXLINE,  
                    MSG_WAITALL, (struct sockaddr *) &for_addr, 
                    &len); 
        buffer[n] = '\0'; 
        printf("Server : %s\n", buffer);
    }
     
  
    close(sfd); 
    return 0; 
} 