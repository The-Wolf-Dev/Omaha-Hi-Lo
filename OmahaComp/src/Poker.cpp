#include <string>
#include <iomanip>

#include <Poker.h>
#include <Tools.h>

Poker::Poker(const std::vector<Card>& handASetup, const std::vector<Card>& handBSetup, const std::vector<Card>& boardSetup)
	: m_handA{ handASetup }, m_handB{ handBSetup }, m_board{ boardSetup } {
}

Poker::winpair_t Poker::getWinner() {
	m_handA.findHiLoHand(m_board);
	m_handB.findHiLoHand(m_board);

	std::cout << "HandA: Hi " << std::setw(15) << highHandRankToString(m_handA.getHighHand().getRank()) << " ";
	for (const auto& card : m_handA.getHighHand().getCards())
	{
		for (size_t i{ 0ULL }; i < card.second; ++i)
		{
			std::cout << cardRankToChar(card.first);
		}
	}
	std::cout << " Lo ";
	if (m_handA.getLowHand().isQualified()) {
		for (const auto& card : m_handA.getLowHand().getCards())
		{
			for (size_t i{ 0ULL }; i < card.second; ++i)
			{
				std::cout << cardRankToChar(card.first);
			}
		}
	}
	else std::cout << "No hand qualified for Low";
	std::cout << "\nHandB: Hi " << std::setw(15) << highHandRankToString(m_handB.getHighHand().getRank()) << " ";
	for (const auto& card : m_handB.getHighHand().getCards())
	{
		for (size_t i{ 0ULL }; i < card.second; ++i)
		{
			std::cout << cardRankToChar(card.first);
		}
	}
	std::cout << " Lo ";
	if (m_handB.getLowHand().isQualified()) {
		for (const auto& card : m_handB.getLowHand().getCards())
		{
			for (size_t i{ 0ULL }; i < card.second; ++i)
			{
				std::cout << cardRankToChar(card.first);
			}
		}
	}
	else std::cout << "No hand qualified for Low";
	std::cout << "\n\n";
	return { getHiWinner(), getLoWinner() };
}

Poker::hipair_t Poker::getHiWinner() const {
	auto handAHiRank = m_handA.getHighHand().getRank();
	auto handBHiRank = m_handB.getHighHand().getRank();
	auto handAHiCards = m_handA.getHighHand().getCards();
	auto handBHiCards = m_handB.getHighHand().getCards();

	if (handAHiRank == handBHiRank) {
		if (handAHiCards == handBHiCards) {
			// Split
			return { "Split Pot", handAHiRank };
		}
		else if (handAHiCards < handBHiCards) {
			//HandB wins
			return { "HandB wins", handBHiRank };
		}
		else {
			//HandA wins
			return { "HandA wins", handAHiRank };
		}
	}
	else if (handAHiRank > handBHiRank) {
		//HandA wins
		return { "HandA wins", handAHiRank };
	}
	else {
		//HandB wins
		return { "HandB wins", handBHiRank };
	}
}

Poker::lopair_t Poker::getLoWinner() const {
	auto handALoQualified = m_handA.getLowHand().isQualified();
	auto handBLoQualified = m_handB.getLowHand().isQualified();
	auto handALoCards = m_handA.getLowHand().getCards();
	auto handBLoCards = m_handB.getLowHand().getCards();

	if (handALoQualified && handBLoQualified) {
		if (handALoCards == handBLoCards) {
			// Split
			return { "Split Pot", handBLoCards };
		}
		else if (handALoCards < handBLoCards) {
			//HandA wins
			return { "HandA wins", handALoCards };
		}
		else {
			//HandB wins
			return { "HandB wins", handBLoCards };
		}
	}
	else if (handALoQualified && !handBLoQualified) {
		//HandA wins
		return { "HandA wins", handALoCards };
	}
	else if (!handALoQualified && handBLoQualified) {
		//HandB wins
		return { "HandB wins", handBLoCards };
	}
	else {
		// No hand qualified
		return { "No hand qualified for Low", {} };
	}
}