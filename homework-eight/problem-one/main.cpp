#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cerrno>


int main()
{
    int first_pipe[2];
    int second_pipe[2];

    if(pipe(first_pipe) == -1 || pipe(second_pipe) == -1)
    {
        std::perror("truba");
        exit(errno);
    }

    pid_t firstborn = fork();

    if(firstborn < 0)
    {
        std::perror("fork1");
        exit(errno);
    }
    if(firstborn == 0) //child mek
    {
        if(close(first_pipe[0]) == -1)
        {
            std::perror("close");
            exit(errno);
        }
        if(close(second_pipe[1]) == -1)
        {
            std::perror("close");
            exit(errno);
        }

        pid_t my_pid = getpid();

        if(write(first_pipe[1], &my_pid, sizeof(my_pid)) == -1)
        {
            std::perror("write");
            exit(errno);
        }

        pid_t sibling_pid;

        if(read(second_pipe[0], &sibling_pid, sizeof(sibling_pid)) == -1)
        {
            std::perror("read");
            exit(errno);
        }

        std::cout << "I am the firstborn: " << my_pid << "\nMy sibling is: " << sibling_pid << std::endl;

        if(close(first_pipe[1]) == -1)
        {
            std::perror("close");
            exit(errno);
        }
        if(close(second_pipe[0]) == -1)
        {
            std::perror("close");
            exit(errno);
        }

        exit(EXIT_SUCCESS);
    }

    pid_t secondborn = fork();

    if(secondborn < 0)
    {
        std::perror("fork2");
        exit(errno);
    }
    if(secondborn == 0) //child mek
    {
        if(close(first_pipe[1]) == -1)
        {
            std::perror("close");
            exit(errno);
        }
        if(close(second_pipe[0]) == -1)
        {
            std::perror("close");
            exit(errno);
        }

        pid_t my_pid = getpid();

        if(write(second_pipe[1], &my_pid, sizeof(my_pid)) == -1)
        {
            std::perror("write");
            exit(errno);
        }

        pid_t sibling_pid;

        if(read(first_pipe[0], &sibling_pid, sizeof(sibling_pid)) == -1)
        {
            std::perror("read");
            exit(errno);
        }

        std::cout << "I am the secondborn: " << my_pid << "\nMy sibling is: " << sibling_pid << std::endl;

        if(close(first_pipe[0]) == -1)
        {
            std::perror("close");
            exit(errno);
        }
        if(close(second_pipe[1]) == -1)
        {
            std::perror("close");
            exit(errno);
        }

        exit(EXIT_SUCCESS);
    }

    if(close(first_pipe[0]) == -1)
    {
        std::perror("close");
        exit(errno);
    }
    if(close(second_pipe[0]) == -1)
    {
        std::perror("close");
        exit(errno);
    }
    if(close(first_pipe[1]) == -1)
    {
        std::perror("close");
        exit(errno);
    }
    if(close(second_pipe[1]) == -1)
    {
        std::perror("close");
        exit(errno);
    }

    int status1, status2;
    waitpid(firstborn, &status1, 0);
    waitpid(secondborn, &status2, 0);

    return 0;
}
