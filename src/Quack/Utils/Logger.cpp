#include "Quack/Utils/Logger.hpp"
#include <iostream>

std::mutex Logger::s_mutex;
LogLevel Logger::s_minLogLevel = LogLevel::Info;

void Logger::log(LogLevel level, const std::string& message) {
    if (level < s_minLogLevel) {
        return;
    }

    std::lock_guard lock(s_mutex);

    switch (level) {
        case LogLevel::Debug:    std::cout << "[DEBUG] "; break;
        case LogLevel::Info:     std::cout << "[INFO] "; break;
        case LogLevel::Warning:  std::cout << "[WARNING] "; break;
        case LogLevel::Error:    std::cout << "[ERROR] "; break;
    }

    std::cout << message << '\n';
}

void Logger::debug(const std::string& message) {
    log(LogLevel::Debug, message);
}

void Logger::info(const std::string& message) {
    log(LogLevel::Info, message);
}

void Logger::warn(const std::string& message) {
    log(LogLevel::Warning, message);
}

void Logger::error(const std::string& message) {
    log(LogLevel::Error, message);
}

void Logger::setMinLogLevel(LogLevel level) {
    std::lock_guard lock(s_mutex);
    s_minLogLevel = level;
}
