/*
Brandon Hudson
01/27/22
CS514-HW1
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "Sharedstruct.h"

#define BUFFSIZE 5

int main(){

  char text[] = "Hello World!";

  int fd = shm_open("sharedmem", O_RDWR, S_IRUSR | S_IWUSR);
  shared* sharedstruct = mmap(NULL, sizeof(shared), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  printf("From Producer\n");

  int i = 0;
  while(i < 12){

    sem_wait(&sharedstruct->empty);
    sem_wait(&sharedstruct->mutex);   

    sharedstruct->buffer[sharedstruct->pindex] = text[i];
    sharedstruct->pindex = (sharedstruct->pindex + 1) % BUFFSIZE;
  
    sem_post(&sharedstruct->mutex); 
    sem_post(&sharedstruct->full); 

    //buffer[i] = text[i];
    //pindex = (pindex + 1) % BUFFSIZE;

    i++;

  }

  return 1;
}

