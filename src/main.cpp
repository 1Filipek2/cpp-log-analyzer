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

    return 0;
}