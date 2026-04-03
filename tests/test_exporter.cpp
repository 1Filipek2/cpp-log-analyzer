#include <catch2/catch.hpp>
#include <fstream>

#include "exporter.hpp"

TEST_CASE("exportSummaryCSV should create a valid CSV file", "[exporter]") {
    std::map<std::string, int> levelCounts {
        {"INFO", 10},
        {"WARNING", 5},
        {"ERROR", 3}
    };
    std::vector<std::pair<std::string, int>> topErrors {
        {"NullPointerException", 2},
        {"OutOfMemoryError", 1}
    };
    std::string filename = "test_summary.csv";

    REQUIRE(exportSummaryCsv(filename, levelCounts, topErrors));

    std::ifstream inFile(filename);
    REQUIRE(inFile.is_open());
    std::string content((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    inFile.close();
    std::string expectedHeader = "Level,Count\n";
    std::string expectedInfo = "INFO,10\n";
    std::string expectedWarn = "WARNING,5\n";
    std::string expectedError = "ERROR,3\n";
    std::string expectedErrorHeader = "Error,Count\n";
    std::string expectedNullPointer = "NullPointerException,2\n";
    std::string expectedOutOfMemory = "OutOfMemoryError,1\n";
    REQUIRE(content.find(expectedHeader) != std::string::npos);
    REQUIRE(content.find(expectedInfo) != std::string::npos);
    REQUIRE(content.find(expectedWarn) != std::string::npos);
    REQUIRE(content.find(expectedError) != std::string::npos);
    REQUIRE(content.find(expectedErrorHeader) != std::string::npos);
    REQUIRE(content.find(expectedNullPointer) != std::string::npos);
    REQUIRE(content.find(expectedOutOfMemory) != std::string::npos);
    std::remove(filename.c_str());
}

TEST_CASE("exportSummaryCSV should handle empty data", "[exporter]") {
    std::map<std::string, int> levelCounts;
    std::vector<std::pair<std::string, int>> topErrors;
    std::string filename = "test_empty_summary.csv";

    REQUIRE(exportSummaryCsv(filename, levelCounts, topErrors));
    std::ifstream inFile(filename);
    REQUIRE(inFile.is_open());
    std::string content((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    inFile.close();

    REQUIRE(content.find("Level,Count") != std::string::npos);
    REQUIRE(content.find("Error,Count") != std::string::npos);
    std::remove(filename.c_str());
}