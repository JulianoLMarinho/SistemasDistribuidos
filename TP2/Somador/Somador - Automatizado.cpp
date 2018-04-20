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

    ofstream file;
    file.open("saida.csv");
    file<<"N, k, Tempo"<<endl;
    cout<<"montei"<<endl;
    clock_t beginV, endV;
    Spinlock spinlock;


    vector<char> vetor(1000000000);
    generateRandomVector(1000000000, vetor);


    long int Nu[3] = {10000000, 100000000, 1000000000};
    int Ku[9] = {1, 2, 4, 8, 16, 32, 64, 128, 256};
    for(int i = 0; i<3; i++){
        for(int j = 0; j<9; j++){
            double totalTime = 0.0;
            for(int z = 0; z<10; z++){
                long int somas = 0;

                vector<thread> threads;

                double NK = Nu[i]*1.0/Ku[j];

                auto ll = static_cast<int>(Nu[i] - (floor(NK) * Ku[j]));

                auto begin = chrono::system_clock::now();
                for(long int k = 0; k<Nu[i]; k += NK){
                    auto end = static_cast<int>(k + NK);
                    if(k+ll == Nu[i]){
                        end = static_cast<int>(Nu[i]);
                    }
                    threads.emplace_back(Soma, ref(somas), ref(vetor), ref(spinlock), k, end);
                }

                for (thread & t : threads) {
                    t.join();
                }
                auto end = chrono::system_clock::now();

                double timeThread = chrono::duration<double, std::milli>(end- begin).count();
                totalTime+=timeThread;
            }

            cout<<"N: "<<Nu[i]<<", K: "<<Ku[j]<<", Time Thread: "<<totalTime/10.0<<"ms"<<endl;
            file<<Nu[i]<<","<<Ku[j]<<","<<totalTime/10.0<<endl;
        }


    }

    file.close();


    return 0;
}