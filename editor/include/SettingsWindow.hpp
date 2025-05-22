#ifndef QUACK_EDITOR_SETTINGS_WINDOW_HPP
#define QUACK_EDITOR_SETTINGS_WINDOW_HPP
#include "Quack/Graphics/Color.hpp"

class Window;

class SettingsWindow {
public:
    void show(const Window& editorWindow);

    bool visible = false;
    bool vSyncEnabled = true;
    Color clearColor = Color::Black;
};

#endif //QUACK_EDITOR_SETTINGS_WINDOW_HPP
