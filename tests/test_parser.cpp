#include <catch2/catch_test_macros.hpp>
#include <fstream>
#include <cstdio>
#include <string>
#include "parser.hpp"
#include "log_entry.hpp"

TEST_CASE("parseLogLine returns nullopt for empty line", "[parser]") 
{
    std::string line = "";
    auto result = parseLogLine(line);

    REQUIRE_FALSE(result.has_value());
}

TEST_CASE("parseLogLine returns nullopt for incomplete line", "[parser]") 
{
    std::string line = "2024-06-01 12:00:00 INFO";
    auto result = parseLogLine(line);

    REQUIRE_FALSE(result.has_value());
}

TEST_CASE("parseLogLine correctly parses valid log line", "[parser]") 
{
    std::string line = "2024-06-01 12:00:00 INFO Application started";
    auto result = parseLogLine(line);

    REQUIRE(result.has_value());
    REQUIRE(result->date == "2024-06-01");
    REQUIRE(result->time == "12:00:00");
    REQUIRE(result->level == LogLevel::INFO);
    REQUIRE(result->message == "Application started");
}

TEST_CASE("parseLogLine accepts WARNING and legacy WARN levels", "[parser]") 
{
    auto warning = parseLogLine("2024-06-01 12:00:00 WARNING Disk usage high");
    auto warn = parseLogLine("2024-06-01 12:01:00 WARN Low disk space");

    REQUIRE(warning.has_value());
    REQUIRE(warning->level == LogLevel::WARN);
    REQUIRE(warn.has_value());
    REQUIRE(warn->level == LogLevel::WARN);
}

TEST_CASE("parseLogFile parses a valid log file", "[parser]") 
{
    std::string filename = "test_log.txt";
    std::ofstream outFile(filename);
    outFile << "2024-06-01 12:00:00 INFO Application started\n";
    outFile << "2024-06-01 12:01:00 WARN Low disk space\n";
    outFile << "2024-06-01 12:02:00 ERROR NullPointerException\n";
    outFile.close();

    auto entries = parseLogFile(filename);

    REQUIRE(entries.has_value());
    REQUIRE(entries->size() == 3);
    REQUIRE((*entries)[0].level == LogLevel::INFO);
    REQUIRE((*entries)[1].level == LogLevel::WARN);
    REQUIRE((*entries)[2].level == LogLevel::ERROR);

    std::remove(filename.c_str());
}

TEST_CASE("parseLogFile returns nullopt for non-existent file", "[parser]") 
{
    std::string filename = "non_existent_log.txt";
    auto entries = parseLogFile(filename);

    REQUIRE_FALSE(entries.has_value());
}

TEST_CASE("parseLogFile returns empty vector for empty file", "[parser]") 
{
    std::string filename = "empty_log.txt";
    {
        std::ofstream outFile(filename);
    }
    auto entries = parseLogFile(filename);

    REQUIRE(entries.has_value());
    REQUIRE(entries->empty());

    std::remove(filename.c_str());
}

TEST_CASE("parseLogLine keeps unrecognized level as UNKNOWN", "[parser]") 
{
    auto result = parseLogLine("2026-07-11 10:22:00 DEBUG Cache miss on key user:42");

    REQUIRE(result.has_value());
    REQUIRE(result->level == LogLevel::UNKNOWN);
    REQUIRE(result->message == "Cache miss on key user:42");
}

TEST_CASE("parseLogLine still rejects structurally broken lines", "[parser]") 
{
    REQUIRE_FALSE(parseLogLine("bad malformed line").has_value());
    REQUIRE_FALSE(parseLogLine("").has_value());
    REQUIRE_FALSE(parseLogLine("2024-06-01 12:00:00 INFO").has_value());
}