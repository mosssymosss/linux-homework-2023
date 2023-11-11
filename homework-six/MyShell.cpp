#include <iostream>
#include <string>
#include <string.h>
//#include <cstring>
#include <cstdlib>
//#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>
#include <ostream>
#include <fcntl.h>
#include <algorithm>


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
    std::string input = "";
    while(true) {
        if (input.empty()) {
            if (getcwd(path, sizeof(path)) == NULL)
            {
                std::perror("getcwd");
                exit(errno);
            }
            std::cout << "\033[91mMeineShell>";
            std::cout << "\033[96m" << username << "@" << hostname;
            std::cout << "\033[0m:";
            std::cout << "\033[93m~" << path << "\033[0m@ ";


            std::getline(std::cin, input);
        }

        if(input == "exit")
        {
            std::cout << input << std::endl;
            break;
        }
        std::vector<char*> args;
        char* token = strtok(const_cast<char*>(input.c_str()), " ");
        //bool b = false;
        std::string b = " ";
        while (token != nullptr)
        {
            args.push_back(token);
            if(!(strcmp(args.back(), "&&")))
            {
                args.pop_back();
                b = "&";
                break;
            }
            else if(!(strcmp(args.back(), "||")))
            {
                args.pop_back();
                b = "|";
                break;
            }


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


        std::vector<char*> ua = args;
        ua.pop_back();


        auto slaq = std::find_if(ua.begin(), ua.end(), [](const char* str) {
            return strcmp(str, ">") == 0;
        });

        auto erku_slaq = std::find_if(ua.begin(), ua.end(), [](const char* str) {
            return strcmp(str, ">>") == 0;
        });


        if(pid == 0)
        {

            int fd;

            if(ua.size() > 2 && (slaq != ua.end() || erku_slaq != ua.end()))
            {
                if(slaq != ua.end())
                {
                    fd = open(*(slaq + 1), O_WRONLY | O_CREAT | O_TRUNC, 0666);
                    ua.erase(slaq, ua.end());
                }
                else
                {
                    fd = open(*(erku_slaq + 1), O_WRONLY | O_CREAT | O_APPEND, 0666);
                    ua.erase(erku_slaq, ua.end());
                }
            }


            if (fd == -1)
            {
                std::perror("open");
                exit(errno);
            }

            int stdout_copy = dup(1);

            if (stdout_copy == -1)
            {
                std::perror("dup");
                exit(errno);
            }

            if (dup2(fd, 1) == -1)
            {
                std::perror("dup2");
                exit(errno);
            }
            close(fd);

            ua.push_back(nullptr);
            if(execvp(ua[0], ua.data()) < 0)
            {
                std::cout << ua[0] << ": command not found" << std::endl;
                exit(EXIT_FAILURE);
            }

            if (dup2(stdout_copy, 1) == -1)
            {
                std::perror("dup2");
                exit(errno);
            }
            close(stdout_copy);

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
                if(WEXITSTATUS(status) != 0)
                {
                    if(!strcmp(b.c_str(), "&"))
                        input.clear();
                }
                else
                {
                    if(!strcmp(b.c_str(), "|"))
                        input.clear();
                }

            }
        }
        if(!strcmp(b.c_str(), " "))
            input.clear();
        else
        {
            auto a = input.find_first_of(b);
            std::string tmp = "";
            for (int i = a + 3; i < input.size(); ++i) {
                tmp += input[i];
            }
            input = tmp;
        }
    }

    free(dir);
    free(to);
    return 0;
}