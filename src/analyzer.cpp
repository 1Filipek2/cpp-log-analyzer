#include "analyzer.hpp"
#include <algorithm>

std::map<std::string, int> LogAnalyzer::countLevels(const std::vector<LogEntry>& entries) const {
    std::map<std::string, int> counts;
    for (const auto& entry : entries) {
        counts[entry.level]++;
    }
    return counts;
}

std::unordered_map<std::string, int> LogAnalyzer::countMessageFrequency(const std::vector<LogEntry>& entries) const {
    std::unordered_map<std::string, int> messageCounts;
    for (const auto& entry : entries) {
        messageCounts[entry.message]++;
    }
    return messageCounts;
}

std::vector<LogEntry> LogAnalyzer::filterByLevel(const std::vector<LogEntry>& entries, const std::string& level) const {
    std::vector<LogEntry> filteredEntries;
    for (const auto& entry : entries) {
        if (entry.level == level) {
            filteredEntries.push_back(entry);
        }
    }
    return filteredEntries;
}

std::vector<std::pair<std::string, int>> LogAnalyzer::getTopErrorMessages(const std::vector<LogEntry>& entries, std::size_t topN) const {
    std::vector<LogEntry> errorEntries = filterByLevel(entries, "ERROR");
    std::unordered_map<std::string, int> messageCounts = countMessageFrequency(errorEntries);
    std::vector<std::pair<std::string, int>> topErrors;
    for (const auto& pair : messageCounts) {
        topErrors.push_back(pair);
    }
    std::sort(topErrors.begin(), topErrors.end(),
              [](const auto& a, const auto& b) {
                  return a.second > b.second;
              });
    if (topErrors.size() > topN) {
        topErrors.resize(topN);
    }
    return topErrors;
}

std::map<std::string, int> countLevels(const std::vector<LogEntry>& entries) {
    LogAnalyzer analyzer;
    return analyzer.countLevels(entries);
}

std::unordered_map<std::string, int> countMessageFrequency(const std::vector<LogEntry>& entries) {
    LogAnalyzer analyzer;
    return analyzer.countMessageFrequency(entries);
}

std::vector<LogEntry> filterByLevel(const std::vector<LogEntry>& entries, const std::string& level) {
    LogAnalyzer analyzer;
    return analyzer.filterByLevel(entries, level);
}

std::vector<std::pair<std::string, int>> getTopErrorMessages(const std::vector<LogEntry>& entries, std::size_t topN) {
    LogAnalyzer analyzer;
    return analyzer.getTopErrorMessages(entries, topN);
}
