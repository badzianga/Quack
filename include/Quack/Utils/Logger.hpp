#ifndef QUACK_LOGGER_HPP
#define QUACK_LOGGER_HPP
#include <mutex>
#include <string>

/**
 * @brief Static logger utility for engine-wide logging.
 *
 * Provides thread-safe logging with different log levels.
 * Supports filtering by minimum log level.
 */
class Logger {
public:
    /**
     * @enum LogLevel
     * @brief Represents the severity of a log message.
     */
    enum class LogLevel { Debug, Info, Warning, Error };

    /**
     * @brief Deleted default constructor.
     */
    Logger() = delete;

    /**
     * @brief Deleted copy constructor.
     */
    Logger(const Logger&) = delete;

    /**
     * @brief Deleted move constructor.
     */
    Logger(Logger&&) = delete;

    /**
     * @brief Deleted copy assignment.
     */
    Logger& operator=(const Logger&) = delete;

    /**
     * @brief Deleted move assignment.
     */
    Logger& operator=(Logger&&) = delete;

    /**
     * @brief Log a message with a given log level.
     *
     * @param level Severity of the log message.
     * @param message The message content.
     */
    static void log(LogLevel level, const std::string& message);

    /**
     * @brief Log a debug message.
     *
     * @param message Message content.
     */
    static void debug(const std::string& message);

    /**
     * @brief Log an informational message
     *
     * @param message Message content.
     */
    static void info(const std::string& message);

    /**
     * @brief Log a warning message
     *
     * @param message Message content.
     */
    static void warn(const std::string& message);

    /**
     * @brief Log an error message.
     *
     * @param message Message content.
     */
    static void error(const std::string& message);

    /**
     * @brief Set the minimum log level.
     *
     * Messages below this level will be ignored.
     * By default, log level is set to Info.
     *
     * @param level Minimum log level to display.
     */
    static void setMinLogLevel(LogLevel level);

private:
    static std::mutex s_mutex;
    static LogLevel s_minLogLevel;
};

#endif //QUACK_LOGGER_HPP
