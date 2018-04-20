#include <iostream>
#include <atomic>
#include <random>
#include <thread>
#include <chrono>
#include <fstream>


using namespace std;



class Spinlock{
    atomic_flag lock = ATOMIC_FLAG_INIT;

public:
    void acquire(){
        while(lock.test_and_set()){}
    }
    void release(){
        lock.clear();
    }
};

void generateRandomVector(int N, vector<char> &vetor){
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(-100,100);
    for(int i = 0; i < N; i++){
        vetor[i] = char(dist(mt));
    }
}

void Soma(long int &soma, vector<char> &vetor, Spinlock &spinlock, int begin, int end){
    long int temp = 0;
    for(int i = begin; i< end; i++){
        temp += (int)vetor[i];
    }
    spinlock.acquire();
    soma += temp;
    spinlock.release();
}

int main(int argc, char *argv[]) {

    Spinlock spinlock;

    if(argc!=3){
        cout<<"Você precisa inserir o tamanho do vetor e a quantidade de threads."<<endl;
        _Exit(1);
    }

    unsigned int N = static_cast<unsigned int>(atoi(argv[1]));
    int K = atoi(argv[2]);

    vector<char> vetor(N);
    generateRandomVector(N, vetor);

    long int somas = 0;

    vector<thread> threads;

    double NK = N*1.0/K;

    auto ll = static_cast<int>(N - (floor(NK) * K));

    auto beginT = chrono::system_clock::now();
    for(int k = 0; k<N; k += NK){
        auto end = static_cast<int>(k + NK);
        if(k+ll == N){
            end = N;
        }
        threads.emplace_back(Soma, ref(somas), ref(vetor), ref(spinlock), k, end);
    }

    for (thread & t : threads) {
        t.join();
    }
    auto endT = chrono::system_clock::now();

    double timeThread = chrono::duration<double, std::milli>(endT- beginT).count();
    cout<<"N: "<<N<<", K: "<<K<<", Tempo: "<<timeThread<<"ms, Soma: "<<somas<<endl;


    return 0;
}