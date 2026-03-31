#pragma once
#include <stdexcept>
#include <string>

class ParserFatalException : public std::runtime_error {
public:
    explicit ParserFatalException(const std::string& message)
        : std::runtime_error(message) {}
};

