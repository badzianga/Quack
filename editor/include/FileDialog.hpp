#ifndef QUACK_EDITOR_FILE_DIALOG_HPP
#define QUACK_EDITOR_FILE_DIALOG_HPP
#include <string>

class FileDialog {
public:
    static void open(const std::string& id, const std::string& title, const char* filter, const std::string& path = ".");
};

#endif //QUACK_EDITOR_FILE_DIALOG_HPP
