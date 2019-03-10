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
    printf("%d\n",key);
    // msgget creates a message queue 
    // and returns identifier 
    msgid = msgget(key, 0666 | IPC_CREAT); 

    while(1){
  
    // msgrcv to receive message 
    msgrcv(msgid, &msg, sizeof(msg), 1, 0); 
  
    // display the message 
    printf("Data Received is : %s \n",  
                    msg.text); }
  
    // to destroy the message queue 
    msgctl(msgid, IPC_RMID, NULL); 
  
    return 0; 
} 