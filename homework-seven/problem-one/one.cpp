#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <signal.h>

int main(int argc, char** argv)
{
    if(argc != 3)
    {
        std::cerr<<"Wrong number of arguments\n";
        exit(EXIT_FAILURE);
    }

    int signal_number = std::stoi(argv[1]);
    pid_t target_pid = std::stoi(argv[2]);

    if (kill(target_pid, signal_number) == 0)
    {
        std::cout<<"Signal "<< signal_number<<"sent to process "<<target_pid<<std::endl;
    }
    else
    {
        std::perror("kill");
        exit(EXIT_FAILURE);
    }


    return 0;

}