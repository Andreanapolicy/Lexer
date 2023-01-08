#pragma once
#include <string>

namespace lexem
{
    enum class LexemType
    {
        IDENTIFIER,
        KEYWORD,
        NUMBER,
        SEPARATOR,
        PLUS,
        MINUS,
        MULTIPLICATION,
        DIVISION,
        ASSIGNMENT,
        STRING,
        ERROR
    };

    LexemType GetLexemType(const std::string& data);
}