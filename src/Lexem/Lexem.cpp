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
}

namespace lexem
{
    using Handler = std::function<bool(const std::string&)>;

    const std::map<LexemType, Handler> associations = {
            {LexemType::KEYWORD, checkKeyword},
            {LexemType::IDENTIFIER, checkIdentifier},
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