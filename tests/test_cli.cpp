#include <catch2/catch_test_macros.hpp>

#include "cli.hpp"

TEST_CASE("parseArguments accepts input file", "[cli]")
{
    char arg0[] = "cpp_log_analyzer";
    char arg1[] = "sample.log";

    char* argv[] = {arg0, arg1, nullptr};

    auto result = parseArguments(2, argv);

    REQUIRE(result.has_value());
    REQUIRE(result->inputFile == "sample.log");
    REQUIRE(result->topErrors == 3);
    REQUIRE_FALSE(result->levelFilter.has_value());
    REQUIRE_FALSE(result->exportFile.has_value());
}

TEST_CASE("parseArguments rejects invalid top-errors value", "[cli]")
{
    char arg0[] = "cpp_log_analyzer";
    char arg1[] = "sample.log";
    char arg2[] = "--top-errors";
    char arg3[] = "3abc";

    char* argv[] = {arg0, arg1, arg2, arg3, nullptr};

    auto result = parseArguments(4, argv);

    REQUIRE_FALSE(result.has_value());
}

TEST_CASE("parseArguments rejects decimal top-errors value", "[cli]")
{
    char arg0[] = "cpp_log_analyzer";
    char arg1[] = "sample.log";
    char arg2[] = "--top-errors";
    char arg3[] = "3.9";

    char* argv[] = {arg0, arg1, arg2, arg3, nullptr};

    auto result = parseArguments(4, argv);

    REQUIRE_FALSE(result.has_value());
}

TEST_CASE("parseArguments rejects non-numeric top-errors value", "[cli]")
{
    char arg0[] = "cpp_log_analyzer";
    char arg1[] = "sample.log";
    char arg2[] = "--top-errors";
    char arg3[] = "abc";

    char* argv[] = {arg0, arg1, arg2, arg3, nullptr};

    auto result = parseArguments(4, argv);

    REQUIRE_FALSE(result.has_value());
}

TEST_CASE("parseArguments rejects empty top-errors value", "[cli]")
{
    char arg0[] = "cpp_log_analyzer";
    char arg1[] = "sample.log";
    char arg2[] = "--top-errors";
    char arg3[] = "";

    char* argv[] = {arg0, arg1, arg2, arg3, nullptr};

    auto result = parseArguments(4, argv);

    REQUIRE_FALSE(result.has_value());
}

TEST_CASE("parseArguments rejects overflowing top-errors value", "[cli]")
{
    char arg0[] = "cpp_log_analyzer";
    char arg1[] = "sample.log";
    char arg2[] = "--top-errors";
    char arg3[] = "999999999999999999999999999999";

    char* argv[] = {arg0, arg1, arg2, arg3, nullptr};

    auto result = parseArguments(4, argv);

    REQUIRE_FALSE(result.has_value());
}

TEST_CASE("parseArguments rejects zero top-errors value", "[cli]")
{
    char arg0[] = "cpp_log_analyzer";
    char arg1[] = "sample.log";
    char arg2[] = "--top-errors";
    char arg3[] = "0";

    char* argv[] = {arg0, arg1, arg2, arg3, nullptr};

    auto result = parseArguments(4, argv);

    REQUIRE_FALSE(result.has_value());
}

TEST_CASE("parseArguments rejects negative top-errors value", "[cli]")
{
    char arg0[] = "cpp_log_analyzer";
    char arg1[] = "sample.log";
    char arg2[] = "--top-errors";
    char arg3[] = "-1";

    char* argv[] = {arg0, arg1, arg2, arg3, nullptr};

    auto result = parseArguments(4, argv);

    REQUIRE_FALSE(result.has_value());
}

TEST_CASE("parseArguments accepts valid top-errors value", "[cli]")
{
    char arg0[] = "cpp_log_analyzer";
    char arg1[] = "sample.log";
    char arg2[] = "--top-errors";
    char arg3[] = "2";

    char* argv[] = {arg0, arg1, arg2, arg3, nullptr};

    auto result = parseArguments(4, argv);

    REQUIRE(result.has_value());
    REQUIRE(result->topErrors == 2);
}

TEST_CASE("parseArguments rejects top-errors value with plus sign", "[cli]")
{
    char arg0[] = "cpp_log_analyzer";
    char arg1[] = "sample.log";
    char arg2[] = "--top-errors";
    char arg3[] = "+3";

    char* argv[] = {arg0, arg1, arg2, arg3, nullptr};

    auto result = parseArguments(4, argv);

    REQUIRE_FALSE(result.has_value());
}

TEST_CASE("parseArguments rejects top-errors value with leading space", "[cli]")
{
    char arg0[] = "cpp_log_analyzer";
    char arg1[] = "sample.log";
    char arg2[] = "--top-errors";
    char arg3[] = " 3";

    char* argv[] = {arg0, arg1, arg2, arg3, nullptr};

    auto result = parseArguments(4, argv);

    REQUIRE_FALSE(result.has_value());
}

TEST_CASE("parseArguments rejects missing level value", "[cli]")
{
    char arg0[] = "cpp_log_analyzer";
    char arg1[] = "sample.log";
    char arg2[] = "--level";

    char* argv[] = {arg0, arg1, arg2, nullptr};

    auto result = parseArguments(3, argv);

    REQUIRE_FALSE(result.has_value());
}

TEST_CASE("parseArguments rejects missing top-errors value", "[cli]")
{
    char arg0[] = "cpp_log_analyzer";
    char arg1[] = "sample.log";
    char arg2[] = "--top-errors";

    char* argv[] = {arg0, arg1, arg2, nullptr};

    auto result = parseArguments(3, argv);

    REQUIRE_FALSE(result.has_value());
}

