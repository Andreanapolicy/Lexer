#pragma once
#include <map>
#include <string>

namespace token::type
{
    enum class TokenType
    {
        IDENTIFIER,
        FLOAT,
        INT,
        BIGINT,
        NUMBER,
        SEPARATOR,
        PLUS,
        MINUS,
        MULTIPLICATION,
        DIVISION,
        ASSIGNMENT,
        STRING,
        END,
    };
}