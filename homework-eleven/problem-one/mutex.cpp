#include <iostream>
#include <vector>
#include <pthread.h>
#include <ctime>
#include <chrono>

class Number
{

public:
    int x = 0;
    pthread_mutex_t* mutex;

    Number()
    {
        mutex = new pthread_mutex_t();
        pthread_mutex_init(mutex, nullptr);
    }

    ~Number()
    {
        pthread_mutex_destroy(mutex);
        delete mutex;
    }
};

void* example(void* arg)
{
    Number* num = (Number*)arg;

    // lock
    pthread_mutex_lock(num->mutex);
    for (int i = 0; i < 10000; ++i)
    {
        num->x++;
    }
    // unlock
    pthread_mutex_unlock(num->mutex);
    return nullptr;
}

int main(int argc, char** argv)
{
    double res = 0;
    for(int i = 0; i < 100; ++i)
    {
        Number *num = new Number();
        num->x = 2;
        std::vector <pthread_t> tids(20);

        auto start_time = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < 20; ++i) {
            pthread_create(&tids[i], NULL, example, (void *) num);
        }

        for (int i = 0; i < 20; ++i) {
            pthread_join(tids[i], NULL);
        }

        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_time = end_time - start_time;


        //std::cout << num->x << std::endl;

        std::cout << i << ": Elapsed time: " << elapsed_time.count() << " seconds" << std::endl;
        delete num;
        res+=elapsed_time.count();
    }
    std::cout<<std::endl<<"Average time: "<<res/100<<std::endl;
    return 0;
}
