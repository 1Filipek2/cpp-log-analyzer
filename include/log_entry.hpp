#pragma once
#include <string>

struct LogEntry {
    std::string date;
    std::string time;
    std::string level;
    std::string message;
};