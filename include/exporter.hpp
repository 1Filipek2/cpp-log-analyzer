#pragma once

#include <string>
#include <map>
#include <vector>
#include <utility>

bool exportSummaryCsv(const std::string& filename,
                      const std::map<std::string, int>& levelCounts,
                      const std::vector<std::pair<std::string, int>>& topErrors);