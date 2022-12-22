#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>
#include<sys/un.h>

int main() {
    char * fifo_1 = "FIFO_1";
    char * fifo_2 = "FIFO_2";
    mkfifo(fifo_1, 0666);
    mkfifo(fifo_2, 0666);
    char meth[5];
    int file1, file2,ret;

	  int index = 0;
    int i=index;
	while(1) {
		while(i < index + 5) {
			sleep(2);
			file1 = open(fifo_1, O_RDONLY);
			ret = read(file1, meth, sizeof(meth));
			close(file1);
			if(ret == -1) {	
				perror("couldn't read");
				exit(EXIT_FAILURE);
			}
			i = meth[0];
			printf("String: ");		
			
			for(int i = 1;i< 8; i++) {
				printf("%c", meth[i]);
			}
			printf("\n");
			
			sprintf(meth, "%d", i);
			printf("ID os String = %s\n", meth);	
		}
		index = i;
		file2 = open(fifo_2, O_WRONLY);
		ret = write(file2, meth, sizeof(meth));
		close(file2);
		if(index >= 50){
      exit(EXIT_SUCCESS);
      }
	}
    return 0;
}