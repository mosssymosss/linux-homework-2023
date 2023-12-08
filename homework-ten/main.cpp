#include <iostream>
#include <vector>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <cerrno>

struct TeliData
{
    int num1;
    int num2;
    std::string operation;
    std::string output_file;
};

void* gorci_telov(void* data)
{
    TeliData* tel = static_cast<TeliData*>(data);

    int res;
    if(tel->operation == "s")
    {
        res = tel->num1 + tel->num2;
    }
    else if(tel->operation == "m")
    {
        res = tel->num1 * tel->num2;
    }
    else if(tel->operation == "ss")
    {
        res = tel->num1 * tel->num1 + tel->num2 * tel->num2;
    }
    else
    {
        std::cerr << "No such operation: " << tel->operation <<std::endl;
        return nullptr;
    }

    int fd = open(tel->output_file.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if(fd == -1)
    {
        std::perror("open");
        return nullptr;
    }

    std::string line = std::to_string(tel->num1) + " " + tel->operation + " " + std::to_string(tel->num2) + " " + std::to_string(res);

    if(write(fd, line.c_str(), line.length()) == -1)
    {
        std::perror("write");
        return nullptr;
    }

    if(close(fd) == -1)
    {
        std::perror("close");
        return nullptr;
    }

    return nullptr;
}


int main()
{
    int n;
    std::cin>>n;

    std::vector<pthread_t> teler(n);
    std::vector<TeliData> inputs;

    for(int i = 0; i < n; ++i)
    {
        TeliData tel_d;
        std::cin >> tel_d.num1 >> tel_d.num2 >> tel_d.operation;
        tel_d.output_file = "out_" + std::to_string(i + 1);
        inputs.push_back(tel_d);
    }

    for(int i = 0; i < n; ++i)
    {
        if (pthread_create(&teler[i], nullptr, gorci_telov, &inputs[i]) != 0)
        {
            std::perror("pthread_create");
            exit(errno);
        }
    }



    for (auto& teler : teler)
    {
        pthread_join(teler, nullptr);
    }

    for(int i = 0; i < n; ++i)
    {
        std::cout<<inputs[i].output_file<<" ";
    }
    std::cout<<std::endl;
    return 0;
}