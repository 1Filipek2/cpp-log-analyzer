#include <catch2/catch.hpp>

#include "analyzer.hpp"

TEST_CASE("countLevels should correctly count log levels", "[analyzer]") {
    std::vector<LogEntry> entries = {
        {"2024-06-01", "12:00:00", "INFO", "Application started"},
        {"2024-06-01", "12:01:00", "WARN", "Low disk space"},
        {"2024-06-01", "12:02:00", "ERROR", "NullPointerException"},
        {"2024-06-01", "12:03:00", "INFO", "User logged in"},
        {"2024-06-01", "12:04:00", "ERROR", "OutOfMemoryError"}
    };

    auto levelCounts = countLevels(entries);

    REQUIRE(levelCounts["INFO"] == 2);
    REQUIRE(levelCounts["WARN"] == 1);
    REQUIRE(levelCounts["ERROR"] == 2);
}