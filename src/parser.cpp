#include "parser.hpp"
#include "log_entry.hpp"
#include "parser_fatal_exception.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

std::optional<LogEntry> parseLogLine(const std::string& line) {
    if (line.empty()) {
        return std::nullopt;
    }

    std::stringstream ss(line);

    LogEntry entry;
    std::string levelStr;

    if (!(ss >> entry.date >> entry.time >> levelStr)) {
        return std::nullopt;
    }
    entry.level = logLevelFromString(levelStr);

    std::getline(ss, entry.message);
    if (!entry.message.empty() && entry.message[0] == ' ') {
        entry.message.erase(0, 1);
    }
    if (entry.message.empty() || entry.message.find_first_not_of(' ') == std::string::npos) {
        return std::nullopt;
    }
    if (entry.level == LogLevel::UNKNOWN) {
        return std::nullopt;
    }
    return entry;
}

std::vector<LogEntry> parseLogFile(const std::string& filename) {
    std::vector<LogEntry> entries;
    std::ifstream file(filename);
    if (!file) {
        throw ParserFatalException("Failed to open file: " + filename);
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