#pragma once
#include <string>

enum class LogLevel {
    INFO,
    WARN,
    ERROR,
    UNKNOWN
};

template<typename StringType>
LogLevel logLevelFromString(const StringType& str) {
    if (str == "INFO") return LogLevel::INFO;
    if (str == "WARN" || str == "WARNING") return LogLevel::WARN;
    if (str == "ERROR") return LogLevel::ERROR;
    return LogLevel::UNKNOWN;
}

inline std::string logLevelToString(LogLevel level) {
    switch (level) {
        case LogLevel::INFO: return "INFO";
        case LogLevel::WARN: return "WARNING";
        case LogLevel::ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

struct LogEntry {
    std::string date;
    std::string time;
    LogLevel level;
    std::string message;
};