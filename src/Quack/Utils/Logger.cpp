#include "Quack/Utils/Logger.hpp"
#include <iostream>

Logger::LogLevel Logger::minLogLevel = LogLevel::Info;
std::ostringstream Logger::LogStream::s_stream;

std::string Logger::LogStream::toString() const {
    switch (m_level) {
        case LogLevel::Debug:   return "[DEBUG]";
        case LogLevel::Info:    return "[INFO]";
        case LogLevel::Warning: return "[WARNING]";
        case LogLevel::Error:   return "[ERROR]";
        default:                return "[UNKNOWN]";
    }
}

Logger::LogStream::LogStream(LogLevel level) : m_level(level) {}

Logger::LogStream::~LogStream() {
    if (m_level >= minLogLevel) {
        std::cout << toString() << ' ' << s_stream.str() << '\n';
        s_stream.str("");
        s_stream.clear();
    }
}

Logger::LogStream Logger::debug() {
    return LogStream(LogLevel::Debug);
}

Logger::LogStream Logger::info() {
    return LogStream(LogLevel::Info);
}

Logger::LogStream Logger::warning() {
    return LogStream(LogLevel::Warning);
}

Logger::LogStream Logger::error() {
    return LogStream(LogLevel::Error);
}
