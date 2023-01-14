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

			WHEN("In lexer goes comment with wrong usage")
			{
				input << "//this is a comment";
				auto lexer = std::make_unique<lexer::Lexer>(input);

				THEN("there will be expetion")
				{
					REQUIRE_THROWS_WITH(lexer->Process(), "Error, wrong lexem at pos(1, 0); [...//this...]");
				}
			}
		}
	}

	SECTION("Testing delimiter")
	{
		GIVEN("Lexer dialog, input and output")
		{
			std::stringstream input;
			std::stringstream output;

			auto lexerDialog = std::make_unique<LexerDialog>(output);

			WHEN("In lexer goes only `;`")
			{
				input << ";";
				auto lexer = std::make_unique<lexer::Lexer>(input);
				lexer->Process();

				THEN("List of token will be consist of delimiter")
				{
					std::stringstream intendedOutput;
					intendedOutput << "separator (;) [1, 0]" << std::endl;

					lexerDialog->OutputTokens(lexer->GetAllTokens());
					REQUIRE(output.str() == intendedOutput.str());
				}
			}

			WHEN("In lexer goes only `{}`")
			{
				input << "{" << std::endl << "}";
				auto lexer = std::make_unique<lexer::Lexer>(input);
				lexer->Process();

				THEN("List of token will be consist of 2 delimiter")
				{
					std::stringstream intendedOutput;
					intendedOutput << "separator ({) [1, 0]" << std::endl << "separator (}) [2, 0]" << std::endl;

					lexerDialog->OutputTokens(lexer->GetAllTokens());
					REQUIRE(output.str() == intendedOutput.str());
				}
			}

			WHEN("In lexer goes only `()`")
			{
				input << "(" << std::endl << ")";
				auto lexer = std::make_unique<lexer::Lexer>(input);
				lexer->Process();

				THEN("List of token will be consist of 2 delimiter")
				{
					std::stringstream intendedOutput;
					intendedOutput << "separator (() [1, 0]" << std::endl << "separator ()) [2, 0]" << std::endl;

					lexerDialog->OutputTokens(lexer->GetAllTokens());
					REQUIRE(output.str() == intendedOutput.str());
				}
			}

			WHEN("In lexer goes only `[]`")
			{
				input << "[" << std::endl << "]";
				auto lexer = std::make_unique<lexer::Lexer>(input);
				lexer->Process();

				THEN("List of token will be consist of 2 delimiter")
				{
					std::stringstream intendedOutput;
					intendedOutput << "separator ([) [1, 0]" << std::endl << "separator (]) [2, 0]" << std::endl;

					lexerDialog->OutputTokens(lexer->GetAllTokens());
					REQUIRE(output.str() == intendedOutput.str());
				}
			}
		}
	}

	SECTION("Testing keywords")
	{
		GIVEN("Lexer dialog, input and output")
		{
			std::stringstream input;
			std::stringstream output;

			auto lexerDialog = std::make_unique<LexerDialog>(output);

			WHEN("In lexer goes keyword int")
			{
				input << "int";
				auto lexer = std::make_unique<lexer::Lexer>(input);
				lexer->Process();

				THEN("List of token will be consist of keyword")
				{
					std::stringstream intendedOutput;
					intendedOutput << "keyword (int) [1, 0]" << std::endl;

					lexerDialog->OutputTokens(lexer->GetAllTokens());
					REQUIRE(output.str() == intendedOutput.str());
				}
			}

			WHEN("In lexer goes keyword float")
			{
				input << "float";
				auto lexer = std::make_unique<lexer::Lexer>(input);
				lexer->Process();

				THEN("List of token will be consist of keyword")
				{
					std::stringstream intendedOutput;
					intendedOutput << "keyword (float) [1, 0]" << std::endl;

					lexerDialog->OutputTokens(lexer->GetAllTokens());
					REQUIRE(output.str() == intendedOutput.str());
				}
			}

			WHEN("In lexer goes 2 keywords with delimiter")
			{
				input << "float;" << std::endl << "int;";
				auto lexer = std::make_unique<lexer::Lexer>(input);
				lexer->Process();

				THEN("List of token will be consist of keywords and delimiter")
				{
					std::stringstream intendedOutput;
					intendedOutput
						<< "keyword (float) [1, 0]" << std::endl
						<< "separator (;) [1, 5]" << std::endl
						<< "keyword (int) [2, 0]" << std::endl
						<< "separator (;) [2, 3]" << std::endl;

					lexerDialog->OutputTokens(lexer->GetAllTokens());
					REQUIRE(output.str() == intendedOutput.str());
				}
			}
		}
	}
}