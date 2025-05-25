#ifndef QUACK_LOGGER_HPP
#define QUACK_LOGGER_HPP
#include <sstream>

class LogStream;

class Logger {
public:
    enum class LogLevel { Debug, Info, Warning, Error, Off };

    class LogStream {
    public:
        explicit LogStream(LogLevel level);

        ~LogStream();

        template <typename T>
        LogStream& operator<<(const T& value) {
            s_stream << value;
            return *this;
        }
    private:
        [[nodiscard]] std::string toString() const;

        LogLevel m_level;
        static std::ostringstream s_stream;
    };

    Logger() = delete;
    Logger(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger& operator=(Logger&&) = delete;

    static LogStream debug();
    static LogStream info();
    static LogStream warning();
    static LogStream error();

    static LogLevel minLogLevel;
};

#endif //QUACK_LOGGER_HPP
