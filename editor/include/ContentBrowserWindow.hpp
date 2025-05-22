#ifndef QUACK_EDITOR_CONTENT_BROWSER_WINDOW_HPP
#define QUACK_EDITOR_CONTENT_BROWSER_WINDOW_HPP
#include <filesystem>

class ContentBrowserWindow {
public:
    void show();
private:
    void showDirectoryTree(const std::filesystem::path& path);
};

#endif //QUACK_EDITOR_CONTENT_BROWSER_WINDOW_HPP
