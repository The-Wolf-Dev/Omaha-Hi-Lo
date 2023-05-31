#include <iostream>
#include <algorithm>
#include <functional>

#include <Hand.h>
#include <Combinations.h>

void removeDuplicates(std::vector<Card>& vec);
bool changeAceWeight(std::vector<Card>& vec, std::vector<Card>::iterator& It);

auto findHighAce(std::vector<Card>& vec) {
	return std::find(vec.begin(), vec.end(), (int)CardConst::HIGH_HAND_ACE);
}

auto findNotSuitableCard(std::vector<Card>& vec) {
	return std::find_if(vec.cbegin(), vec.cend(),
		[](const Card& card) { return card > (int)CardConst::LOW_HAND_MAX_RANK; }); //std::greater<Card>((int)CardConst::LOW_HAND_MAX_RANK, std::placeholders::_1)
}

Hand::Hand(std::string handSetup) 
	: m_maxHighHandRank{ HighHand::None }, m_hasLowHand{ false } {
	for (size_t i{ 0U }, end{ handSetup.length() }; i < end; ++i)
	{
		if (i % 3 == 0) {
			m_cards.emplace_back(handSetup[i], handSetup[i+1]);
		}
	}
	std::sort(m_cards.begin(), m_cards.end(), std::greater<Card>());
}

std::string Hand::getHighHand() const {
	switch (m_maxHighHandRank)
	{
	case HighHand::StraightFlush: return "Straight Flush";
	case HighHand::FourOfAKind: return "4-of-a-Kind";
	case HighHand::FullHouse: return "Full House";
	case HighHand::Flush: return "Flush";
	case HighHand::Straight: return "Straight";
	case HighHand::ThreeOfAKind: return "3-of-a-Kind";
	case HighHand::TwoPair: return "Two Pair";
	case HighHand::OnePair: return "One Pair";
	case HighHand::HighCard: return "High Card";
	default:
		return "Unknown HighHand";
	}
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
	//std::copy(boardCards.begin(), boardCards.end(), std::back_inserter(m_lowHandCards));
	
	removeDuplicates(m_lowHandCards);
	if (m_lowHandCards.size() < (int)CardConst::LOW_HAND_SIZE) return;

	auto aceCard = findHighAce(m_lowHandCards);
	changeAceWeight(m_lowHandCards, aceCard);
	std::sort(m_lowHandCards.begin(), m_lowHandCards.end());

	//cutting off unnecessary elements (only 5 necessary elements remain)
	m_lowHandCards.erase(m_lowHandCards.begin() + (int)CardConst::LOW_HAND_SIZE, m_lowHandCards.end());

	auto notSuitableCard = findNotSuitableCard(m_lowHandCards);
	if (notSuitableCard != m_lowHandCards.cend()) return;

	// reverse to correctly display the sequence of cards
	std::reverse(m_lowHandCards.begin(), m_lowHandCards.end());

	m_hasLowHand = true;
}

//  not a member function!!!
void removeDuplicates(std::vector<Card>& vec) {
	auto last = std::unique(vec.begin(), vec.end());
	vec.erase(last, vec.end());
}

bool changeAceWeight(std::vector<Card>& vec, std::vector<Card>::iterator & It) {
	if (It != vec.end()) {
		(*It).setWeight((int)CardConst::LOW_HAND_ACE);
		return true;
	}
	else return false;
}

void Hand::checkHighHandRank(const HighHand& highHandRank, const std::vector<Card>& highHandCards) {
	if (m_maxHighHandRank < highHandRank) {
		m_maxHighHandRank = highHandRank;
		m_maxHighHandCards.assign(highHandCards.begin(), highHandCards.end());
	}
}

