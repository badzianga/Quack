#ifndef QUACK_EDITOR_IMGUI_CONFIG_HPP
#define QUACK_EDITOR_IMGUI_CONFIG_HPP

struct GLFWwindow;

class ImGuiConfig {
public:
    ImGuiConfig() = delete;
    ~ImGuiConfig() = delete;
    ImGuiConfig(const ImGuiConfig&) = delete;
    ImGuiConfig(ImGuiConfig&&) = delete;
    ImGuiConfig& operator=(const ImGuiConfig&) = delete;
    ImGuiConfig& operator=(ImGuiConfig&&) = delete;

    static void Init(GLFWwindow* window);
    static void Shutdown();

    static void BeginFrame();
    static void EndFrame();
};

#endif //QUACK_EDITOR_IMGUI_CONFIG_HPP
