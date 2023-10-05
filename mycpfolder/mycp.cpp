#include <iostream>
#include <cerrno>
#include <vector>
#include <fcntl.h>
#include <unistd.h>

const std::size_t buffer_size = 4096;

int main(int argc, char** argv)
{
    if(argc != 3)
    {
        std::cerr  << errno << ": wrong arguments";
        exit(EXIT_FAILURE);
    }
    const char* file_from = argv[1];
    int file_from_id = open(file_from, O_RDONLY);
    constexpr mode_t copy_to_mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    const char* file_to = argv[2];
    int file_to_id = open(file_to, O_WRONLY | O_CREAT | O_TRUNC, copy_to_mode);
    if(file_from_id == -1)
    {
        std::cerr  << errno << ": cannot open file ";
        exit(EXIT_FAILURE);
    }
    if(file_to_id == -1)
    {
        std::cerr  << errno << ": cannot open file ";
        exit(EXIT_FAILURE);
    }
    std::vector<char> buffer(buffer_size, '\0');
    ssize_t bytes_read;
    while(0 != (bytes_read = read(file_from_id, buffer.data(), buffer_size)))
    {
        if (bytes_read < 0)
        {
	    std::cerr << "read failed: ";
            exit(EXIT_FAILURE);
        }
        ssize_t bytes_written = write(file_to_id, buffer.data(), bytes_read);
        if (bytes_written < 0)
       	{      
	    std::cout<< "write failed: ";
            exit(EXIT_FAILURE);
        }
    }
    std::cout << "copied successfully";
    close(file_to_id);
    close(file_from_id);
    return 0;
}


