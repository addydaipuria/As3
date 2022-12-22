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

void stringgenerate(char arr_rand[][8]);

struct buff {
    long type;
    char str[100];
} msg;

int main() {
    char arr_rand[50][8] = {{0}};
    key_t jesse;
    jesse=ftok("prog",0);
    int walter;
  
    int index = 1;
    stringgenerate(arr_rand);
    
  msg.type=1;
  int i=index;
  while(1){
    for(int i;i<index+5;i++){
      walter=msgget(jesse,0666 | IPC_CREAT);
      strncpy(msg.str,arr_rand[i],sizeof(arr_rand[i]));
      msgsnd(walter, &msg,sizeof(msg),0);
      sleep(1);
      msgctl(walter,IPC_RMID,NULL);
    }
     walter = msgget(jesse, 0666 | IPC_CREAT);
     msgrcv(walter, &msg, sizeof(msg), 1, 0);
     msgctl(walter, IPC_RMID, NULL);
     msg.str[sizeof(msg.str) - 1] = 0;
        
     int index1 = atoi(msg.str);
 		 printf("HIGHEST ID = %s\n\n", msg.str);
     index = index + 1;
     if(index >= 50) {
        msgctl(walter, IPC_RMID, NULL);
        break;
      }
  }
}

void stringgenerate(char arr_rand[][8]) {        
    srand (time(NULL));                            
    for (int j = 0; j <50; j++) {
        arr_rand[j][0] = j;
    }
    for(int i = 0; i <50; i++) {
      for(int j=0;j<=5;j++){
        arr_rand[i][j]=rand() % 26 + 65;
        
      }
    }  
}
