#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "../lib/commandlinereader.h"


int main(int argc, char** argv){

  int vectorSize = 10;
  char *argVector[vectorSize];
  int bufferSize = 150;
  char buffer[bufferSize];

  while(1){
    int numArgs = readLineArguments(argVector, vectorSize, buffer, bufferSize);
    printf("%s\n", argVector[0]);

    if(strcmp(argVector[0], "run")==0){
      pid_t pid = fork();

      if(pid<0){
        perror("Erro ao criar a Fork()\n");
        exit(-1);
      }
      if(pid == 0){
        execv("./CircuitRouter-SeqSolver.c", argVector[1]);
      }
      else{
        wait(NULL);
      }
    }
    if(strcmp(argVector[0], "exit")==0){
      //Mensagens de exit para cada processo
      exit(0);
    }
    else{
      printf("Invalid comand\n");
    }
  }
  return 0;
}
