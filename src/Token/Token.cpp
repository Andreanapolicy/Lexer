#include "Token.h"

#include <utility>

namespace token
{
    Token::Token(type::TokenType tokenType, size_t position, std::string data)
            : m_tokenType(tokenType)
            , m_position(position)
            , m_data(std::move(data))
    {
    }

    type::TokenType Token::GetType() const
    {
        return m_tokenType;
    }

    size_t Token::GetPos() const
    {
        return m_position;
    }

    std::string Token::GetData() const
    {
        return m_data;
    }
}