#include "parser.hpp"

#include <sstream>

std::optional<LogEntry> parseLogLine(const std::string& line) {
    if (line.empty()) {
        return std::nullopt;
    }

    std::stringstream ss(line);

    LogEntry entry;

    if (!(ss >> entry.date >> entry.time >> entry.level)) {
        return std::nullopt;
    }

    std::getline(ss, entry.message);

    if (!entry.message.empty() && entry.message[0] == ' ') {
        entry.message.erase(0, 1);
    }

    if (entry.message.empty()) {
        return std::nullopt;
    }

    return entry;
}