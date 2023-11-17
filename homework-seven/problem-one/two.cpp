#include <iostream>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <cerrno>

int sigusr2_count = 0;

void sigusr1_handler(int signum, siginfo_t* info, void* context)
{

}

void sigusr2_handler(int signum, siginfo_t* info, void* context)
{
    ++sigusr2_count;
}

void sigint_handler(int signum, siginfo_t* info, void* context)
{
    std::cout << "SIGUSR2 count "<< sigusr2_count <<std::endl;
    exit(EXIT_SUCCESS);
}

int main()
{
    std::cout<<getpid()<<std::endl;
    struct sigaction usr1 = {};

    usr1.sa_sigaction = sigusr1_handler;
    usr1.sa_handler = SIG_IGN;
    if(sigaction(SIGUSR1, &usr1, nullptr) == -1)
    {
        std::perror("sigaction");
        exit(errno);
    }

    struct sigaction usr2 = {};

    usr2.sa_sigaction = sigusr2_handler;
    if(sigaction(SIGUSR2, &usr2, nullptr) == -1)
    {
        std::perror("sigaction");
        exit(errno);
    }

    struct sigaction sint = {};

    sint.sa_sigaction = sigint_handler;
    if(sigaction(SIGINT, &sint, nullptr) == -1)
    {
        std::perror("sigaction");
        exit(errno);
    }


    while (true)
    {
        std::cout<<" I am still alive!!\n";
        sleep(5);
    }

    return 0;
}