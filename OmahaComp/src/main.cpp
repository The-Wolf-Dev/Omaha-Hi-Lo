#include <string>
#include <fstream>

#include <Poker.h>
#include <Tools.h>

int main(int argc, char* argv[])
{	
	std::ifstream inputFile(argv[1]);
	std::ofstream outputFile(argv[2]);

	std::string inputLine{};
	while (std::getline(inputFile, inputLine))
	{
		const auto handASetup{ cardSetupToVector(inputLine.substr(6, 11)) };
		const auto handBSetup{ cardSetupToVector(inputLine.substr(24, 11)) };
		const auto boardSetup{ cardSetupToVector(inputLine.substr(42, 14)) };
		Poker poker(handASetup, handBSetup, boardSetup);

		auto winner = poker.getWinner();
		auto hihand = winner.first;
		auto lohand = winner.second;
		outputFile << inputLine << std::endl;
		outputFile << "=> " << hihand.first << " Hi (" << highHandRankToString(hihand.second) << "); ";
		if (lohand.second.empty()) {
			outputFile << lohand.first;
		}
		else {
			outputFile << lohand.first << " Lo (" << lohand.second << ")";
		}
		outputFile << std::endl << std::endl;
	}
	return 0;
}
