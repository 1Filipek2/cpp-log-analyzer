#pragma once

#include <optional>
#include <string>

struct CliOptions {
    std::string inputFile;
    std::optional<std::string> levelFilter;
    std::optional<std::string> exportFile;
    std::size_t topErrors = 3;
};

std::optional<CliOptions> parseArguments(int argc, char* argv[]);