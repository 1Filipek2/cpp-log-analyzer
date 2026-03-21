#include <iostream>
#include <map>
#include <vector>

#include "analyzer.hpp"
#include "exporter.hpp"
#include "parser.hpp"

int main() {
    std::vector<LogEntry> entries = parseLogFile("../sample/sample.log");
    std::cout << "Loaded valid entries: " << entries.size() << std::endl;

    std::map<std::string, int> levelCounts = countLevels(entries);
    std::cout << "Level counts:" << std::endl;

    for (const auto& [level, count] : levelCounts) {
        std::cout << level << ": " << count << std::endl;
    }

    std::cout << std::endl;

    std::vector<std::pair<std::string, int>> topErrors = getTopErrorMessages(entries, 3);
    std::cout << "Top error messages:" << std::endl;

    int index = 1;
    for (const auto& [message, count] : topErrors) {
        std::cout << index << ". " << message << " - " << count << std::endl;
        ++index;
    }

    std::cout << std::endl;

    bool exportOk = exportSummaryCsv("../sample/summary.csv", levelCounts, topErrors);

    if (exportOk) {
        std::cout << "Export successful: ../sample/summary.csv\n";
    } else {
        std::cout << "Export failed\n";
    }

    return 0;
}