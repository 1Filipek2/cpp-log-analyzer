#include <catch2/catch.hpp>

#include "analyzer.hpp"

TEST_CASE("countLevels should correctly count log levels", "[analyzer]") {
    std::vector<LogEntry> entries = {
        {"2024-06-01", "12:00:00", LogLevel::INFO, "Application started"},
        {"2024-06-01", "12:01:00", LogLevel::WARN, "Low disk space"},
        {"2024-06-01", "12:02:00", LogLevel::ERROR, "NullPointerException"},
        {"2024-06-01", "12:03:00", LogLevel::INFO, "User logged in"},
        {"2024-06-01", "12:04:00", LogLevel::ERROR, "OutOfMemoryError"}
    };

    auto levelCounts = countLevels(entries);

    REQUIRE(levelCounts[LogLevel::INFO] == 2);
    REQUIRE(levelCounts[LogLevel::WARN] == 1);
    REQUIRE(levelCounts[LogLevel::ERROR] == 2);
}