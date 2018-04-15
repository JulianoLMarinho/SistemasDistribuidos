#include <iostream>
#include <atomic>
#include <random>
#include <thread>
#include <numeric>

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

void Soma(long int &soma, vector<char> &vetorParcial, Spinlock &spinlock, int begin, int end){
    long int temp = 0;
    for(int i = begin; i< end; i++){
        temp += (int)vetorParcial[i];
    }
    spinlock.acquire();
    soma += temp;
    spinlock.release();
}

void test(long int &soma, int &k, Spinlock &spinlock){
    spinlock.acquire();
        soma++;
    spinlock.release();
}

int main(int argc, char *argv[]) {
    Spinlock spinlock;
    long int somas = 0;
    long int somaTeste = 0;
    int j = 0;
    spinlock.acquire();
    int N = atoi(argv[1]);
    int K = atoi(argv[2]);
    spinlock.release();

    long int Nu[3] = {10000000, 100000000, 1000000000};
    int Ku[9] = {1, 2, 4, 8, 16, 32, 64, 128, 256};

    vector<char> vetor(N);
    vector<thread> threads;
    generateRandomVector(N, vetor);

    vector<vector<char>>temp;

    for(int i = 0; i<N; i += N/K){
        threads.emplace_back(Soma, ref(somas), ref(vetor), ref(spinlock), i, i+N/K);
    }

    for(int i = 0; i < N; i++){
        somaTeste+=vetor[i];
    }



    for (thread & t : threads) {
        t.join();
    }

    cout<<somas<<endl;
    cout<<somaTeste<<endl;


    return 0;
}