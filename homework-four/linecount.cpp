#include <iostream>
#include <string>
#include <vector>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    int file_from = open(argv[1], O_RDONLY);
    if(file_from == -1)
    {
        perror("can't open");
        exit(EXIT_FAILURE);
    }

    std::vector<std::string> lines;
    std::string line;
    std::vector<char> buffer(1024);

    ssize_t bytes_read;
    while ((bytes_read = read(file_from, buffer.data(), 1024)) > 0)
    {
        if (bytes_read < 0)
        {
            std::cerr << "read failed: ";
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < bytes_read; ++i)
        {
            if (buffer[i] == '\n')
            {
                lines.push_back(line);
                line.clear();
            }
            else
            {
                line += buffer[i];
            }
        }
    }
    if (!line.empty())
    {
        lines.push_back(line);
    }

    std::cout << lines.size() << std::endl;

    int file_to = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if(file_to== -1)
    {
        perror("can't open");
        exit(EXIT_FAILURE);
    }

    for (int i = lines.size() - 1; i >= 0; i--)
    {
        if(write(file_to, lines[i].c_str(), lines[i].length()) == -1)
        {
            perror("can't write");
            exit(EXIT_FAILURE);
        }
        if(write(file_to, "\n", 1) == -1)
        {
            perror("can't write");
            exit(EXIT_FAILURE);
        }
    }

    if(close(file_to) == -1)
    {
        perror("can't close");
        exit(EXIT_FAILURE);
    }
    if(close(file_from) == -1)
    {
        perror("can't close");
        exit(EXIT_FAILURE);
    }
    return 0;
}