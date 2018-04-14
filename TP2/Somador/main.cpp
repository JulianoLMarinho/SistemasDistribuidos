#include <iostream>
#include <atomic>

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

int main() {
    cout << "Hello, World!" << endl;
    return 0;
}