#pragma once

#include <string>
#include <optional>
#include <vector>

#include "log_entry.hpp"

[[nodiscard]] std::optional<LogEntry> parseLogLine(const std::string& line);
[[nodiscard]] std::optional<std::vector<LogEntry>> parseLogFile(const std::string& filename);