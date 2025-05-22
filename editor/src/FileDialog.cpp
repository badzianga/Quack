#include "FileDialog.hpp"
#include <ImGuiFileDialog.h>

void FileDialog::open(const std::string& id, const std::string& title, const char* filter, const std::string& path) {
    IGFD::FileDialogConfig config;
    config.path = path;
    config.countSelectionMax = 1;
    config.flags = ImGuiFileDialogFlags_Modal;
    ImGuiFileDialog::Instance()->OpenDialog(id, title, filter, config);
}
