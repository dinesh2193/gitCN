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
struct process{
    long pid;
    char grp[3];
};
int check(struct process proc[],int pc,long pid)
{
    for(int i=0;i<pc;i++)
    {
        if(proc[i].pid==pid)
            return i;
    }
    return -1;
}
int main()
{
	key_t keyr,keyw; 
	int msgidr,msgidw;
	struct process proc[10];
    int pc=0;
	keyr = ftok("uni_read1", 65);
    keyw = ftok("uni_write1", 65);

    msgidr = msgget(keyr, 0666 | IPC_CREAT);
    msgidw = msgget(keyw, 0666 | IPC_CREAT);

    printf("%d\n",keyr);
    printf("%d\n",keyw);

    while(1)
    {
    	msgrcv(msgidr,&msg,sizeof(msg),0,0);
        
        int flag = check(proc,pc,msg.type);
       // printf("%d\n",flag);
       // printf("%ld\n",msg.type);
    	 if(flag == -1)
        {
           // printf("%d\n",msg.type);
            strcpy(proc[pc].grp,msg.text);
            proc[pc++].pid=msg.type;
           // printf("%s\n",msg.text);
        }
        else
        {
            for(int i=0;i<pc;i++)
            {
                int idx = check(proc,pc,msg.type);
               // printf("%d\n",idx);
                if(proc[i].pid!=msg.type&&strcmp(proc[i].grp,proc[idx].grp)==0)
                {
                    struct mesg_buffer smsg;
                    smsg.type = proc[i].pid;
                    strcpy(smsg.text,msg.text);
                    msgsnd(msgidw,&smsg,sizeof(smsg),0);
                    kill(smsg.type,SIGUSR1);
                }
            }
        }
    }
}