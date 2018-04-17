#include <iostream>
#include <vector>
#include <semaphore.h>
#include <random>
#include <thread>

using namespace std;

sem_t mutex;
sem_t empty;
sem_t full;
vector<long int>numeros;
long int TOTAL = 1000;

string primo(long int i){
    string temp;
    long int cpy = i-1;
    for(long int c = 2; c<i; c++){
        if(i%c==0){
            temp = to_string(i)+" não é primo";
            return temp;
        }
    }

    temp = to_string(i)+" é primo";
    return temp;
    // return true;
}

void produzir(long int &total){
    while(true){

        random_device rd;
        mt19937 mt(rd());
        uniform_int_distribution<long int> dist(1,10000000);
        long int produce = dist(mt);

        sem_wait(&empty);
        sem_wait(&mutex);

        for (long &numero : numeros) {
            if(numero == 0){
                numero = produce;
                break;
            }
        }

        sem_post(&mutex);
        sem_post(&full);

        if(total>=TOTAL){
            break;
        }
    }
}

void consumir(long int &total){
    while(total<TOTAL){
        cout<<total<<endl;
        sem_wait(&full);
        sem_wait(&mutex);

        for (long &numero : numeros){
            if(numero != 0){
                long int cpnumero = numero;
                numero = 0;
//                cout<<primo(cpnumero)<<endl;
                break;
            }
        }
        total++;
        sem_post(&mutex);
        sem_post(&empty);

        if(total>=TOTAL){
            break;
        }
    }
}

int main(int argc, char *argv[]) {

    unsigned int N = 2;
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, N);
    sem_init(&full, 0, 0);
    numeros.resize(N);
    long int total = 0;
    fill(numeros.begin(), numeros.end(), 0);

    int combinacao[9][2]={{1,1},{1,2},{1,4},{1,8},{1,16},{2,1},{4,1},{8,1},{16,1}};

    vector<thread>threads;
        for(int p = 0; p<combinacao[0][0]; p++){
            threads.emplace_back(produzir, ref(total));
        }
        for(int c = 0; c<combinacao[4][1]; c++){
            threads.emplace_back(consumir, ref(total));
        }

    for(thread &t : threads){
        t.join();
    }

    cout<<total<<endl;
    return 0;
}