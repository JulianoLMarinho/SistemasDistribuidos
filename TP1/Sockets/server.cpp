#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

class Server{
  int client, server;
  int portNumber;
  bool isExit;
  int bufferSize;
  char buffer[1024];

  struct sockaddr_in server_addr;
  socklen_t size;
public:
  Server(){
    this->portNumber = 1500;
    this->isExit = false;
    this->bufferSize = 1024;
    this->connectSocket();
    this->bindSocket();
    this->listeningCall();
    this->acceptingClients();
  }

  void connectSocket(){
    this->client = socket(AF_INET, SOCK_STREAM, 0);
    if(this->client<0){
      cout<<"\nErro ao estabelecer conexão"<<endl;
      exit(1);
    }
    cout<<"\nServidor criado..."<<endl;

    this->server_addr.sin_family = AF_INET;
    this->server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    this->server_addr.sin_port = htons(this->portNumber);
  }

  void bindSocket(){
    if((bind(this->client, (struct sockaddr*)&this->server_addr, sizeof(this->server_addr)))<0){
      cout<<"Erro"<<endl;
      //return -1;
    }

    this->size = sizeof(this->server_addr);
    cout<<"Esperando o cliente"<<endl;
  }

  void listeningCall(){
    listen(this->client, 1);
  }

  void acceptingClients(){
    int clientCount = 1;
    this->server = accept(this->client, (struct sockaddr *)&this->server_addr, &this->size);

    if(this->server<0){
      cout<<"Erro"<<endl;
    }

    while(this->server>0){
      strcpy(this->buffer, "=>Server Connected...\n");
      send(this->server, this->buffer, this->bufferSize, 0);
    }

    close(this->client);
  }
};

int main(){
  Server servidor;
  return 0;
}
