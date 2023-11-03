#include <iostream>
//#include <string>
#include <string.h>
//#include <cstring>
#include <cstdlib>
//#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>
#include <ostream>


int main(int argc, char** argv)
{

    char  *gdir = NULL;
    char  *dir = NULL;
    char  *to = NULL;
    char buf[1000];
    char path[1000];
    if(getlogin() == NULL)
    {
        std::cerr << "not logged in" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string username = getlogin();
    char hostname[4096];
    if(gethostname(hostname, sizeof(hostname)) < 0)
    {
        std::cerr << "not logged in" << std::endl;
        exit(EXIT_FAILURE);
    }

    while(true)
    {
        if(getcwd(path, sizeof(path)) == NULL)
        {
            std::perror("getcwd");
            exit(errno);
        }
        std::cout<<"\033[91mMeineShell>";
        std::cout<<"\033[96m"<<username<<"@"<<hostname;
        std::cout<<"\033[0m:";
        std::cout<<"\033[93m~"<<path<<"\033[0m@ ";
        std::string input;
        std::getline(std::cin, input);
        if(input == "exit")
        {
            std::cout << input << std::endl;
            break;
        }
        std::vector<char*> args;
        char* token = strtok(const_cast<char*>(input.c_str()), " ");
        while (token != nullptr) {
            args.push_back(token);
            token = strtok(nullptr, " ");
        }
        args.push_back(nullptr);
        if (!strcmp(args[0], "cd"))
        {
            gdir = getcwd(buf, sizeof(buf));
            dir = strcat(gdir, "/");
            to = strcat(dir, args[1]);

            chdir(to);
            continue;
        }

        pid_t pid = fork();

        if(pid < 0)
        {
            std::perror("fork gone wrong");
            exit(errno);
        }

        if(pid == 0)
        {
            if(execvp(args[0], args.data()) < 0)
            {
                std::cout << args[0] << ": command not found" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            int status;
            if(wait(&status) < 0)
            {
                std::perror("wait");
                exit(errno);
            }

            if(WIFEXITED(status))
            {
                std::cout << "exit code: " << WEXITSTATUS(status) << std::endl;
            }

        }
    }
    return 0;
}