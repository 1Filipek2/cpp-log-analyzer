#include "app.hpp"

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "analyzer.hpp"
#include "cli.hpp"
#include "exporter.hpp"
#include "parser.hpp"

namespace
{
void printLevelCounts(const std::map<LogLevel, int>& levelCounts)
{
    std::cout << "Level counts: \n";

    for (const auto& [level, count] : levelCounts)
    {
        std::cout << logLevelToString(level) << ": " << count << "\n";
    }

    std::cout << "\n";
}

void printTopErrors(const std::vector<std::pair<std::string, int>>& topErrors)
{
    std::cout << "Top error messages: \n";

    if (topErrors.empty())
    {
        std::cout << "No error messages found \n\n";
        return;
    }

    int index = 1;
    for (const auto& [message, count] : topErrors)
    {
        std::cout << index << ". " << message << " - " << count << "\n";
        ++index;
    }

    std::cout << "\n";
}

bool writeCsvSummary(
    const std::string& filename,
    const std::map<LogLevel, int>& levelCounts,
    const std::vector<std::pair<std::string, int>>& topErrors)
{
    std::map<std::string, int> levelCountsStr;

    for (const auto& [level, count] : levelCounts)
    {
        levelCountsStr[std::string(logLevelToString(level))] = count;
    }

    CsvExporter exporter;

    return exporter.exportSummary(filename, levelCountsStr, topErrors);
}

} // namespace

int runApplication(int argc, char* argv[])
{
    auto options = parseArguments(argc, argv);

    if (!options.has_value())
    {
        return 1;
    }

    auto entriesResult = parseLogFile(options->inputFile);

    if (!entriesResult)
    {
        return 1;
    }

    auto entries = std::move(*entriesResult);
    LogAnalyzer analyzer;

    if (options->levelFilter.has_value())
    {
        LogLevel filterLevel = logLevelFromString(*options->levelFilter);
        entries = analyzer.filterByLevel(entries, filterLevel);

        std::cout << "Filtered level: " << *options->levelFilter << "\n";
    }

    std::cout << "Loaded valid entries: " << entries.size() << "\n\n";

    std::map<LogLevel, int> levelCounts = analyzer.countLevels(entries);

    printLevelCounts(levelCounts);

    std::vector<std::pair<std::string, int>> topErrors = analyzer.getTopErrorMessages(entries, options->topErrors);

    printTopErrors(topErrors);

    if (options->exportFile.has_value())
    {
        if (!writeCsvSummary(*options->exportFile, levelCounts, topErrors))
        {
            std::cout << "Export failed \n";
            return 1;
        }

        std::cout << "Export successful: " << *options->exportFile << "\n";
    }

    return 0;
}
