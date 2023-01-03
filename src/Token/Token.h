#pragma once
#include "./TokenType.h"
#include <string>

namespace token
{
    class Token
    {
    public:
        explicit Token(type::TokenType tokenType, size_t position, std::string  data);
        [[nodiscard]] type::TokenType GetType() const;
        [[nodiscard]] size_t GetPos() const;
        [[nodiscard]] std::string GetData() const;
    private:
        type::TokenType m_tokenType;
        size_t m_position;
        std::string m_data;
    };
}