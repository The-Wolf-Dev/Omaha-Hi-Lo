#include <iostream>

#include <Hand.h>
#include <Combinations.h>
#include <Checker.h>
#include <Tools.h>

Hand::Hand(std::string handSetup) 
	: m_hasLowHand{ false } {
	for (size_t i{ 0U }, end{ handSetup.length() }; i < end; ++i)
	{
		if (i % 3 == 0) {
			m_cards.emplace_back(parseRank(handSetup[i]), parseSuit(handSetup[i + 1U]));
		}
	}
}

HighHand Hand::getHighHand() const {
	return highHand;
}

std::vector<Card> Hand::getLowHand() const {
	return m_lowHandCards;
}

void Hand::findHiLoHand(const Board& board) {
	const auto boardCards = board.getCards();
	HighHandRank highHandRank = HighHandRank::None;
	std::vector<Card> cards, twoCards, threeCards;
	Checker checker;

	Combinations<Card> handComb(m_cards, PAIR_FROM_HAND), boardComb(boardCards, THREE_FROM_BOARD);

	cards.reserve(HILO_HAND_SIZE);
	while (handComb.generateCombination(twoCards))
	{
		while (boardComb.generateCombination(threeCards)) {
			cards.assign(twoCards.begin(), twoCards.end());
			cards.insert(cards.end(), threeCards.begin(), threeCards.end());
			
			//highHandRank = checkHighHandCards(cards);
			//checkHighHandRank(highHandRank, cards);
			//checkLowHandCards(cards);
			std::sort(cards.begin(), cards.end(), std::greater<Card>());
			checker.validate(cards);

			cards.clear();
		}
	}
	highHand = checker.getHighHand();
}

void Hand::checkLowHandCards(std::vector<Card>& cards) {
	auto uniqueCardsCount = std::unique(cards.begin(), cards.end()) - cards.begin();
	if (uniqueCardsCount < HILO_HAND_SIZE) return;

	auto aceCard = findHighAce(cards);
	if (aceCard != cards.end()) makeLowAce(aceCard);
	std::sort(cards.begin(), cards.end());

	auto notSuitableCard = findNotSuitableCard(cards);
	if (notSuitableCard != cards.cend()) return;

	if (m_lowHandCards.empty() || cards < m_lowHandCards) {
		m_lowHandCards.assign(cards.begin(), cards.end());
		std::reverse(m_lowHandCards.begin(), m_lowHandCards.end());
		m_hasLowHand = true;
	}
}

//HighHandRank Hand::checkHighHandCards(std::vector<Card>& highHandCards) {
//	std::sort(highHandCards.begin(), highHandCards.end(), std::greater<Card>());
//	Checker checker;
//	
//	checker.validate(highHandCards);
//}

//void Hand::checkHighHandRank(const HighHandRank& highHandRank, const std::vector<Card>& highHandCards) {
//	if (m_maxHighHandRank < highHandRank) {
//		m_maxHighHandRank = highHandRank;
//		m_maxHighHandCards.assign(highHandCards.begin(), highHandCards.end());
//	}
//	else if (m_maxHighHandRank == highHandRank && m_maxHighHandCards < highHandCards) {
//		m_maxHighHandCards.assign(highHandCards.begin(), highHandCards.end());
//	}
//}