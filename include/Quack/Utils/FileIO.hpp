#ifndef QUACK_FILE_IO_HPP
#define QUACK_FILE_IO_HPP
#include <string>

class FileIO {
public:
    FileIO() = delete;
    ~FileIO() = delete;
    FileIO(const FileIO&) = delete;
    FileIO(FileIO&&) = delete;
    FileIO& operator=(const FileIO&) = delete;
    FileIO& operator=(FileIO&&) = delete;

    static std::string read(const char* filename);
};

#endif //QUACK_FILE_IO_HPP
