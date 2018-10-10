#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "lib/commandlinereader.h"

#define MAXCHILDREN 10

int main(int argc, char** argv){
  int i=0;
  int estado;
  int *arrayPid;
  int vectorSize = 10;
  char *argVector[vectorSize];
  int bufferSize = 150;
  char buffer[bufferSize];
  printf("antes: %d\n", i);

  arrayPid = (int *)malloc(sizeof(int)*10);

  while(1){
    readLineArguments(argVector, vectorSize, buffer, bufferSize);

    if(strcmp(argVector[0], "run")==0){
      pid_t pid = fork();

      if(pid<0){
        perror("Erro ao criar a Fork()\n");
        exit(-1);
      }
      if(pid == 0){
        arrayPid[i] = getpid();
        printf("arrayPid[%d]= %d\n", i, arrayPid[i]);
        i++;
        printf("depois: %d\n", i);
        execl("CircuitRouter-SeqSolver", "./CircuitRouter-SeqSolver", argVector[1], (char *)0);
      }
      else{
        wait(&estado);
      }
    }
    else if(strcmp(argVector[0], "exit")==0){
      //Mensagens de exit para cada processo
      exit(0);
    }
    else{
      printf("Invalid comand\n");
    }
  }
  return 0;
}
