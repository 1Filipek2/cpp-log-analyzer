#include "parser.hpp"

#include <fstream>
#include <iostream>
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
    if (entry.message.empty() || entry.message.find_first_not_of(' ') == std::string::npos) {
        return std::nullopt;
    }
    if (entry.level != "INFO" && entry.level != "WARN" && entry.level != "ERROR") {
        return std::nullopt;
    }

    return entry;
}

std::vector<LogEntry> parseLogFile(const std::string& filename) {
    std::vector<LogEntry> entries;

    std::ifstream file(filename);

    if (!file) {
        std::cerr << "Failed to open file: " << filename << "\n";
        return entries;
    }

    std::string line;
    int lineNumber = 0;

    while (std::getline(file, line)) {
        ++lineNumber;

        auto parsedEntry = parseLogLine(line);

        if (parsedEntry.has_value()) {
            entries.push_back(*parsedEntry);
        } else {
            std::cerr << "Invalid log line at line " << lineNumber << "\n";
        }
    }

    return entries;
}