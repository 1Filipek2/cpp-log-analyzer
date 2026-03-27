#include <iostream>
#include <map>
#include <vector>
#include <memory>

#include "analyzer.hpp"
#include "cli.hpp"
#include "exporter.hpp"
#include "parser.hpp"

void printLevelCounts(const std::map<std::string, int>& levelCounts) {
    std::cout << "Level counts: \n";

    for (const auto& [level, count] : levelCounts) {
        std::cout << level << ": " << count << "\n";
    }

    std::cout << "\n";
}

void printTopErrors(const std::vector<std::pair<std::string, int>>& topErrors) {
    std::cout << "Top error messages: \n";

    if (topErrors.empty()) {
        std::cout << "No error messages found \n\n";
        return;
    }

    int index = 1;
    for (const auto& [message, count] : topErrors) {
        std::cout << index << ". " << message << " - " << count << "\n";
        ++index;
    }

    std::cout << "\n";
}

int main(int argc, char* argv[]) {
    auto options = parseArguments(argc, argv);

    if (!options.has_value()) {
        return 1;
    }

    std::vector<LogEntry> entries = parseLogFile(options->inputFile);

    auto analyzer = std::make_unique<LogAnalyzer>();
    if (options->levelFilter.has_value()) {
        entries = analyzer->filterByLevel(entries, *options->levelFilter);
        std::cout << "Filtered level: " << *options->levelFilter << "\n";
    }
    std::cout << "Loaded valid entries: " << entries.size() << "\n\n";

    std::map<std::string, int> levelCounts = analyzer->countLevels(entries);
    printLevelCounts(levelCounts);

    std::vector<std::pair<std::string, int>> topErrors = analyzer->getTopErrorMessages(entries, options->topErrors);
    printTopErrors(topErrors);

    if (options->exportFile.has_value()) {
        std::unique_ptr<Exporter> exporter = std::make_unique<CsvExporter>();
        bool exportOk = exporter->exportSummary(*options->exportFile, levelCounts, topErrors);

        if (exportOk) {
            std::cout << "Export successful: " << *options->exportFile << "\n";
        } else {
            std::cout << "Export failed \n";
            return 1;
        }
    }

    return 0;
}