#include <iostream>
#include <signal.h>
#include <zconf.h>

using namespace std;

static volatile sig_atomic_t sig_caught = 0;

void send(int signal, pid_t pid)
{
    if(!kill(pid, signal)){
        cout<<"Sinal enviado para o processo "<<pid<<endl;
    }else{
        cout<<"O processo "<<pid<<" não existe!"<<endl;
    }
}

int main(int argc, char *argv[]) {
	cout<<atoi(argv[1])<<endl;
	cout<<atoi(argv[2])<<endl;
    send(atoi(argv[1]), atoi(argv[2]));
    return 0;
}
