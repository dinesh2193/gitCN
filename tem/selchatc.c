#include"myheader.h"
#include<string.h>
#include<sys/types.h>
#include<sys/time.h>
char* m = "polc";
int main()
{
   int k = open(m,O_WRONLY);
   int p = getpid();
   char buf[80];
   sprintf(buf,"%d",p);
   char v[80];
   strcpy(v,buf);
   write(k,v,strlen(v)+1);
   int ret = mkfifo(v,0666);
   int y = open(v,O_RDONLY);   
   printf("k1 wrote %s\n",v);
    fd_set readfds;
    FD_ZERO(&readfds);
   while(1)
   {
      int fd = 0; 
      char buffer[80];      
      FD_ZERO(&readfds);
      memset(buffer,'\0',80);
    //FD_SET(0,&readfds); 
      FD_SET(fd,&readfds);  
      FD_SET(y,&readfds);       
      int ready = select(FD_SETSIZE,&readfds,NULL,NULL,NULL);
      if(FD_ISSET(0,&readfds))
      {
      //printf("enter some data into %d\n",y);
      int r = read(fd,buffer,80);
      char send[80];
      strcpy(send,buf);
      strcat(send,"|");
      strcat(send,buffer);
      int u = strlen(send);
      buffer[u] = '\0';
      write(k,send,strlen(send)+1);
      }
      if(FD_ISSET(y,&readfds))
      {
      //printf("data received from node%d\n",fd[1]);
      //char buffer[80];
      memset(buffer,'\0',80);
      int r = read(y,buffer,80);
      buffer[r] = '\0';
      if(r>0)
      printf("data received is %s\n",buffer);
      }       
   //sleep(5);
   //close(k);
   }

}