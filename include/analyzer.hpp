#pragma once

#include <vector>
#include <map>
#include <string>

#include "log_entry.hpp"

std::map<std::string, int> countLevels(const std::vector<LogEntry>& entries);