HighHand Hand::checkHighHandCards(std::vector<Card>& highHandCards) {
	std::sort(highHandCards.begin(), highHandCards.end(), std::greater<Card>());
	if (isStraightFlush(highHandCards)) {
		return HighHand::StraightFlush;
	} 
	else if(is4OfAKind(highHandCards)) {
		return HighHand::FourOfAKind;
	}
	else if (isFullHouse(highHandCards)) {
		return HighHand::FullHouse;
	}
	else if (isFlush(highHandCards)) {
		return HighHand::Flush;
	}
	else if (isStraight(highHandCards)) {
		return HighHand::Straight;
	}
	else if (is3OfAKind(highHandCards)) {
		return HighHand::ThreeOfAKind;
	}
	else if (isTwoPair(highHandCards)) {
		return HighHand::TwoPair;
	}
	else if (isOnePair(highHandCards)) {
		return HighHand::OnePair;
	}
	else {
		return HighHand::HighCard;
	}
}

bool Hand::isStraightFlush(const std::vector<Card>& highHandCards) const {
	if (isStraight(highHandCards) && isFlush(highHandCards)) return true;
	else return false;
}

bool Hand::is4OfAKind(const std::vector<Card>& highHandCards) const {
	//Check if any 4 sequential cards of the same rank
	for (size_t i{ 0U }, end{ highHandCards.size() - 3U }; i < end; ++i)
	{
		if (highHandCards[i] == highHandCards[i + 1U] 
			&& highHandCards[i + 1U] == highHandCards[i + 2U]
			&& highHandCards[i + 2U] == highHandCards[i + 3U]) {
			return true;
		}
	}
	return false;
}

bool Hand::isFullHouse(const std::vector<Card>& highHandCards) const {
	// if first 3 elements are equal, then if last 2 elemets are equal, it's Full House
	if (highHandCards[0] == highHandCards[1]
		&& highHandCards[1] == highHandCards[2]) {
		if (highHandCards[3] == highHandCards[4]) {
			return true;
		}
	}
	// if first 2 elements are equal, then if last 3 elemets are equal, it's Full House
	else if (highHandCards[0] == highHandCards[1]) {
		if (highHandCards[2] == highHandCards[3]
			&& highHandCards[3] == highHandCards[4]) {
			return true;
		}
	}
	return false;
}

bool Hand::isFlush(const std::vector<Card>& highHandCards) const {
	//if suits of two cards are not equal, then it's not Flush
	for (size_t i{ 0 }, end{ highHandCards.size() - 1U }; i < end; ++i) {
		if (highHandCards[i].getSuit() != highHandCards[i + 1U].getSuit()) return false;
	}
	return true;
}

bool Hand::isStraight(const std::vector<Card>& highHandCards) const {
	//if weight of one element isn't equal to weight of next element then it's not Straight
	//exception: A5432 because A has a weight equal to 14
	for (size_t i{ 0U }, end{ highHandCards.size() - 1U }; i < end; ++i)
	{
		if (i == 0U && highHandCards[i].getRank() == 'A' && highHandCards[i + 1U].getRank() == '5') continue;
		if (highHandCards[i].getWeight() != highHandCards[i + 1U].getWeight() + 1U) return false;
	}
	return true;
}

bool Hand::is3OfAKind(const std::vector<Card>& highHandCards) const {
	//Check if any 3 sequential cards of the same suit
	for (size_t i{ 0 }, end{ highHandCards.size() - 2 }; i < end; ++i)
	{
		if (highHandCards[i] == highHandCards[i + 1U]
			&& highHandCards[i + 1U] == highHandCards[i + 2U]) {
			return true;
		}
	}
	return false;
}

bool Hand::isTwoPair(const std::vector<Card>& highHandCards) const {
	for (size_t i{ 0U }, end{ highHandCards.size() - 3U }; i < end; ++i)
	{
		for (size_t j{ i + 2 }, end2{ highHandCards.size() - 1U }; j < end2; ++j)
		{
			if (highHandCards[i] == highHandCards[i + 1U]
				&& highHandCards[j] == highHandCards[j + 1U]) return true;
		}
	}
	return false;
}

bool Hand::isOnePair(const std::vector<Card>& highHandCards) const {
	for (size_t i{ 0U }, end{ highHandCards.size() - 1U }; i < end; ++i)
	{
		if (highHandCards[i] == highHandCards[i + 1U]) return true;
	}
	return false;
}