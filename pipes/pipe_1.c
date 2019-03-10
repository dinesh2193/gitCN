#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include <stdlib.h> 
#define size 15 
char* msg1 = "hello,world#1"; 

int main(){
	
	FILE* fd;
	fd  = popen("./p2.exe","w");
	fputs(msg1,fd);
	sleep(1);
	pclose(fd);
}
