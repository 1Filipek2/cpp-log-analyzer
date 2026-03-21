#include "analyzer.hpp"

std::map<std::string, int> countLevels(const std::vector<LogEntry>& entries) {
    std::map<std::string, int> counts;

    for (const auto& entry : entries) {
        counts[entry.level]++;
    }
    return counts;
}

std::unordered_map<std::string, int> countMessageFrequency(const std::vector<LogEntry>& entries) {
    std::unordered_map<std::string, int> messageCounts;

    for (const auto& entry : entries) {
        messageCounts[entry.message]++;
    }
    return messageCounts;
}