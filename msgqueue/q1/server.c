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
int main()
{
	key_t keyr,keyw; 
	int msgidr,msgidw;
	long proc[100],pc=0;
	keyr = ftok("uni_read", 65);
    keyw = ftok("uni_write", 65);

    msgidr = msgget(keyr, 0666 | IPC_CREAT);
    msgidw = msgget(keyw, 0666 | IPC_CREAT);

    while(1)
    {
    	msgrcv(msgidr,&msg,sizeof(msg),0,0);

    	if(strlen(msg.text)==0)
    	{
    		proc[pc++]=msg.type;
    	}
    	else
    	{
    		for(int i=0;i<pc;i++)
    		{
    			if(proc[i]!=msg.type)
    			{
    				struct mesg_buffer smsg;
    				smsg.type = proc[i];
    				strcpy(smsg.text,msg.text);
    				msgsnd(msgidw,&smsg,sizeof(smsg),0);
    				kill(smsg.type,SIGUSR1);
    			}
    		}
    	}
    }
}
