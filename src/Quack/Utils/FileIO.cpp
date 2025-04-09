#include "Quack/Utils/FileIO.hpp"
#include "Quack/Utils/Logger.hpp"
#include <fstream>
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
    catch (std::ifstream::failure&) {
        Logger::error("Failed to open file: " + std::string(filename));
    }
    return stream.str();
}
