#include <fstream>
#include <iostream>
#include <memory>
#include "src/Lexer/Lexer.h"

namespace
{
struct Args
{
	std::string inputFilename;
};

Args ParseArgs(int argc, char** argv)
{
	if (argc != 2)
	{
		throw std::invalid_argument("invalid parameters");
	}

	return {
		.inputFilename = argv[1]
	};
}
}

int main(int argc, char** argv)
{
	try
	{
		auto const args = ParseArgs(argc, argv);
		std::ifstream input(args.inputFilename);

		if (!input.is_open())
		{
			throw std::runtime_error("Cannot open input file");
		}

        auto lexer = std::make_unique<lexer::Lexer>(input);
        lexer->Process();

        lexer->OutAllTokens(std::cout);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
