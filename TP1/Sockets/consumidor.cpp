#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

string primo(int i){
  string temp;
  int cpy = i-1;
  for(int c = 2; c<i; c++){
    if(i%c==0){
      temp = to_string(i)+" não é primo";
      return temp;
    }
  }

  temp = to_string(i)+" é primo";
  return temp;
  // return true;
}

int main(){
  int socket_desc, new_socket, c;
  struct sockaddr_in server, client;
  string message;
  int client_reply;

  socket_desc = socket(AF_INET, SOCK_STREAM, 0);
  if(socket_desc == -1){
    cout<<"Não foi possível criar o socket"<<endl;
  }

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(8888);

  //bind
  if(bind(socket_desc, (struct sockaddr*)&server, sizeof(server)) < 0){
    cout<<"Falha na conexão"<<endl;
  }
  // cout<<"Sucesso"<<endl;

  //listen
  listen(socket_desc, 3);

  cout<<"Aguardando produtor..."<<endl;
  c=sizeof(struct sockaddr_in);
  new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
  if(new_socket<0){
    cout<<"Falha na conexão"<<endl;
  }else{
    do{
      if(read(new_socket, (char *)&client_reply, sizeof(client_reply))<0){
        cout<<"Não houve mensagem"<<endl;
      }
      message = primo(client_reply);
      write(new_socket, message.c_str(), 30);
    }while(client_reply>0);
  }

  cout<<"Consumidor encerrado"<<endl;

  return 0;
}
