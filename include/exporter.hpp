#pragma once

#include <string>
#include <map>
#include <vector>
#include <utility>
#include <memory>

class Exporter
{
public:
    virtual ~Exporter() = default;

    [[nodiscard]] virtual bool exportSummary(
        const std::string& filename,
        const std::map<std::string, int>& levelCounts,
        const std::vector<std::pair<std::string, int>>& topErrors) = 0;
};

class CsvExporter : public Exporter
{
public:
    [[nodiscard]] bool exportSummary(
        const std::string& filename,
        const std::map<std::string, int>& levelCounts,
        const std::vector<std::pair<std::string, int>>& topErrors) override;
};

[[nodiscard]] bool exportSummaryCsv(
    const std::string& filename,
    const std::map<std::string, int>& levelCounts,
    const std::vector<std::pair<std::string, int>>& topErrors);