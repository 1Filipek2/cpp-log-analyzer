#include "analyzer.hpp"
#include <algorithm>

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

std::vector<LogEntry> filterByLevel(const std::vector<LogEntry>& entries, const std::string& level) {
   std::vector<LogEntry> filteredEntries;

    for (const auto& entry : entries) {
        if (entry.level == level) {
            filteredEntries.push_back(entry);
        }
    }
    return filteredEntries;
}

std::vector<std::pair<std::string, int>> getTopErrorMessages(const std::vector<LogEntry>& entries, std::size_t topN) {
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
