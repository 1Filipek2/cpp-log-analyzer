#pragma once

#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <memory>

#include "log_entry.hpp"

class LogAnalyzer 
{
public:
    LogAnalyzer() = default;

    [[nodiscard]] std::map<LogLevel, int> countLevels(const std::vector<LogEntry>& entries) const;
    [[nodiscard]] std::unordered_map<std::string, int> countMessageFrequency(const std::vector<LogEntry>& entries) const;
    [[nodiscard]] std::vector<LogEntry> filterByLevel(const std::vector<LogEntry>& entries, LogLevel level) const;
    [[nodiscard]] std::vector<std::pair<std::string, int>> getTopErrorMessages(const std::vector<LogEntry>& entries, std::size_t topN) const;
};

[[nodiscard]] std::map<LogLevel, int> countLevels(const std::vector<LogEntry>& entries);
[[nodiscard]] std::unordered_map<std::string, int> countMessageFrequency(const std::vector<LogEntry>& entries);
[[nodiscard]] std::vector<LogEntry> filterByLevel(const std::vector<LogEntry>& entries, LogLevel level);
[[nodiscard]] std::vector<std::pair<std::string, int>> getTopErrorMessages(const std::vector<LogEntry>& entries, std::size_t topN);
