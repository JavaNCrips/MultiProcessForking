#include "Sharedstruct.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <fcntl.h>


int main(int argc, char* argv[]){
    char text[] = "New Text!";


  int fd = shm_open("sharedmemory", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
  ftruncate(fd, sizeof(shared));
  shared* sharedstruct = mmap(NULL, sizeof(shared), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);


  sharedstruct->pindex = 0;
  sharedstruct->cindex = 0;

//char buffer[BUFFSIZE] = shm_open("prodconshare", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
int status;

int nprod = atoi(argv[1]);
int ncons = atoi(argv[2]);


  sharedstruct->pid = fork();


  if(sharedstruct->pid == 0){
  for (int i = 0; i < nprod; i++){

    //int fd = shm_open("sharedmemory", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    //shared* sharedstruct = mmap(NULL, sizeof(shared), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    printf("process ID: %d\n", sharedstruct->pid);
    printf("Var: %c\n",  sharedstruct->buffer[0]);
    execlp("./producer", sharedstruct->buffer , sharedstruct->pindex);
   
    
   
  }
  }else{
    //sharedstruct->pid = fork();
    printf("The Id is: %d\n", sharedstruct->pid);

    printf("Var: %c\n",  sharedstruct->buffer[0]);
    //for(int j=0; j < 12; j++){
    
    //}

    //producer(sharedstruct->buffer, text, sharedstruct->pindex);
    waitpid(sharedstruct->pid, 0 ,0);
   
  }

  if(sharedstruct->pid == 0){
  for (int i = 0; i < ncons; i++){


    //int fd = shm_open("sharedmemory", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    //shared* sharedstruct = mmap(NULL, sizeof(shared), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    printf("Var: %c\n",  sharedstruct->buffer[2]);
    printf("process ID: %d\n", sharedstruct->pid);
    execlp("./consumer", sharedstruct->buffer,  sharedstruct->cindex);
   
   
   
    
  }
  }else{
  sharedstruct->pid = fork();
   printf("The Id is: %d\n", sharedstruct->pid);
   
   waitpid(sharedstruct->pid, 0, 0);
    

  }

  
  return 0;
}
