#define CATCH_CONFIG_MAIN

#include "../catch2/catch.hpp"
#include "../src/Lexer/Lexer.h"
#include "../src/utils/LexerDialog/LexerDialog.h"

TEST_CASE("Tests for single usage lexems")
{
	SECTION("Testing comments")
	{
		GIVEN("Lexer dialog, input and output")
		{
			std::stringstream input;
			std::stringstream output;

			auto lexerDialog = std::make_unique<LexerDialog>(output);

			WHEN("In lexer goes single comment with right usage")
			{
				input << "// this is a comment";
				auto lexer = std::make_unique<lexer::Lexer>(input);
				lexer->Process();

				THEN("List of token will be empty")
				{
					std::stringstream intendedOutput;

					lexerDialog->OutputTokens(lexer->GetAllTokens());
					REQUIRE(output.str() == intendedOutput.str());
				}
			}

			WHEN("In lexer goes double comments with right usage")
			{
				input << "// this is a comment" << std::endl
					  << "// and this is too comment";
				auto lexer = std::make_unique<lexer::Lexer>(input);
				lexer->Process();

				THEN("List of token will be empty")
				{
					std::stringstream intendedOutput;

					lexerDialog->OutputTokens(lexer->GetAllTokens());
					REQUIRE(output.str() == intendedOutput.str());
				}
			}
		}
	}
}