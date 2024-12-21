#include "Logger.hpp"
#include <iostream>
#include <chrono>
#include <iomanip>

std::string get_color(MessageType type)
{
    switch (type)
    {
    case MessageType::RESET:
        return "\033[0m";
    case MessageType::ERROR:
        return "\033[31m";
    case MessageType::WARN:
        return "\033[33m";
    case MessageType::INFO:
        return "\033[32m";
    case MessageType::DEBUG:
        return "\033[94m";
    case MessageType::TIMESTAMP:
        return "\033[90m"; // Gray color
    default:
        return "";
    }
}

std::string get_message_type(MessageType type)
{
    switch (type)
    {
    case MessageType::DEBUG:
        return "DEBUG";
    case MessageType::ERROR:
        return "ERROR";
    case MessageType::WARN:
        return "WARN";
    case MessageType::INFO:
        return "INFO";
    case MessageType::RESET:
        return "";
    default:
        return "";
    }
}

std::string get_log_message(const std::string &message, MessageType type, const std::string &prefix)
{
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);

    std::string resultMsg = "";

    // Format timestamp
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_c), "%Y-%m-%d:%X");
    std::string timestamp = ss.str();

    std::string msgType = get_message_type(type);
    std::string msgColor = get_color(type);
    std::string resetColor = get_color(MessageType::RESET);

    std::string timestampColor = get_color(MessageType::TIMESTAMP);

    resultMsg += timestampColor + timestamp + resetColor + " ";
    resultMsg += msgColor + "[" + msgType + "]";

    if (!prefix.empty())
    {
        resultMsg += ":" + prefix + ": ";
    }
    else
    {
        resultMsg += ": ";
    }

    resultMsg += resetColor;
    resultMsg += message;

    return resultMsg;
}

void Logger::info(const std::string &message, const std::string &prefix)
{
    std::cout << get_log_message(message, MessageType::INFO, prefix) << std::endl;
}

void Logger::warn(const std::string &message, const std::string &prefix)
{
    std::cout << get_log_message(message, MessageType::WARN, prefix) << std::endl;
}

void Logger::error(const std::string &message, const std::string &prefix)
{
    std::cerr << get_log_message(message, MessageType::ERROR, prefix) << std::endl;
}

void Logger::debug(const std::string &message, const std::string &prefix)
{
    std::cout << get_log_message(message, MessageType::DEBUG, prefix) << std::endl;
}
