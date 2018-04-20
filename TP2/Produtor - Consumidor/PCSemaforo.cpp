#include <iostream>
#include <vector>
#include <semaphore.h>
#include <random>
#include <thread>
#include <fstream>

using namespace std;

sem_t mutex;
sem_t empty;
sem_t full;
vector<int>buffer;
int TOTAL = 100000;

void primo(int i){
    string temp;
    int irec = i;
    int cpy = i-1;
    for(int c = 2; c<irec; c++){
        if(irec%c==0){
            cout<<to_string(i)+" não é primo"<<endl;
            //return temp;
        }
    }

    cout<<to_string(i)+" é primo"<<endl;
    // return true;
}

void produzir(int &total){
    while(true){

        random_device rd;
        mt19937 mt(rd());
        uniform_int_distribution<int> dist(1,10000000);
        int produce = dist(mt);

        sem_wait(&empty);
        sem_wait(&mutex);

        if(total >= TOTAL){
            sem_post(&empty);
            sem_post(&mutex);
            sem_post(&full);
            break;
        }

        for (int &numero : buffer) {
            if(numero == 0){
                numero = produce;
                break;
            }
        }

        sem_post(&mutex);
        sem_post(&full);


    }
}

void consumir(int &total){
    while(true){
        sem_wait(&full);
        sem_wait(&mutex);

        if(total >= TOTAL){
            sem_post(&full);
            sem_post(&mutex);
            sem_post(&empty);
            break;
        }


        for (int &numero : buffer){
            if(numero != 0){
                int cpnumero = numero;
                numero = 0;
//                primo(cpnumero);
                break;
            }
        }

        total++;
        sem_post(&mutex);
        sem_post(&empty);


    }
}

int main(int argc, char *argv[]) {

    if(argc!=4){
        cout<<"Você precisa colocar o tamanho no buffer, quantidade de produtores e quantidade de consumidores!"<<endl;
        _Exit(1);
    }

    int N = atoi(argv[1]);
    int Np = atoi(argv[2]);
    int Nc = atoi(argv[3]);



    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, static_cast<unsigned int>(N));
    sem_init(&full, 0, 0);

    buffer.resize(static_cast<unsigned long>(N));

    int total = 0;

    fill(buffer.begin(), buffer.end(), 0);
    double totalTime = 0;

    vector<thread> threads;
    auto begin = chrono::system_clock::now();
    for (int p = 0; p < Np; p++) {
        threads.emplace_back(produzir, ref(total));
    }
    for (int c = 0; c < Nc; c++) {
        threads.emplace_back(consumir, ref(total));
    }



    for (thread &t : threads) {
        t.join();
    }

    auto end = chrono::system_clock::now();
    double timeThread = chrono::duration<double, std::milli>(end- begin).count();


    cout<<"N: "<<N<<", Cmb: {"<<Np<<","<<Nc<<"}, tempo: "<<timeThread<<endl;




    return 0;
}