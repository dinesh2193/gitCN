#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/select.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<pthread.h>

 void *s2(void *par)
{
  int nsfd = *(int *)par;

  while(1)
  {
    char msg[100];
    read(nsfd,msg,100);
    char s[100];
    sprintf(s,"%d",strlen(msg));
    write(nsfd,s,strlen(s));
  }
}
int main(int argc, char const *argv[])
{
   if(argc<=2)
   {
      printf("Enter 2 port numnber\n");
      return 0;
   }

   int sfd[2],n=2;
   struct sockaddr_in loc_addr[2];
   struct sockaddr_in for_addr;
   for(int i=0;i<n;i++)
   {
      sfd[i] = socket(AF_INET,SOCK_STREAM,0);         if(sfd[i]<0){perror("socket()\n");}
      
      loc_addr[i].sin_family = AF_INET;
      loc_addr[i].sin_port = htons(atoi(argv[i+1]));
      loc_addr[i].sin_addr.s_addr = INADDR_ANY;

      if(bind(sfd[i],(struct sockaddr *)&loc_addr[i],sizeof(loc_addr[i]))<0){perror("bind()\n");}
   
      if(listen(sfd[i],10)<0)                      {perror("listen()\n");}
   
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
         
         printf("ret:%d\n",retval);
        if(FD_ISSET(sfd[0],&rfds))
        {
          printf("%s\n","s1" );
          int for_length = sizeof(for_addr);
          int nsfd = accept(sfd[0],(struct sockaddr *)&for_addr,(socklen_t *)&for_length);

          int c= fork();
          if(c)
          {
            close(nsfd);
          }
          else
          {
            close(sfd[0]);
            close(sfd[1]);

            dup2(nsfd,2);
            dup2(nsfd,3);
            char *tem[]={"./s1",NULL};
            execvp("./s1",tem);
          }

        }
        if(FD_ISSET(sfd[1],&rfds))
        {
          printf("%s\n","s2" );
          int for_length = sizeof(for_addr);
          int nsfd = accept(sfd[1],(struct sockaddr *)&for_addr,(socklen_t *)&for_length);

          pthread_t tid;

          pthread_create(&tid,NULL,s2,(void *)&nsfd);

          pthread_join(tid,NULL);

        }

      }
      else
      {
         printf("no data\n");
      }
   }



   return 0;
}