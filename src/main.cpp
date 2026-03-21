#include <iostream>
#include <map>
#include <vector>

#include "analyzer.hpp"
#include "cli.hpp"
#include "exporter.hpp"
#include "parser.hpp"

int main(int argc, char* argv[]) {
    auto options = parseArguments(argc, argv);

    if (!options.has_value()) {
        return 1;
    }

    std::vector<LogEntry> entries = parseLogFile(options->inputFile);

    if (options->levelFilter.has_value()) {
        entries = filterByLevel(entries, *options->levelFilter);
        std::cout << "Filtered level: " << *options->levelFilter << std::endl;
    }

    std::cout << "Loaded valid entries: " << entries.size() << std::endl;

    std::map<std::string, int> levelCounts = countLevels(entries);
    std::cout << "Level counts:" << std::endl;

    for (const auto& [level, count] : levelCounts) {
        std::cout << level << ": " << count << std::endl;
    }

    std::cout << std::endl;

    std::vector<std::pair<std::string, int>> topErrors = getTopErrorMessages(entries, options->topErrors);
    std::cout << "Top error messages:" << std::endl;

    int index = 1;
    for (const auto& [message, count] : topErrors) {
        std::cout << index << ". " << message << " - " << count << std::endl;
        ++index;
    }

    std::cout << std::endl;

    if (options->exportFile.has_value()) {
        bool exportOk = exportSummaryCsv(*options->exportFile, levelCounts, topErrors);

        if (exportOk) {
            std::cout << "Export successful: " << *options->exportFile << "\n";
        } else {
            std::cout << "Export failed \n";
            return 1;
        }
    }

    return 0;
}