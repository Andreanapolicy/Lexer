#include "Lexem.h"
#include <map>
#include <vector>
#include <functional>

namespace
{
    bool checkKeyword(const std::string& data)
    {
        return data == "int" || data == "float";
    }

    bool checkIdentifier(const std::string& data)
    {
        auto result = std::find_if(data.begin() + 1, data.end(), [](char c) {
            return !(std::isalpha(c) || std::isdigit(c));
        });

        return std::isalpha(data[0]) && result == data.end();
    }

    bool checkString(const std::string& data)
    {
        return data[0] == '\"' && data[data.size() - 1] == '\"';
    }

    bool checkAssigment(const std::string& data)
    {
        return data == "=";
    }

    bool checkDivision(const std::string& data)
    {
        return data == "/";
    }

    bool checkMultiplication(const std::string& data)
    {
        return data == "*";
    }

    bool checkMinus(const std::string& data)
    {
        return data == "-";
    }

    bool checkPlus(const std::string& data)
    {
        return data == "+";
    }

    bool checkSeparator(const std::string& data)
    {
        return data == ";";
    }

    bool checkNumber(const std::string& data)
    {
        bool isFloat = false;
        if (data.empty())
        {
            return false;
        }

        for (auto index = 0; index < data.size(); index++)
        {
            if (std::isdigit(data[index]))
            {
                continue;
            }

            if (data[index] == '.' && isFloat)
            {
                return false;
            }

            if (data[index] == '.' && !isFloat)
            {
                isFloat = true;
                continue;
            }

            if (data.size() > 2 && index == 1 && data[0] == '0' && (data[1] == 'x' || data[1] == 'b' || data[1] == 'e'))
            {
                continue;
            }

            return false;
        }

        return true;
    }
}

namespace lexem
{
    using Handler = std::function<bool(const std::string&)>;

    const std::map<LexemType, Handler> associations = {
		{LexemType::KEYWORD, checkKeyword},
		{LexemType::IDENTIFIER, checkIdentifier},
		{LexemType::ASSIGNMENT, checkAssigment},
		{LexemType::NUMBER, checkNumber},
		{LexemType::SEPARATOR, checkSeparator},
		{LexemType::PLUS, checkPlus},
		{LexemType::MINUS, checkMinus},
		{LexemType::MULTIPLICATION, checkMultiplication},
		{LexemType::DIVISION, checkDivision},
		{LexemType::STRING, checkString},
    };

    LexemType GetLexemType(const std::string& data)
    {
        for (const auto& rule : associations)
        {
            if (rule.second(data))
            {
                return rule.first;
            }
        }

        return LexemType::ERROR;
    }
}