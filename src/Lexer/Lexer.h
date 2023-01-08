#pragma once

#include <sstream>
#include <vector>
#include "../Common/Position.h"
#include "../Token/Token.h"

namespace lexer
{
    class Lexer
    {
    public:
        explicit Lexer(std::istream& input);

        token::Token GetToken();

        void OutAllTokens(std::ostream& output);
    private:
        std::istream& m_input;
        Position m_position;
        std::vector<token::Token> tokens;
    };
}