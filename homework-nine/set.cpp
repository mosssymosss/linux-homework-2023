#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstring>
#include <cerrno>

void SieveOfEratosthenes(int* array, int n)
{
    array[0] = array[1] = 1;
    for (int i = 2; i < n; ++i)
    {
        if (array[i] == 0)
        {
            for (int j = i * i; j < n; j += i)
            {
                array[j] = 1;
            }
        }
    }
}

int main()
{
    const char *name = "/shared_meme";
    const int size = 1000;

    int shm_fd = shm_open(name, O_RDWR, 0666);
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

    SieveOfEratosthenes(array, size);

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

    std::cout << "set finished" << std::endl;
    return 0;
}