#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sstream>

using namespace std;

int deltaAleatorio(int i, int f){
  srand((unsigned)time(0));
  int maior = i;
  int menor = f;
  return rand()%(maior-menor+1) + menor;
}

bool primo(int i){
  int cpy = i-1;
  for(int c = 2; c<i; c++){
    if(i%c==0){
      cout<<i<<" não é primo"<<endl;
      return false;
    }
  }
  cout<<i<<" é primo"<<endl;
  return true;
}

void pipe_ipc(){
  int pipefd[2];
  pid_t pid;
  int n = 1;
  int rec;

  if (pipe(pipefd)==-1){
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  pid=fork();

  if(pid==-1){
    perror("fork");
    exit(EXIT_FAILURE);
  }

  if (pid == 0){
    do{
      read(pipefd[0], (char *)&rec, sizeof(rec));
      if(rec!=0){
        primo(rec);
      }
    }while(!rec==0);
    if(rec==0){
      close(pipefd[1]);
      exit(EXIT_SUCCESS);
    }
  }
  else{
    int count = 0;
    int delta = deltaAleatorio(1, 100);
    do{
      n = 1+delta*count;
      if(count==1000){n = 0;};
      write(pipefd[1], (char *)&n, sizeof(n));
      count++;
    }while(!n==0);
    if(n==0){
      close(pipefd[0]);
      exit(EXIT_SUCCESS);
    }
  }
}


int main(){
  pipe_ipc();
  return 0;
}
