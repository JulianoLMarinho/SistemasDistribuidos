#include <iostream>
#include <signal.h>

using namespace std;

void send(int signal, pid_t pid)
{
    if(!kill(pid, signal)){
        cout<<"\nSinal enviado para o processo "<<pid<<endl;
    }else{
        cout<<"\nO processo "<<pid<<" não existe!"<<endl;
    }
}

int main(int argc, char *argv[]) {
    send(atoi(argv[1]), atoi(argv[2]));
    return 0;
}
