#include <iostream>
#include <signal.h>
#include <zconf.h>

using namespace std;

static volatile sig_atomic_t sig_caught = 0;

class SignalHandler{
public:
    SignalHandler(int type){
        signal(1, handler);
        signal(2, handler);
        signal(4, handler);
        cout << "Porta número: "<<getpid() << endl;
        if(type==1){
			cout<<"Busy wait"<<endl;
            while(1){
                if(sig_caught){
                    sig_caught=0;
                    break;
                }
            }
        } else if(type==2){
			cout<<"Bloking wait"<<endl;
            while(1){
                pause();
                if(sig_caught){
                    sig_caught=0;
                    break;
                }
            }

        }
    }
    static void handler(int signal){
        if(signal==1){
            cout<<"O Sinal foi 1"<<endl;
        }else if(signal==2){
            cout<<"O Sinal foi 2"<<endl;
        }else if(signal==4){
            sig_caught = 1;
            cout<<"Sair"<<endl;
        }
    }
};

int main(int argc, char *argv[]) {
    SignalHandler sig(atoi(argv[1]));
    return 0;
}
