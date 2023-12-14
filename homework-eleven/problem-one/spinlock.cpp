#include <iostream>  
#include <vector>  
#include <pthread.h>  
#include <ctime>  
#include <chrono>  
  
class Number  
{  
public:  
    pthread_spinlock_t* spinlock;  
	      
    int x = 0;  
			  
    Number()  
    {  
        spinlock = new pthread_spinlock_t();  
        pthread_spin_init(spinlock, PTHREAD_PROCESS_PRIVATE);  
    }  
			      
    ~Number()  
    {  
        pthread_spin_destroy(spinlock);  
        delete spinlock;  
    }  
};  
  
void* example(void* arg)  
{  
    Number* num = (Number*)arg;  

    pthread_spin_lock(num->spinlock);  
    for (int i = 0; i < 10000; ++i)  
    {  
        num->x++;  
    }  
    pthread_spin_unlock(num->spinlock);  

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
								      
        for (int i = 0; i < 20; ++i)
       	{  
            pthread_create(&tids[i], NULL, example, (void *) num);  
        }  
									      
        for (int i = 0; i < 20; ++i)
       	{  
            pthread_join(tids[i], NULL);  
        }  
										      
        auto end_time = std::chrono::high_resolution_clock::now();  
        std::chrono::duration<double> elapsed_time = end_time - start_time;  
												      
												      

												      
        std::cout << i << ": Elapsed time: " << elapsed_time.count() << " seconds" << std::endl;  
        delete num;  
        res+=elapsed_time.count();  
   }  
   std::cout<<std::endl<<"Average time: "<<res/10<<std::endl;  
   return 0;  
}
