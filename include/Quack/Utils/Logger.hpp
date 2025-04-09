#ifndef QUACK_LOGGER_HPP
#define QUACK_LOGGER_HPP
#include "LogLevel.hpp"
#include <mutex>
#include <string>

class Logger {
public:
    Logger() = delete;
    ~Logger() = delete;
    Logger(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger& operator=(Logger&&) = delete;

    static void log(LogLevel level, const std::string& message);

    static void debug(const std::string& message);
    static void info(const std::string& message);
    static void warn(const std::string& message);
    static void error(const std::string& message);

    static void setMinLogLevel(LogLevel level);

private:
    static std::mutex s_mutex;
    static LogLevel s_minLogLevel;
};

#endif //QUACK_LOGGER_HPP
