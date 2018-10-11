#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "lib/commandlinereader.h"

#define MAXCHILDREN 10

int main(int argc, char** argv){
  int i=0;
  int j;
  int estado;
  int *arrayPid;
  int vectorSize = 10;
  char *argVector[vectorSize];
  int bufferSize = 150;
  char buffer[bufferSize];

  arrayPid = (int *)malloc(sizeof(int)*10);

  while(1){
    readLineArguments(argVector, vectorSize, buffer, bufferSize);

    if(strcmp(argVector[0], "run")==0){
      pid_t pid = fork();

      if(pid<0){
        perror("Erro ao criar a Fork()\n");
        exit(-1);
      }
      else if(pid == 0){
        execl("CircuitRouter-SeqSolver", "CircuitRouter-SeqSolver", argVector[1], (char *)0);
      }
      else{
        arrayPid[i]= pid;
        i++;
        wait(&estado);
      }
    }
    else if(strcmp(argVector[0], "exit")==0){
      wait(&estado);
      for (j = 0; j < i; j++) {
        printf("CHILD EXITED (PID=%d; return )\n", arrayPid[j]);
      }
      printf("END.\n");
      exit(0);
    }
    else{
      printf("Invalid comand\n");
    }
  }
  return 0;
}
