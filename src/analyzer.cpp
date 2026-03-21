#include "analyzer.hpp"

std::map<std::string, int> countLevels(const std::vector<LogEntry>& entries) {
    std::map<std::string, int> counts;

    for (const auto& entry : entries) {
        counts[entry.level]++;
    }
    return counts;
}