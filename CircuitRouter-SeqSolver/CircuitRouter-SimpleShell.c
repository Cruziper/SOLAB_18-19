#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "lib/commandlinereader.h"


int main(int argc, char** argv){

  int estado;
  int vectorSize = 10;
  char *argVector[vectorSize];
  int bufferSize = 150;
  char buffer[bufferSize];

  while(1){
    readLineArguments(argVector, vectorSize, buffer, bufferSize);

    if(strcmp(argVector[0], "run")==0){
      pid_t pid = fork();

      if(pid<0){
        perror("Erro ao criar a Fork()\n");
        exit(-1);
      }
      if(pid == 0){
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
