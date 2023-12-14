#include <iostream>
#include <pthread.h>
#include <vector>
#include <cerrno>

class BankAccount
{
private:
    int balance;
    pthread_mutex_t* mutex;

public:
    BankAccount()
        :balance(0)
    {
        mutex = new pthread_mutex_t();
        pthread_mutex_init(mutex, nullptr);
    }

    ~BankAccount()
    {
        pthread_mutex_destroy(mutex);
        delete mutex;
    }

    void debit(int amount)
    {
        pthread_mutex_lock(mutex);
        balance -= amount;
        pthread_mutex_unlock(mutex);
    }

    void credit(int amount)
    {
        pthread_mutex_lock(mutex);
        balance += amount;
        pthread_mutex_unlock(mutex);
    }

    int getBalance() const
    {
        pthread_mutex_lock(mutex);
        int current = balance;
        pthread_mutex_unlock(mutex);
        return current;
    }
};

void* gorci_telov(void* params)
{
    BankAccount* account = static_cast<BankAccount*>(params);

    for(int i = 0; i < 1000; ++i)
    {
        account->credit(50);
        account->debit(30);
    }

    return nullptr;
}

int main()
{
    BankAccount account;
    std::vector<pthread_t> teler(20);

    for (int i = 0; i < 20; ++i)
    {
        if (pthread_create(&teler[i], nullptr, gorci_telov, &account) != 0)
        {
            std::perror("pthread_create");
            exit(errno);
        }
    }


    for (int i = 0; i < 20; ++i)
    {
        if (pthread_join(teler[i], nullptr) != 0)
        {
            std::perror("pthread_join");
            exit(errno);
        }
    }


    std::cout << "Final balance: " << account.getBalance() << std::endl;

    return 0;
}
