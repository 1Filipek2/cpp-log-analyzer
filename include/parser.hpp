#pragma once

#include <string>
#include <optional>
#include <vector>

#include "log_entry.hpp"
#include "parser_fatal_exception.hpp"

std::optional<LogEntry> parseLogLine(const std::string& line);
std::vector<LogEntry> parseLogFile(const std::string& filename);