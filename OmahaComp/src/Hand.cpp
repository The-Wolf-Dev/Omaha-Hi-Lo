#include <iostream>

#include <Hand.h>
#include <Combinations.h>
#include <Checker.h>
#include <Tools.h>

Hand::Hand(const std::vector<Card> &handSetup) 
	: m_cards{ handSetup } {
}

HighHand Hand::getHighHand() const {
	return m_checker.getHighHand();
}

LowHand Hand::getLowHand() const {
	return m_checker.getLowHand();
}

void Hand::findHiLoHand(const Board& board) {
	const auto boardCards = board.getCards();
	HighHandRank highHandRank = HighHandRank::None;
	std::vector<Card> cards, twoCards, threeCards;
	Combinations<Card> handComb(m_cards, PAIR_FROM_HAND), boardComb(boardCards, THREE_FROM_BOARD);

	cards.reserve(HILO_HAND_SIZE);
	while (handComb.generateCombination(twoCards))
	{
		while (boardComb.generateCombination(threeCards)) {
			cards.assign(twoCards.begin(), twoCards.end());
			cards.insert(cards.end(), threeCards.begin(), threeCards.end());

			m_checker.update(cards);

			cards.clear();
		}
	}
}