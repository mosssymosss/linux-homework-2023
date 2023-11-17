#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t child_pid = fork();


    if (child_pid< 0)
    {
        std::perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (child_pid == 0)
    {
        sleep(2);
        if (kill(getppid(), SIGKILL) == 0)
        {
            std::cout<<"OMG WHAT DID I JUST DO?!?!?!?!?!?\n";
        }
        else
        {
            std::cout<<"I got grounded for trying to kill my own parents:[\n";
        }
        exit(EXIT_SUCCESS);
    }
    else
    {
        std::cout<<"Luke I am your father... " << getpid() <<"\n";
        int status;
        waitpid(child_pid, &status, 0);

        if (WIFEXITED(status))
        {
            std::cout << "exit code: " << WEXITSTATUS(status) << std::endl;
        }
    }

    return 0;
}
