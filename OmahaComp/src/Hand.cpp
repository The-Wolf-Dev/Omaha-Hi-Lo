#include <iostream>

#include <Hand.h>
#include <Combinations.h>
#include <Checker.h>
#include <Tools.h>

Hand::Hand(std::string handSetup) 
	: m_maxHighHandRank{ HighHand::None }, m_hasLowHand{ false } {
	for (size_t i{ 0U }, end{ handSetup.length() }; i < end; ++i)
	{
		if (i % 3 == 0) {
			m_cards.emplace_back(handSetup[i], parseSuit(handSetup[i + 1U]));
		}
	}
	std::sort(m_cards.begin(), m_cards.end(), std::greater<Card>());
}

HighHand Hand::getHighHandRank() const {
	return m_maxHighHandRank;
}

std::vector<Card> Hand::getHighHandCards() const {
	return m_maxHighHandCards;
}

bool Hand::hasLowHand() const {
	return m_hasLowHand;
}

std::vector<Card> Hand::getLowHandCards() const {
	return m_lowHandCards;
}

void Hand::findHiLoHand(const Board& board) {
	const auto boardCards = board.getCards();
	findHighHand(boardCards);
	findLowHand(boardCards);
}

void Hand::findHighHand(const std::vector<Card>& boardCards) {
	HighHand highHandRank = HighHand::None;
	std::vector<Card> highHandCards, twoCards, threeCards;

	Combinations<Card> handComb(m_cards, (int)CardConst::PAIR_FROM_HAND), boardComb(boardCards, (int)CardConst::THREE_FROM_BOARD);

	highHandCards.reserve((int)CardConst::HIGH_HAND_SIZE);
	while (handComb.generateCombination(twoCards))
	{
		while (boardComb.generateCombination(threeCards)) {
			highHandCards.insert(highHandCards.end(), twoCards.begin(), twoCards.end());
			highHandCards.insert(highHandCards.end(), threeCards.begin(), threeCards.end());

			highHandRank = checkHighHandCards(highHandCards);
			checkHighHandRank(highHandRank, highHandCards);

			highHandCards.clear();
		}
	}
}

void Hand::findLowHand(const std::vector<Card>& boardCards) {
	m_lowHandCards.reserve(boardCards.size() + m_cards.size());
	m_lowHandCards.assign(m_cards.begin(), m_cards.end());
	m_lowHandCards.insert(m_lowHandCards.end(), boardCards.begin(), boardCards.end());

	removeDuplicates(m_lowHandCards);
	if (m_lowHandCards.size() < (int)CardConst::LOW_HAND_SIZE) return;

	auto aceCard = findHighAce(m_lowHandCards);
	if(aceCard != m_lowHandCards.end()) changeAceWeight(aceCard);
	std::sort(m_lowHandCards.begin(), m_lowHandCards.end());

	//cutting off unnecessary elements (only 5 necessary elements remain)
	m_lowHandCards.erase(m_lowHandCards.begin() + (int)CardConst::LOW_HAND_SIZE, m_lowHandCards.end());

	auto notSuitableCard = findNotSuitableCard(m_lowHandCards);
	if (notSuitableCard != m_lowHandCards.cend()) return;

	// reverse to correctly display the sequence of cards
	std::reverse(m_lowHandCards.begin(), m_lowHandCards.end());

	m_hasLowHand = true;
}

void Hand::checkHighHandRank(const HighHand& highHandRank, const std::vector<Card>& highHandCards) {
	if (m_maxHighHandRank < highHandRank) {
		m_maxHighHandRank = highHandRank;
		m_maxHighHandCards.assign(highHandCards.begin(), highHandCards.end());
	}
	else if (m_maxHighHandRank == highHandRank && m_maxHighHandCards < highHandCards) {
		m_maxHighHandCards.assign(highHandCards.begin(), highHandCards.end());
	}
}

HighHand Hand::checkHighHandCards(std::vector<Card>& highHandCards) {
	std::sort(highHandCards.begin(), highHandCards.end(), std::greater<Card>());
	Checker checker;
	StraightFlushChecker sfchecker;

	for (const auto& c : highHandCards) {
		checker.update(c);
		sfchecker.update(c);
	}

	if (sfchecker.isStraightFlush()) {
		handleExceptionalStraightFlush(highHandCards);
		return HighHand::StraightFlush;
	} 
	else if (checker.is4OfAKind()) {
		return HighHand::FourOfAKind;
	}
	else if (checker.isFullHouse()) {
		return HighHand::FullHouse;
	}
	else if (sfchecker.isFlush()) {
		return HighHand::Flush;
	}
	else if (sfchecker.isStraight()) {
		handleExceptionalStraightFlush(highHandCards);
		return HighHand::Straight;
	}
	else if (checker.is3OfAKind()) {
		return HighHand::ThreeOfAKind;
	}
	else if (checker.isTwoPair()) {
		return HighHand::TwoPair;
	}
	else if (checker.isOnePair()) {
		return HighHand::OnePair;
	}
	else {
		return HighHand::HighCard;
	}
}

void Hand::handleExceptionalStraightFlush(std::vector<Card>& highHandCards) {
	if (!highHandCards.empty()
		&& highHandCards[0].getRank() == 'A' && highHandCards[1].getRank() == '5') {
		highHandCards[0].setWeight(1);
	}
}