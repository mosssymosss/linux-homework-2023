
#include <iostream>
#include <unistd.h>
#include <vector>
#include <cerrno>
#include <iostream>
#include <fcntl.h>

int main(int argc, char** argv)
{
    std::string source_file, destination_file;
    off_t source_offset, dest_offset;
    size_t bytes_to_copy;

    std::cout << "Enter the name of the source file: ";
    std::cin >> source_file;

    std::cout << "Enter the name of the destination file: ";
    std::cin >> destination_file;

    std::cout << "Enter the initial offset in the source file (in bytes): ";
    std::cin >> source_offset;

    std::cout << "Enter the initial offset in the destination file (in bytes): ";
    std::cin >> dest_offset;

    std::cout << "Enter the number of bytes to copy: ";
    std::cin >> bytes_to_copy;

    int from = open(source_file.c_str(), O_RDONLY);
    if (from == -1)
    {
        perror("Error opening source file");
        return 1;
    }

    int to = open(destination_file.c_str(), O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
    if (to == -1)
    {
        perror("Error opening destination file");
        return 1;
    }

    if (lseek(from, source_offset, SEEK_SET) == -1)
    {
        perror("Error setting source file offset");
        exit(EXIT_FAILURE);
    }
    if (lseek(to, dest_offset, SEEK_SET) == -1)
    {
        perror("Error setting destination file offset");
        exit(EXIT_FAILURE);
    }

    std::vector<char> buffer(1, '\0');

    ssize_t total_copied = 0;
    ssize_t bytes_read;
    while((total_copied <= bytes_to_copy) && ((bytes_read = read(from, buffer.data(), 1)) != 0))
    {
        if(bytes_read == -1)
        {
            perror("Error reading from source file");
            exit(EXIT_FAILURE);
        }
        ssize_t bytes_written = write(to, buffer.data(), bytes_read);
        if (bytes_written == -1)
        {
            perror("Error writing to destination file");
            exit(EXIT_FAILURE);
        }
        total_copied += bytes_read;
    }
    ssize_t close_fd = close(to);
    if (close_fd == -1)
    {
        perror("Error closing source file");
        exit(EXIT_FAILURE);
    }
    close_fd = close(from);
    if (close_fd == -1)
    {
        perror("Error closing source file");
        exit(EXIT_FAILURE);
    }
    
    return 0;
}