TEST_CASE("parseArguments rejects missing export value", "[cli]")
{
    char arg0[] = "cpp_log_analyzer";
    char arg1[] = "sample.log";
    char arg2[] = "--export";

    char* argv[] = {arg0, arg1, arg2, nullptr};

    auto result = parseArguments(3, argv);

    REQUIRE_FALSE(result.has_value());
}

TEST_CASE("parseArguments rejects unknown argument", "[cli]")
{
    char arg0[] = "cpp_log_analyzer";
    char arg1[] = "sample.log";
    char arg2[] = "--bogus";

    char* argv[] = {arg0, arg1, arg2, nullptr};

    auto result = parseArguments(3, argv);

    REQUIRE_FALSE(result.has_value());
}

TEST_CASE("parseArguments rejects missing input file", "[cli]")
{
    char arg0[] = "cpp_log_analyzer";

    char* argv[] = {arg0, nullptr};

    auto result = parseArguments(1, argv);

    REQUIRE_FALSE(result.has_value());
}

TEST_CASE("parseArguments accepts level option", "[cli]")
{
    char arg0[] = "cpp_log_analyzer";
    char arg1[] = "sample.log";
    char arg2[] = "--level";
    char arg3[] = "ERROR";

    char* argv[] = {arg0, arg1, arg2, arg3, nullptr};

    auto result = parseArguments(4, argv);

    REQUIRE(result.has_value());
    REQUIRE(result->levelFilter.has_value());
    REQUIRE(*result->levelFilter == "ERROR");
}

TEST_CASE("parseArguments accepts export option", "[cli]")
{
    char arg0[] = "cpp_log_analyzer";
    char arg1[] = "sample.log";
    char arg2[] = "--export";
    char arg3[] = "out.csv";

    char* argv[] = {arg0, arg1, arg2, arg3, nullptr};

    auto result = parseArguments(4, argv);

    REQUIRE(result.has_value());
    REQUIRE(result->exportFile.has_value());
    REQUIRE(*result->exportFile == "out.csv");
}

TEST_CASE("parseArguments accepts all options together", "[cli]")
{
    char arg0[] = "cpp_log_analyzer";
    char arg1[] = "sample.log";
    char arg2[] = "--level";
    char arg3[] = "ERROR";
    char arg4[] = "--top-errors";
    char arg5[] = "5";
    char arg6[] = "--export";
    char arg7[] = "out.csv";

    char* argv[] = {
        arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, nullptr
    };

    auto result = parseArguments(8, argv);

    REQUIRE(result.has_value());
    REQUIRE(result->inputFile == "sample.log");
    REQUIRE(result->levelFilter.has_value());
    REQUIRE(*result->levelFilter == "ERROR");
    REQUIRE(result->topErrors == 5);
    REQUIRE(result->exportFile.has_value());
    REQUIRE(*result->exportFile == "out.csv");
}

TEST_CASE("parseArguments accepts options in reverse order", "[cli]")
{
    char arg0[] = "cpp_log_analyzer";
    char arg1[] = "sample.log";
    char arg2[] = "--export";
    char arg3[] = "out.csv";
    char arg4[] = "--top-errors";
    char arg5[] = "5";
    char arg6[] = "--level";
    char arg7[] = "ERROR";

    char* argv[] = {
        arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, nullptr
    };

    auto result = parseArguments(8, argv);

    REQUIRE(result.has_value());
    REQUIRE(result->inputFile == "sample.log");
    REQUIRE(result->levelFilter.has_value());
    REQUIRE(*result->levelFilter == "ERROR");
    REQUIRE(result->topErrors == 5);
    REQUIRE(result->exportFile.has_value());
    REQUIRE(*result->exportFile == "out.csv");
}

TEST_CASE("parseArguments accepts unknown level value", "[cli]")
{
    char arg0[] = "cpp_log_analyzer";
    char arg1[] = "sample.log";
    char arg2[] = "--level";
    char arg3[] = "NESMYSL";

    char* argv[] = {arg0, arg1, arg2, arg3, nullptr};

    auto result = parseArguments(4, argv);

    REQUIRE(result.has_value());
    REQUIRE(result->levelFilter.has_value());
    REQUIRE(*result->levelFilter == "NESMYSL");
}

TEST_CASE("parseArguments uses last duplicate top-errors value", "[cli]")
{
    char arg0[] = "cpp_log_analyzer";
    char arg1[] = "sample.log";
    char arg2[] = "--top-errors";
    char arg3[] = "2";
    char arg4[] = "--top-errors";
    char arg5[] = "5";

    char* argv[] = {
        arg0, arg1, arg2, arg3, arg4, arg5, nullptr
    };

    auto result = parseArguments(6, argv);

    REQUIRE(result.has_value());
    REQUIRE(result->topErrors == 5);
}

TEST_CASE("parseArguments treats first argument as input file", "[cli]")
{
    char arg0[] = "cpp_log_analyzer";
    char arg1[] = "--level";

    char* argv[] = {arg0, arg1, nullptr};

    auto result = parseArguments(2, argv);

    REQUIRE(result.has_value());
    REQUIRE(result->inputFile == "--level");
}

TEST_CASE("parseArguments accepts flag-looking value after level", "[cli]")
{
    char arg0[] = "cpp_log_analyzer";
    char arg1[] = "sample.log";
    char arg2[] = "--level";
    char arg3[] = "--export";

    char* argv[] = {arg0, arg1, arg2, arg3, nullptr};

    auto result = parseArguments(4, argv);

    REQUIRE(result.has_value());
    REQUIRE(result->levelFilter.has_value());
    REQUIRE(*result->levelFilter == "--export");
}
