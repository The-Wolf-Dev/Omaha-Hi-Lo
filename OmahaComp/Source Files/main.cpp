#include <fstream>
#include <string>

#include "../Header Files/Poker.h"

int main()
{	
	std::ifstream inputFile("../../../../input.txt");

	if(!inputFile) {
		std::cerr << "Error: Couldn't open the file " << "\n";
		return 1;
	}

	std::string inputLine{};
	while (std::getline(inputFile, inputLine))
	{
		//std::getline(inputFile, inputLine);
		std::string handASetup = inputLine.substr(6, 11);
		std::string handBSetup = inputLine.substr(24, 11);
		std::string boardSetup = inputLine.substr(42, 14);
		Poker poker(handASetup, handBSetup, boardSetup);
		//std::cout << std::endl;
		poker.findWinner();
	}

	return 0;
}
