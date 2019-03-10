#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/msg.h>
#include<sys/types.h>
struct mesg_buffer { 
    long type; 
    char text[100]; 
} msg; 
  
int main() 
{ 
    key_t key; 
    int msgid; 
  
    // ftok to generate unique key 
    key = ftok("progfile", 65); 
  	printf("%d\n",key );
    // msgget creates a message queue 
    // and returns identifier 
    msgid = msgget(key, 0666 | IPC_CREAT); 
    msg.type = 1; 
  while(1){
    printf("Write Data : "); 
    gets(msg.text); 
  
    // msgsnd to send message 
    msgsnd(msgid, &msg, sizeof(msg), 0); 
    msgsnd(msgid, &msg, sizeof(msg), 0); 
  
    // display the message 
    printf("Data send is : %s \n", msg.text); }
  
    return 0; 
} 