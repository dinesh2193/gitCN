#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include<stdlib.h> 
#include<string.h>
int main(int argc,char* argv[])
{
	int pp1[2],pp2[2],pp3[2];	
	pipe(pp1);
	dup2(pp1[1],1);dup2(pp1[0],0);
	printf("hello\n");
	int c=fork();
	if(c>0){
		char* arg[4];
		char* exe="./";strcat(exe,argv[1]);
		execv(exe,arg);
	}
	else{
		pipe(pp2);
		dup2(pp2[1],1);dup2(pp2[0],0);
		int x=fork();
		if(x>0){
			char* arg[4];
			char* exe="./";strcat(exe,argv[2]);
			execv(exe,arg);
		}
		else{
			pipe(pp3);
			dup2(pp3[1],1);dup2(pp3[0],0);
			int z=fork();
			if(z>0){
				char* arg[4];
				char* exe="./";strcat(exe,argv[3]);
				execv(exe,arg);
			}
			else{
				char* arg[4];
				char* exe="./";strcat(exe,argv[4]);
				execv(exe,arg);
			}
		}
	}
}