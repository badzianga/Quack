#ifndef QUACK_FILE_IO_HPP
#define QUACK_FILE_IO_HPP
#include <string>

/**
 * @brief Static utility class for file input.
 *
 * Provides a simple interface for reading files as text.
 */
class FileIO {
public:
    /**
     * @brief Deleted default constructor.
     */
    FileIO() = delete;

    /**
     * @brief Deleted copy constructor.
     */
    FileIO(const FileIO&) = delete;

    /**
     * @brief Deleted move constructor.
     */
    FileIO(FileIO&&) = delete;

    /**
     * @brief Deleted copy assignment.
     */
    FileIO& operator=(const FileIO&) = delete;

    /**
     * @brief Deleted move assignment.
     */
    FileIO& operator=(FileIO&&) = delete;

    /**
     * @brief Read the entire contents of a text file.
     *
     * @param filename Path to the file.
     * @return File content as a string.
     */
    static std::string read(const char* filename);
};

#endif //QUACK_FILE_IO_HPP
