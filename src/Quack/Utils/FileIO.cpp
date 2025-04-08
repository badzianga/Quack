#include "Quack/Utils/FileIO.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

std::string FileIO::read(const char* filename) {
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    std::stringstream stream;
    try {
        file.open(filename, std::ios::in);
        stream << file.rdbuf();
        file.close();
    }
    catch (std::ifstream::failure& error) {
        std::cerr << "File " << filename << " not successfully read: " << error.what() << '\n';
        exit(-1);
    }
    return stream.str();
}
