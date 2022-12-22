#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<time.h>
#include<semaphore.h>

sem_t jesse[5];
sem_t mutex;

void phileat(int hank){
  printf("Philosopher %d is eating\n",hank);
  sleep(2);  
}

void philthink(int hank){
  printf("Philosopher %d is thinking\n",hank);
  sleep(1);
}

void philstopeat(int hank){
  printf("Philosopher %d has stopped eating\n",hank);
}

void philpickfork1(int hank){
  printf("Philosopher %d picked current fork\n",hank);
}

void philpickfork2(int hank){
  printf("Philosopher %d picked next fork\n",hank);
}

void philputfork1(int hank){
  printf("Philosopher %d put current fork down\n",hank);
}

void philputfork2(int hank){
  printf("Philosopher %d put next fork down\n",hank);
}



void *saulgoodman(void * hank){
  int walter= *(int *)hank;
  while(1){
    if(walter==4){
      philthink(walter);
      sem_wait(&jesse[(walter+1)%5]);
      philpickfork2(walter);
      sem_wait(&jesse[walter]);
      philpickfork1(walter);
      phileat(walter);
      philstopeat(walter);
      sem_post(&jesse[walter]);
      philputfork1(walter);
      sem_post(&jesse[(walter+1)%5]);
      philputfork2(walter);
    }
    else{
      philthink(walter);
      sem_wait(&jesse[walter]);
      philpickfork2(walter);
      sem_wait(&jesse[(walter+1)%5]);
      philpickfork1(walter);
      phileat(walter);
      philstopeat(walter);
      sem_post(&jesse[(walter+1)%5]);
      philputfork1(walter);
      sem_post(&jesse[walter]);
      philputfork2(walter);     
    }
  }
}

int main()
{
  pthread_t meth[5];
  int i,arr[5];
  sem_init(&mutex, 0, 1);
  
	for(int i=0;i<5;i++){
		sem_init(&jesse[i],0,1);
	}
	
	for(int i=0;i<5;i++){
		arr[i] = i;
		pthread_create(&meth[i],NULL,saulgoodman,(void *)&arr[i]);
	}

	for(int i=0;i<5;i++){
		pthread_join(meth[i],NULL);
	}
}