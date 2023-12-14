#include <iostream>
#include <vector>
#include <pthread.h>
#include <ctime>
#include <chrono>
#include <semaphore.h>

class Number
{
public:
    sem_t* semaphore;

    int x = 0;

    Number()
    {
        semaphore = new sem_t();
        sem_init(semaphore, 0, 1);
    }

    ~Number()  
    {  
        sem_destroy(semaphore);  
        delete semaphore;  
    } 	
};

void* example(void* arg)
{
    Number* num = (Number*)arg;
    // lock
    sem_wait(num->semaphore);
    for (int i = 0; i < 10000; ++i)
    {
        num->x++;
    }
    sem_post(num->semaphore);
    // unlock
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


        std::cout << num->x << std::endl;

        std::cout << i << ": Elapsed time: " << elapsed_time.count() << " seconds" << std::endl;
        delete num;
        res+=elapsed_time.count();
    }
    std::cout<<std::endl<<"Average time: "<<res/100<<std::endl;
    return 0;
}
