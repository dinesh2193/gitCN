#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 

int main() 
{ 
  
    int fd1[2];  
    int fd2[2];  

     
    pid_t p; 

    pipe(fd1);
    pipe(fd2);
    p = fork(); 
  
    if (p > 0) 
    { 
    	while(1){
    	char buffw[100],buffr[100];
        close(fd1[0]); 
        printf("write in parent:"); 
        scanf("%s",buffw);
        write(fd1[1], buffw, strlen(buffw)+1); 
        sleep(1);
        close(fd2[1]);  
        read(fd2[0], buffr, 100); 
        printf("reading in parent :%s\n", buffr); 
    	}
    }
  
    else
    { 
    	while(1){
    	char buffw[100],buffr[100];
        close(fd1[1]);   
        read(fd1[0], buffr, 100);  
  		printf("reading in child :%s\n",buffr );
        close(fd2[0]); 
        printf("write in child:"); 
  		scanf("%s",buffw);
        write(fd2[1], buffw, strlen(buffw)+1); 
    	}
    } 
} 