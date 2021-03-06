#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "lib/commandlinereader.h"
#include "lib/vector.h"

typedef struct arrayPid{
  int pidChild;
  int estado;
}structPid;

int main(int argc, char** argv){
  int i=0;
  int j;
  int estado;
  int maxchildren=1;
  int vectorSize = 10;
  char *argVector[vectorSize];
  int bufferSize = 150;
  char buffer[bufferSize];

  vector_t* arrayPid = vector_alloc(vectorSize);


  while(1){
    readLineArguments(argVector, vectorSize, buffer, bufferSize);

    if(strcmp(argVector[0], "run")==0){
      pid_t pid = fork();
      int argm=atoi(argv[1]);
      if(pid<0){
        perror("Erro ao criar a Fork()\n");
        exit(-1);
      }
      else if(pid == 0){
        execl("CircuitRouter-SeqSolver", "CircuitRouter-SeqSolver", argVector[1], (char *)0);
      }
      else{
        structPid *newChild = malloc(sizeof(structPid));
        newChild->pidChild = pid;
        printf("antes: %d\n", maxchildren);
        maxchildren++;
        printf("depois: %d\n", maxchildren);
        vector_pushBack(arrayPid, newChild);
        i++;
        if(maxchildren>argm){
            wait(&estado);
            newChild->estado = estado;
            maxchildren--;
        }
      }
    }
    else if(strcmp(argVector[0], "exit")==0){
      wait(&estado);
      for (j = 0; j < i; j++) {
        structPid *auxChild = malloc(sizeof(structPid));
        auxChild = vector_at(arrayPid, j);
        if(WIFEXITED(auxChild->estado)){
          if(WEXITSTATUS(auxChild->estado)==0){
            printf("CHILD EXITED (PID=%d; return OK)\n", auxChild->pidChild);
          }
          else{
            printf("CHILD EXITED (PID=%d; return NOK)\n", auxChild->pidChild);
          }
        }
        else{
            printf("CHILD EXITED (PID=%d; return NOK (KILLED))\n", auxChild->pidChild);
        }
      }
      printf("END.\n");
      vector_free(arrayPid);
      exit(0);
    }
    else{
      printf("Invalid comand\n");
    }
  }
  return 0;
}
