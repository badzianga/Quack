#ifndef QUACK_TIME_HPP
#define QUACK_TIME_HPP

/**
 * @brief Utility class for time management.
 *
 * Provides access to delta time (time between frames)
 * and frames per second (FPS). This class is used internally
 * by the engine and should only be accessed via static methods.
 */
class Time {
public:
    /**
     * @brief Deleted copy constructor.
     */
    Time(const Time&) = delete;

    /**
     * @brief Deleted move constructor.
     */
    Time(Time&&) = delete;

    /**
     * @brief Deleted copy assignment.
     */
    Time& operator=(const Time&) = delete;

    /**
     * @brief Deleted move assignment.
     */
    Time& operator=(Time&&) = delete;

    /**
     * @brief Get the time elapsed since the last frame.
     *
     * @return Time delta in seconds.
     */
    static float getDeltaTime();

    /**
     * @brief Get the current frames per second.
     *
     * @return FPS value.
     */
    static int getFPS();

private:
    /**
     * @brief Private constructor to enforce singleton pattern.
     */
    Time();

    /**
     * @brief Update delta time and FPS.
     *
     * Called internally by the engine once per frame.
     */
    static void update();

    static Time s_instance;

    float m_deltaTime;
    float m_lastFrameTime;

    friend class Engine;
};

#endif //QUACK_TIME_HPP
