#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "parser.hpp"
#include "log_entry.hpp"

TEST_CASE("parseLogLine returns nullopt for empty line", "[parser]") {
    std::string line = "";
    auto result = parseLogLine(line);
    REQUIRE_FALSE(result.has_value());
}

TEST_CASE("parseLogLine returns nullopt for incomplete line", "[parser]") {
    std::string line = "2024-06-01 12:00:00 INFO";
    auto result = parseLogLine(line);
    REQUIRE_FALSE(result.has_value());
}

TEST_CASE("parseLogLine correctly parses valid log line", "[parser]") {
    std::string line = "2024-06-01 12:00:00 INFO Application started";
    auto result = parseLogLine(line);
    REQUIRE(result.has_value());
    REQUIRE(result->date == "2024-06-01");
    REQUIRE(result->time == "12:00:00");
    REQUIRE(result->level == LogLevel::INFO);
    REQUIRE(result->message == "Application started");
}

TEST_CASE("parseLogLine returns nullopt for invalid log line", "[parser]") {
    std::string line = "Invalid log line without proper format";
    auto result = parseLogLine(line);
    REQUIRE_FALSE(result.has_value());
}

TEST_CASE("parseLogFile parses a valid log file", "[parser]") {
    std::string filename = "test_log.txt";
    std::ofstream outFile(filename);
    outFile << "2024-06-01 12:00:00 INFO Application started\n";
    outFile << "2024-06-01 12:01:00 WARN Low disk space\n";
    outFile << "2024-06-01 12:02:00 ERROR NullPointerException\n";
    outFile.close();

    auto entries = parseLogFile(filename);
    REQUIRE(entries.size() == 3);
    REQUIRE(entries[0].level == LogLevel::INFO);
    REQUIRE(entries[1].level == LogLevel::WARN);
    REQUIRE(entries[2].level == LogLevel::ERROR);
    std::remove(filename.c_str());
}

TEST_CASE("parseLogFile returns empty vector for non-existent file", "[parser]") {
    std::string filename = "non_existent_log.txt";
    auto entries = parseLogFile(filename);
    REQUIRE(entries.empty());
}

TEST_CASE("parseLogFile returns empty vector for empty file", "[parser]") {
    std::string filename = "empty_log.txt";
    {
        std::ofstream outFile(filename);
    }
    auto entries = parseLogFile(filename);
    REQUIRE(entries.empty());
    std::remove(filename.c_str());
}