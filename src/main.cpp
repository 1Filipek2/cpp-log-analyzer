#include <iostream>
#include <vector>

#include "parser.hpp"

int main () {
    std::vector<LogEntry> entries = parseLogFile("../sample/sample.log");

    std::cout << "Loaded valid entries:" << entries.size() << std::endl;

    for (const auto& entry : entries) {
        std::cout << "Date: " << entry.date << std::endl;
        std::cout << "Time: " << entry.time << std::endl;
        std::cout << "Level: " << entry.level << std::endl;
        std::cout << "Message: " << entry.message << std::endl;
    }
    return 0;
}