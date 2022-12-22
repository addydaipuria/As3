#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>

struct buff {
    long type;
    char str[100];
} msg;
  

int main() {
    key_t jesse;
    jesse = ftok("prog", 0);

    int walter,index=0,index1=0;
    while(1) {
        while(index1 < index + 5) {
            walter = msgget(jesse, 0666 | IPC_CREAT);
            msgrcv(walter, &msg, sizeof(msg), 1, 0);
			      sleep(1);
            msgctl(walter, IPC_RMID, NULL);
            msg.str[sizeof(msg.str) - 1] = 0;
            index1 = msg.str[0];
			      printf("String: ");		
            for(int i = 1; i < 12; i++) {
				      printf("%c", msg.str[i]);
			      }
            printf("\n");
			      sprintf(msg.str, "%d", index1);
      			printf("ID of String = %s\n", msg.str);	
        }
        index = index1;
        walter = msgget(jesse, 0666 | IPC_CREAT);
        msgsnd(walter, &msg, sizeof(msg), 0);
        msgctl(walter, IPC_RMID, NULL);
        if(index >= 50) break;
      }
    msgctl(walter, IPC_RMID, NULL);
    return 0;
}