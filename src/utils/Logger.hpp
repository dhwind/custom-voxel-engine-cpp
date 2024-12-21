#ifndef UTILS_LOGGER_HPP
#define UTILS_LOGGER_HPP

#include <string>

enum MessageType
{
    DEBUG = 0,
    RESET,
    ERROR,
    WARN,
    INFO,
    TIMESTAMP
};

class Logger
{
public:
    static void info(const std::string &message, const std::string &prefix = "");
    static void warn(const std::string &message, const std::string &prefix = "");
    static void error(const std::string &message, const std::string &prefix = "");
    static void debug(const std::string &message, const std::string &prefix = "");
};

#endif /* UTILS_LOGGER_HPP */
