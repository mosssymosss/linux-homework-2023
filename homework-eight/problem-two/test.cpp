#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <cerrno>
#include <cstring>

int main(int argc, char** argv)
{
//    if(argc < 4)
//    {
//        std::cerr << "wrong argument\n";
//        exit(EXIT_FAILURE);
//    }

    std::cout << argc <<std::endl;
    std::vector<char*> dzax;
    std::vector<char*> aj;
    bool pipline = false;
    for(int i = 1; i < argc; ++i)
    {
        //std::cout << argv[i] <<std::endl;
        if(!(strcmp(argv[i], "?")))
        {
            pipline = true;
            continue;
        }
        if(pipline)
            aj.push_back(argv[i]);
        else
            dzax.push_back(argv[i]);

    }
    //std::cout<<pipline<<std::endl;
    //    std::cout<<aj.size()<<" "<<dzax.size()<<std::endl;
    if(aj.empty() || dzax.empty())
    {
        std::cerr << "wrong input\n";
        exit(EXIT_FAILURE);
    }
    dzax.push_back(nullptr);
    aj.push_back(nullptr);
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1)
    {
        std::perror("pipe");
        exit(errno);
    }

    pid_t bales = fork();

    if (bales < 0) {
        std::perror("fork");
        exit(errno);
    }
    if (bales == 0)
    {
        if(close(pipe_fd[0]) == -1)
        {
            std::perror("close");
            exit(errno);
        }

        if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
        {
            std::perror("dup2");
            exit(errno);
        }
        if(close(pipe_fd[1]) == -1)
        {
            std::perror("close");
            exit(errno);
        }

        if(execvp(dzax[0], dzax.data()) == -1)
        {
            std::cout << dzax[0] << ": dzax command not found" << std::endl;
            exit(errno);
        }

    }
    int status;
    if(waitpid(bales, &status, 0) == -1)
    {
        std::perror("wait");
        exit(errno);
    }
    pid_t en_myus_bales = fork();

    if(en_myus_bales < 0)
    {
        std::perror("fork");
        exit(errno);
    }

    if(en_myus_bales == 0)
    {
        if(close(pipe_fd[1]) == -1)
        {
            std::perror("close");
            exit(errno);
        }

        if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
        {
            std::perror("dup2");
            exit(errno);
        }
        if(close(pipe_fd[0]) == -1)
        {
            std::perror("close");
            exit(errno);
        }

        if(execvp(aj[0], aj.data()) == -1)
        {
            std::cout << aj[0] << ": aj command not found" << std::endl;
            exit(errno);
        }
    }

    close(pipe_fd[0]);
    close(pipe_fd[1]);

    int status2;
    if(waitpid(en_myus_bales, &status2, 0) == -1)
    {
        std::perror("wait");
        exit(errno);
    }


    return 0;
}