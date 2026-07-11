#include "exporter.hpp"
#include <fstream>
#include <iostream>

static std::string escapeCsvField(const std::string& field) {
    if (field.find_first_of(",\"\n\r") != std::string::npos) {
        std::string escaped = "\"";
        for (char c : field) {
            if (c == '"') {
                escaped += "\"\"";
            } else {
                escaped += c;
            }
        }
        escaped += "\"";
        return escaped;
    }
    return field;
}

bool CsvExporter::exportSummary(const std::string& filename,
                               const std::map<std::string, int>& levelCounts,
                               const std::vector<std::pair<std::string, int>>& topErrors) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Failed to open export file: " << filename << std::endl;
        return false;
    }
    file << "Level,Count\n";
    for (const auto& [level, count] : levelCounts) {
        file << escapeCsvField(level) << "," << count << "\n";
    }
    file << "Error,Count\n";
    for (const auto& [message, count] : topErrors) {
        file << escapeCsvField(message) << "," << count << "\n";
    }
    return true;
}

bool exportSummaryCsv(const std::string& filename,
                      const std::map<std::string, int>& levelCounts,
                      const std::vector<std::pair<std::string, int>>& topErrors) {
    CsvExporter exporter;
    return exporter.exportSummary(filename, levelCounts, topErrors);
}
