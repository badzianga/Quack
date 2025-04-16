#ifndef QUACK_ENGINE_HPP
#define QUACK_ENGINE_HPP
#include "Quack/Core/Window.hpp"

/**
 * @brief Core engine class of the Quack %Engine.
 *
 * This class manages the application's main loop and handles
 * window management. To use it, derive from this class and
 * implement the pure virtual methods.
 */
class Engine {
public:
    /**
     * @brief Default constructor.
     *
     * This constructor doesn't actually create the engine,
     * it is used only to declare the object.
     */
    Engine() = default;

    /**
     * @brief Destructor.
     *
     * Does nothing, but it is declared as virtual for polymorphism.
     */
    virtual ~Engine() = default;

    /**
     * @brief Deleted copy constructor.
     */
    Engine(const Engine&) = delete;

    /**
     * @brief Deleted move constructor.
     */
    Engine(Engine&&) = delete;

    /**
     * @brief Deleted copy assignment.
     */
    Engine& operator=(const Engine&) = delete;

    /**
     * @brief Deleted move assignment.
     */
    Engine& operator=(Engine&&) = delete;

    /**
     * @brief Create the window and initialize input system.
     *
     * This method should be called only once. Calls onCreate after initialization.
     *
     * @param width Width of the window
     * @param height Height of the window
     * @param title Title of the window
     * @return True if creation succeeded, false otherwise.
     */
    bool create(int width = 0, int height = 0, const char* title = nullptr);

    /**
    * @brief Start the engine loop.
    *
    * Enters the main application loop, updating internal systems, clearing the window,
    * calling onUpdate() each frame until stop() is called or window is closed and
    * displaying rendered frame on the screen.
    */
    void start();

    /**
     * @brief Stop the engine loop.
     *
     * Signals the engine to exit the main loop and proceed to destruction.
     */
    void stop();

    /**
     * @brief Destroy the engine and release resources.
     *
     * This method should be called to properly shut down
     * the engine and clean up resources such as the window.
     *
     * @return true if destruction succeeded, false otherwise.
     */
    bool destroy();

    /**
     * @brief Set the clear color used to clear the window each frame.
     *
     * @param red Red channel (0.f to 1.f).
     * @param green Green channel (0.f to 1.f).
     * @param blue Blue channel (0.f to 1.f).
     * @param alpha Alpha channel (0.f to 1.f).
     */
    void setWindowClearColor(float red, float green, float blue, float alpha) const;

    /**
     * @brief Set visibility of the mouse cursor in the window.
     *
     * When disabled, the cursor is hidden and locked for applications.
     *
     * @param enabled True to show the cursor, false to hide it.
     */
    void setWindowCursorEnabled(bool enabled) const;

    /**
     * @brief Callback invoked when the engine is created.
     *
     * Use this method to initialize game resources or subsystems.
     */
    virtual void onCreate() = 0;

    /**
     * @brief Callback invoked once per frame.
     *
     * This is the main update loop. Place game logic, input handling,
     * rendering, etc., here.
     */
    virtual void onUpdate() = 0;

    /**
     * @brief Callback invoked before the engine is destroyed.
     *
     * Use this to clean up resources or save state.
     */
    virtual void onDestroy() = 0;
private:
    Window m_window;
};

#endif //QUACK_ENGINE_HPP
