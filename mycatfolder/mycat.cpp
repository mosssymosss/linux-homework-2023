#include <iostream>
#include <cerrno>
#include <vector>
#include <fcntl.h>
#include <unistd.h>

const std::size_t buffer_size = 4096;

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        std::cerr  << errno << ": wrong arguments";
        exit(EXIT_FAILURE);
    }
    const char* file = argv[1];
    int file_id = open(file, O_RDONLY);
    if(file_id == -1)
    {
        std::cerr  << errno << ": cannot open file";
        exit(EXIT_FAILURE);
    }
    std::vector<char> buffer(buffer_size, '\0');
    ssize_t bytes_read;
    while(0 != (bytes_read = read(file_id, buffer.data(), buffer_size)))
    {
	if(bytes_read < 0)
	{
	    std::cerr << "read failed: ";	
            write(1, buffer.data(), bytes_read);
	}
    }

    close(file_id);
    return 0;
}

