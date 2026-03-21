#include "exporter.hpp"

#include <fstream>
#include <iostream>

bool exportSummaryCsv(const std::string& filename,
                      const std::map<std::string, int>& levelCounts,
                      const std::vector<std::pair<std::string, int>>& topErrors) {

    std::ofstream file(filename);

    if (!file) {
        std::cerr << "Failed to open export file: " << filename << std::endl;
        return false;
    }

    file << "section,key,value\n";

    for (const auto& [level, count] : levelCounts) {
        file << "levels," << level << "," << count << std::endl;
    }

    for (const auto& [message, count] : topErrors) {
        file << "top_errors," << message << "," << count << std::endl;
    }

    return true;
}