#include <iostream>
#include <vector>

#include "analyzer.hpp"
#include "parser.hpp"

int main () {
    std::vector<LogEntry> entries = parseLogFile("../sample/sample.log");
    std::cout << "Loaded valid entries: " << entries.size() << std::endl;

    std::map<std::string, int> levelCounts = countLevels(entries);
    std::cout << "Level counts: " << std::endl;

    for (const auto& [level, count] : levelCounts) {
        std::cout << level << ": " << count << std::endl;
    }


    std::unordered_map<std::string, int> messageCounts = countMessageFrequency(entries);
    std::cout << "Message counts: " << std::endl;

    for (const auto& [message, count] : messageCounts) {
        std::cout << message << ": " << count << std::endl;
    }


    std::vector<LogEntry> filteredEntries = filterByLevel(entries, "ERROR");
    std::cout << "Filtered level: ERROR" << std::endl;
    std::cout << "Matching entries: " << filteredEntries.size() << std::endl;

    for (const auto& entry : filteredEntries) {
        std::cout << "Date: " << entry.date << std::endl;
        std::cout << "Time: " << entry.time << std::endl;
        std::cout << "Level: " << entry.level << std::endl;
        std::cout << "Message: " << entry.message << std::endl;
    }

    return 0;
}