#include <iostream>
#include <string.h>
// #include <sys/types.h>
#include <sys/socket.h>
// #include <netinet/in.h>
#include <arpa/inet.h>
// #include <stdlib.h>
#include <unistd.h>

using namespace std;

int deltaAleatorio(int i, int f){
  srand((unsigned)time(0));
  int maior = f;
  int menor = i;
  return rand()%(maior-menor+1) + menor;
}



int main(int argc, char *argv[]){
  int socket_desc;
  struct sockaddr_in server;
  socket_desc = socket(AF_INET, SOCK_STREAM, 0);
  string message;
  char *server_reply;
  //retorna um descritor que poderá ser usado em qualquer outra função com os parâmetros: Adress Family, Type e protocolo
  //O tipo SOCK_STREAM indica que a conexão será TCP
  if(socket_desc==-1){
    cout<<"Could not create socket"<<endl;
  }


  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  server.sin_family = AF_INET;
  server.sin_port = htons(8888);

  if(connect(socket_desc, (struct sockaddr *)&server, sizeof(server))<0){
    cout<<"Erro na conexão"<<endl;
    return 1;
  }
  cout<<"Conectado"<<endl;

  int count = 0;
  int n;
  int delta = deltaAleatorio(1, 100);
  int interacoes = atoi(argv[1]);
  do{
    n = 1 + delta*count;
    message=to_string(n);
    if(count==interacoes){n = 0;};
    if(write(socket_desc, (char *)&n, sizeof(n)) < 0){
      cout<<"Falha no envio da mensagem"<<endl;
      return 1;
    }
    if(read(socket_desc, server_reply, 30)<0){
      cout<<"Erro na resposta"<<endl;
    }
    if(n>0){cout<<server_reply<<endl;}
    count++;
  }while(n>0);

  cout<<"Produtor encerrado"<<endl;

  close(socket_desc);
  return 0;
}
