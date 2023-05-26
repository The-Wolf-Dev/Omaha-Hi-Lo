#include <string>
#include <iomanip>

#include "../Header Files/Poker.h"

Poker::Poker(std::string handASetup, std::string handBSetup, std::string boardSetup) 
	: m_handA{ handASetup }, m_handB{ handBSetup }, m_board{ boardSetup } {
}

void Poker::findWinner() {
	m_handA.findHiLoHand(m_board);
	m_handB.findHiLoHand(m_board);
	std::cout << "HandA: Hi " << std::setw(15) << m_handA.getHighHand() << " ";
	for (const auto& card : m_handA.getHighHandCards())
	{
		std::cout << card;
	}
	std::cout << " Lo ";
	if (m_handA.hasLowHand()) {
		for (const auto& card : m_handA.getLowHandCards())
		{
			std::cout << card;
		}
	}
	else std::cout << "No hand qualified for Low";
	std::cout << "\nHandB: Hi " << std::setw(15) << m_handB.getHighHand() << " ";
	for (const auto& card : m_handB.getHighHandCards())
	{
		std::cout << card;
	}
	std::cout << " Lo ";
	if (m_handB.hasLowHand()) {
		for (const auto& card : m_handB.getLowHandCards())
		{
			std::cout << card;
		}
	} else std::cout << "No hand qualified for Low";
	
	std::cout << "\n\n";
}