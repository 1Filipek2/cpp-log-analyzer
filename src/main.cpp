#include <iostream>

#include "parser.hpp"

int main () {
    std::string line = "2026-03-20 10:42:08 ERROR Database connection failed";

    auto result = parseLogLine(line);

    if (result.has_value()) {
        std::cout << "Date: " << result->date << "\n";
        std::cout << "Time: " << result->time << "\n";
        std::cout << "Level: " << result->level << "\n";
        std::cout << "Message: " << result->message << "\n";
    } else {
        std::cout << "Invalid log line \n";
    }

    return 0;
}