#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

using namespace std;


int main(){
  int socket_desc;
  struct sockaddr_in server;
  socket_desc = socket(AF_INET, SOCK_STREAM, 0);
  const char *message;
  char server_reply[2000];
  //retorna um descritor que poderá ser usado em qualquer outra função com os parâmetros: Adress Family, Type e protocolo
  //O tipo SOCK_STREAM indica que a conexão será TCP
  if(socket_desc==-1){
    cout<<"Coul not create socket"<<endl;
  }


  server.sin_addr.s_addr = inet_addr("172.217.29.110");
  server.sin_family = AF_INET;
  server.sin_port = htons(80);

  if(connect(socket_desc, (struct sockaddr *)&server, sizeof(server))<0){
    cout<<"Erro na conexão"<<endl;
    return 1;
  }
  cout<<"Conectado"<<endl;

  message = "GET / HTTP/1.1\r\n\r\n";
  if(send(socket_desc, message, strlen(message), 0) < 0){
    cout<<"Falha no envio da mensagem"<<endl;
    return 1;
  }
  cout<<"Mensagem Enviada"<<endl;

  if(read(socket_desc, server_reply, 2000)<0){
    cout<<"Erro na resposta"<<endl;
  }
  cout<<"Resposta recebida"<<endl;
  cout<<server_reply<<endl;

  close(socket_desc);
  return 0;
}
