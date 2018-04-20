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


    ofstream file;
    file.open("saida.csv");
    file<<"N, {Np Nc}, Tempo"<<endl;


    int combinacao[9][2]={{1,1},{1,2},{1,4},{1,8},{1,16},{2,1},{4,1},{8,1},{16,1}};
    unsigned int N[3] = {2,8,32};

    for (unsigned int Ns: N){
        for(int *comb: combinacao){
            double totalTime = 0;
            for(int tempos = 0; tempos < 10; tempos++) {

                sem_init(&mutex, 0, 1);
                sem_init(&empty, 0, Ns);
                sem_init(&full, 0, 0);

                buffer.resize(Ns);

                int total = 0;

                fill(buffer.begin(), buffer.end(), 0);

                vector<thread> threads;
                for (int p = 0; p < comb[0]; p++) {
                    threads.emplace_back(produzir, ref(total));
                }
                for (int c = 0; c < comb[1]; c++) {
                    threads.emplace_back(consumir, ref(total));
                }

                auto begin = chrono::system_clock::now();

                for (thread &t : threads) {
                    t.join();
                }

                auto end = chrono::system_clock::now();
                double timeThread = chrono::duration<double, std::milli>(end- begin).count();
                totalTime+=timeThread;
            }
            cout<<"N: "<<Ns<<", Cmb: {"<<comb[0]<<","<<comb[1]<<"}, tempo: "<<totalTime/10.0<<endl;
            file<<Ns<<",{"<<comb[0]<<" "<<comb[1]<<"},"<<totalTime/10.0<<endl;
        }
    }

    file.close();



    return 0;
}