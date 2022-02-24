#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "Sharedstruct.h"



#define BUFFSIZE 5


void* consumer(char buffer[], int cindex){

  
    int fd = shm_open("sharedmemory", O_RDWR, S_IRUSR | S_IWUSR);
    shared* sharedstruct = mmap(NULL, sizeof(shared), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    printf("From Consumer\n");


  while(1){

    printf("%c\n", sharedstruct->buffer[cindex]);
    sharedstruct->cindex = (sharedstruct->cindex + 1) % BUFFSIZE;
    
  }
  
}