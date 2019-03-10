#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/msg.h>
#include<sys/types.h>
#include<string.h>
#include<signal.h>
struct mesg_buffer { 
    long type; 
    char text[100]; 
} msg;
key_t keyr,keyw; 
int msgidr,msgidw;

void fn()
{
	msgrcv(msgidr, &msg, sizeof(msg), msg.type, 0);
	printf("%s\n",msg.text);
}
int main()
{
	msg.type = getpid();
	signal(SIGUSR1,fn);
	printf("%d\n",msg.type);
    keyr = ftok("univ", 65); 
    printf("%d\n",keyr);
   
    msgidr = msgget(keyr, 0666 | IPC_CREAT);
   // msgidw = msgget(keyw, 0666 | IPC_CREAT);
    
    msgsnd(msgidr,&msg, sizeof(msg), 0);


    printf("Enter messages:\n");
    while(1)
    {
    	scanf("%s",msg.text);
    	msgsnd(msgidr, &msg, sizeof(msg), 0);
    }
}
