#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstring>
#include <cerrno>


std::string is_prime(int n, int* array)
{
    return array[n] == 0 ? "Yes" : "No";
}

int main(int argc, char** argv)
{

    if (argc != 2)
    {
        std::cerr << "Wrong arguments" << std::endl;
        exit(EXIT_FAILURE);
    }

    int num = atoi(argv[1]);
    const char *name = "/shared_meme";
    const int size = 1000;
    int shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1)
    {
        std::perror("shm_open");
        exit(errno);
    }

    int *array = (int*)mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (array == MAP_FAILED)
    {
        std::perror("mmap");
        exit(errno);
    }

    std::cout<<is_prime(num, array)<<std::endl;

    if (munmap(array, size) == -1)
    {
        std::perror("munmap");
        exit(errno);
    }

    if (close(shm_fd) == -1)
    {
        perror("close");
        exit(errno);
    }

    std::cout<<"check finished"<<std::endl;
    return 0;
}