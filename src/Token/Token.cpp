#include "Token.h"

#include <utility>

token::Token::Token(token::type::TokenType tokenType, size_t position, std::string data)
    : m_tokenType(tokenType)
    , m_position(position)
    , m_data(std::move(data))
{
}

token::type::TokenType token::Token::GetType() const
{
    return m_tokenType;
}

size_t token::Token::GetPos() const
{
    return m_position;
}

std::string token::Token::GetData() const
{
    return m_data;
}
