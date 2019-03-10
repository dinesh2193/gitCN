#include"myheader.h"
#include<sys/types.h>
#include<sys/time.h>
char store[10][80];
int split;
char* m = "polc";
int f = 0;
int check(char buffer[])
{
  int l = strlen(buffer);
  int index = 0;
  char pid[10];
  while(index<l && buffer[index]!='|')
  {
    pid[index] = buffer[index];
    index++;
  }
  split = index;  
  pid[index] = '\0';
  int spot = -1;
  for(int i=0;i<f;i++)
  {
    if(strcmp(pid,store[i])==0)
    {
      spot = i;
      break;
    }
  }
return spot;

}
int main()
{
	int count = 0;
	int r = mkfifo(m,0666);
	int k = open(m,O_RDONLY);
  int fd[10];
  
  
  printf("k is%d\n", k);
	while(1)
	{
	    printf("ready\n");	
	    char buf[80];
      int t = read(k,buf,80);
      printf("registered %s\n",buf);
      strcpy(store[f],buf);
      f++;

      if(f==3)
      	break;
	}
	//printf("wait for 5 secs getting prepared...\n");
    sleep(5);
    for(int i=0;i<f;i++)
    {
    	fd[i] = open(store[i],O_WRONLY);
    }
    printf("all are ready\n");

    while(1)
    {
      char buffer[80];
      int r = read(k,buffer,80);
      //printf("read\n");
      int u = check(buffer);
      char h[80];
      int g = 0;
      for(int i=split+1;i<strlen(buffer);i++)
       {
        h[g] = buffer[i];
        g++;
       } 
       h[g] = '\0';
      //printf("message is %s and spot is %d\n",h,u);
      for(int i=0;i<f;i++)
      {
        if(i!=u)
        write(fd[i],h,strlen(h)+1);
      } 
    }  
}