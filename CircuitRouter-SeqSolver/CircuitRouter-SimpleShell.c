#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "lib/comandlinereader.h"


int main(int argc, char** argv){

  int pid, estado;
  int vectorSize = 10;
  char **argVector[vectorSize];
  int bufferSize = 150;
  char *buffer[bufferSize];

  int numArgs = readLineArguments(argVector, vectorSize, buffer, bufferSize);


  pid = fork();

  if(pid == 0){
    printf("sou o Filho!\n");
    exit(0);
  }
  else{
    pid = wait(&estado);
  }

}
