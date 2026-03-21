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

    return 0;
}