#include "cli.hpp"

#include <iostream>
#include <string>

std::optional<CliOptions> parseArguments(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: ./cpp_log_analyzer <input_file> [--level LEVEL] [--top-errors N] [--export OUTPUT.csv] \n";
        return std::nullopt;
    }

    CliOptions options;
    options.inputFile = argv[1];

    for (int i = 2; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "--level") {
            if (i + 1 >= argc) {
                std::cerr << "Missing value after --level \n";
                return std::nullopt;
            }
            options.levelFilter = argv[++i];
        }
        else if (arg == "--top-errors") {
            if (i + 1 >= argc) {
                std::cerr << "Missing value after --top-errors \n";
                return std::nullopt;
            }

            try {
                int value = std::stoi(argv[++i]);
                if (value < 1) {
                    std::cerr << "--top-errors must be greater than 0 \n";
                    return std::nullopt;
                }
                options.topErrors = static_cast<std::size_t>(value);
            } catch (...) {
                std::cerr << "Invalid value for --top-errors \n";
                return std::nullopt;
            }
        }
        else if (arg == "--export") {
            if (i + 1 >= argc) {
                std::cerr << "Missing value after --export \n";
                return std::nullopt;
            }
            options.exportFile = argv[++i];
        }
        else {
            std::cerr << "Unknown argument: " << arg << std::endl;
            return std::nullopt;
        }
    }

    return options;
}