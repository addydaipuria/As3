#include<stdio.h>
#include<pthread.h>
#include<time.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>
#include<sys/un.h>
#define BUFFER_SIZE 100

void stringgenerate(char arr_rand[][8]);
int main() {
    char * fifo_1 = "FIFO_1";
    char * fifo_2 = "FIFO_2";
    mkfifo(fifo_1, 0666);
    mkfifo(fifo_2, 0666);
    char arr_rand[50][8] = {{0}};
    char meth[BUFFER_SIZE];
    int file1, file2,ret;
    int index = 1;
    stringgenerate(arr_rand);
    
	while(1) {
		if(file1 == -1) {
			perror("FIFO 1 access error");
		}

		printf("Strings sent from %d to %d\n", index, index + 4);
		
		for(int i = index; i < index + 5; i++) {
			file1 = open(fifo_1, O_WRONLY);
			ret = write(file1, arr_rand[i], sizeof(arr_rand[i]) + 1);
			sleep(1);	
			close(file1);
		}
		file2 = open(fifo_2, O_RDONLY);
		ret = read(file2, meth, sizeof(meth));
		close(file2);

		if(ret == -1) {
			perror("read");
			exit(EXIT_FAILURE);
		}

		int index1 = atoi(meth);
 		printf("Highest ID  = %s\n\n", meth);
		index = index1 + 1;
		if(index >= 50){
      exit(EXIT_SUCCESS);
      }
	}

    return 0;
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
