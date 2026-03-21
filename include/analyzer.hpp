#pragma once

#include <vector>
#include <map>
#include <unordered_map>
#include <string>

#include "log_entry.hpp"

std::map<std::string, int> countLevels(const std::vector<LogEntry>& entries);
std::unordered_map<std::string, int> countMessageFrequency(const std::vector<LogEntry>& entries);
std::vector<LogEntry> filterByLevel(const std::vector<LogEntry>& entries, const std::string& level);
std::vector<std::pair<std::string, int>> getTopErrorMessages(const std::vector<LogEntry>& entries, std::size_t topN);
