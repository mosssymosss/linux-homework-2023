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
    const char *name = "/shared_meme";
    const int size = 1000;

    int shm_fd = shm_open(name, O_RDWR, 0666);
    if (shm_fd == -1)
    {
        std::perror("shm_open");
        exit(errno);
    }

    if (shm_unlink(name) == -1)
    {
        std::perror("shm_unlink");
        exit(errno);
    }

    if (close(shm_fd) == -1)
    {
        perror("close");
        exit(errno);
    }

    std::cout << "destroy finished" << std::endl;

    return 0;
}