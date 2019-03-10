#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/msg.h>
#include<sys/types.h>
#include<string.h>
#include<signal.h>
#include<sys/select.h>
struct mesg_buffer { 
    long type; 
    char text[100]; 
} msg;
key_t keyr,keyw; 
int msgidr,msgidw;
int main()
{
	msg.type = getpid();
	//signal(SIGUSR1,fn);
	printf("%d\n",msg.type);
    keyr = ftok("uni_read", 65);
    keyw = ftok("uni_write", 65); 
    printf("%d\n",keyr);
    printf("%d\n",keyw);
    msgidr = msgget(keyr, 0666 | IPC_CREAT);
    msgidw = msgget(keyw, 0666 | IPC_CREAT);
    
    msgsnd(msgidr,&msg, sizeof(msg), 0);

    fd_set rfds,wfds;
    struct timeval tv;
    int retval;

    printf("Enter messages:\n");

    while(1)
    {
        FD_ZERO(&rfds);
        FD_SET(0,&rfds);
        FD_SET(msgidw,&rfds);
        tv.tv_sec = 2;
        tv.tv_usec = 0;
        retval  = select(msgidw+1,&rfds,NULL,NULL,NULL);

        if(retval==-1)
        {
            perror("select()");
        }
        else if(retval)
        {
            if(FD_ISSET(0,&rfds))
            {
                scanf("%s",msg.text);
                msgsnd(msgidr, &msg, sizeof(msg), 0);

            }
            if(FD_ISSET(msgidw,&rfds))
            {
                while(msgrcv(msgidw, &msg, sizeof(msg), msg.type, 0))
                printf("%s\n",msg.text);
            }
        }
    }
    
}