#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstring>
#include <cerrno>

int main()
{
    const char* name = "/shared_meme";
    const int size = 1000;
    int shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1)
    {
        std::perror("shm_open");
        exit(errno);
    }

    if (ftruncate(shm_fd, size * sizeof(int)) == -1)
    {
        std::perror("ftruncate");
        exit(errno);
    }

    int *array = (int*)mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (array == MAP_FAILED)
    {
        std::perror("mmap");
        exit(errno);
    }

    for (int i = 0; i < size; ++i)
    {
        array[i] = 0;
    }

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

    std::cout << "init finished" << std::endl;

    return 0;
}