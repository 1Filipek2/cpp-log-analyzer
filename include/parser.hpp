#pragma once

#include <string>
#include <optional>

#include "log_entry.hpp"

std::optional<LogEntry> parseLogLine(const std::string& line);