#include "../Header Files/Hand.h"

#include <iostream>
#include <algorithm>

Hand::Hand(std::string handSetup) 
	: m_highHand{ HighHand::None }, m_maxHighHand{ HighHand::None }, m_hasLowHand{ false } {
	for (size_t i = 0; i < handSetup.length(); i++)
	{
		if (i % 3 == 0) {
			m_cards.emplace_back(handSetup[i], handSetup[i+1]);
		}
	}
	std::sort(m_cards.begin(), m_cards.end(), [](auto l, auto r) { return l > r; });
}

std::string Hand::getHighHand() const {
	switch (m_maxHighHand)
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
	
	for (size_t card1 = 0; card1 < m_cards.size() - 1; card1++)
	{
		for (size_t card2 = card1 + 1; card2 < m_cards.size(); card2++)
		{
			for (size_t card3 = 0; card3 < boardCards.size() - 2; card3++)
			{
				for (size_t card4 = card3 + 1; card4 < boardCards.size() - 1; card4++)
				{
					for (size_t card5 = card4 + 1; card5 < boardCards.size(); card5++)
					{
						m_highHandCards.clear();
						try
						{
							m_highHandCards.push_back(m_cards.at(card1));
							m_highHandCards.push_back(m_cards.at(card2));
							m_highHandCards.push_back(boardCards.at(card3));
							m_highHandCards.push_back(boardCards.at(card4));
							m_highHandCards.push_back(boardCards.at(card5));
						}
						catch (const std::exception& e)
						{
							std::cout << e.what() << std::endl;
						}
						checkHighHand();
						if (m_maxHighHand < m_highHand) {
							m_maxHighHand = m_highHand;
							m_maxHighHandCards.clear();
							std::copy(m_highHandCards.begin(), m_highHandCards.end(), std::back_inserter(m_maxHighHandCards));
						}
					}
				}
			}
		}
	}
	//if High Hand of higher rank isn't found, then pick biggest card from hand and board
	if(m_maxHighHand == HighHand::None) assignHighCard(boardCards);
}

void Hand::findLowHand(const std::vector<Card>& boardCards) {
	std::copy(m_cards.begin(), m_cards.end(), std::back_inserter(m_lowHandCards));
	std::copy(boardCards.begin(), boardCards.end(), std::back_inserter(m_lowHandCards));
	std::sort(m_lowHandCards.begin(), m_lowHandCards.end());

	auto last = std::unique(m_lowHandCards.begin(), m_lowHandCards.end());
	m_lowHandCards.erase(last, m_lowHandCards.end());
	if (m_lowHandCards.size() < cards_constant::LOW_HAND_SIZE) return;

	auto aceCard = std::find(m_lowHandCards.begin(), m_lowHandCards.end(), cards_constant::HIGH_ACE);
	if (aceCard != m_lowHandCards.end()) {
		(*aceCard).setWeight(cards_constant::LOW_ACE);
		//sort m_lowHandCards to move Low Ace to beginning
		std::sort(m_lowHandCards.begin(), m_lowHandCards.end());
	}

	//cutting off unnecessary elements (only 5 necessary elements remain)
	m_lowHandCards.erase(m_lowHandCards.begin() + cards_constant::LOW_HAND_SIZE, m_lowHandCards.end());

	auto notSuitableCard = std::find_if(m_lowHandCards.begin(), m_lowHandCards.end(), 
		[](const Card& card) { return card > cards_constant::MAX_LOW_HAND_RANK; });
	if (notSuitableCard != m_lowHandCards.end()) return;

	std::reverse(m_lowHandCards.begin(), m_lowHandCards.end());

	m_hasLowHand = true;
}

void Hand::checkHighHand() {
	std::sort(m_highHandCards.begin(), m_highHandCards.end(), [](auto l, auto r) { return l > r; });
	if (isStraightFlush()) {
		m_highHand = HighHand::StraightFlush;
	} 
	else if(is4OfAKind()) {
		m_highHand = HighHand::FourOfAKind;
	}
	else if (isFullHouse()) {
		m_highHand = HighHand::FullHouse;
	}
	else if (isFlush()) {
		m_highHand = HighHand::Flush;
	}
	else if (isStraight()) {
		m_highHand = HighHand::Straight;
	}
	else if (is3OfAKind()) {
		m_highHand = HighHand::ThreeOfAKind;
	}
	else if (isTwoPair()) {
		m_highHand = HighHand::TwoPair;
	}
	else if (isOnePair()) {
		m_highHand = HighHand::OnePair;
	}
}

//Assinging biggest cards from hand and board to HighHand
void Hand::assignHighCard(const std::vector<Card>& boardCards) { 
	m_highHandCards.clear();											//clear after loops in Hand::findHighHand
	m_highHand = HighHand::HighCard;
	try
	{
		m_highHandCards.push_back(m_cards.at(0));
		m_highHandCards.push_back(m_cards.at(1));
		m_highHandCards.push_back(boardCards.at(0));
		m_highHandCards.push_back(boardCards.at(1));
		m_highHandCards.push_back(boardCards.at(2));
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

bool Hand::isStraightFlush() const {
	if (isStraight() && isFlush()) return true;
	else return false;
}

bool Hand::is4OfAKind() const {
	//Check if any 4 sequential cards of the same suit
	for (size_t i = 0; i < m_highHandCards.size() - 3; i++)
	{
		try
		{
			if (m_highHandCards.at(i) == m_highHandCards.at(i + 1) 
				&& m_highHandCards.at(i + 1) == m_highHandCards.at(i + 2)
				&& m_highHandCards.at(i + 2) == m_highHandCards.at(i + 3)) {
				return true;
			}
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	return false;
}

bool Hand::isFullHouse() const {
	// if first 3 elements are equal, then if last 2 elemets are equal, it's Full House
	if (m_highHandCards.at(0) == m_highHandCards.at(1)
		&& m_highHandCards.at(1) == m_highHandCards.at(2)) {
		if (m_highHandCards.at(3) == m_highHandCards.at(4)) {
			return true;
		}
	}
	// if first 2 elements are equal, then if last 3 elemets are equal, it's Full House
	else if (m_highHandCards.at(0) == m_highHandCards.at(1)) {
		if (m_highHandCards.at(2) == m_highHandCards.at(3)
			&& m_highHandCards.at(3) == m_highHandCards.at(4)) {
			return true;
		}
	}
	return false;
}

bool Hand::isFlush() const {
	//if suits of two cards are not equal, then it's not Flush
	for (size_t i = 0; i < m_highHandCards.size() - 1; i++) {
		try
		{
			if (m_highHandCards.at(i).getSuit() != m_highHandCards.at(i + 1).getSuit()) return false;
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	return true;
}

bool Hand::isStraight() const {
	//if weight of one element isn't equal to weight of next element then it's not Straight
	//exception: A5432 because A has a weight equal to 14
	for (size_t i = 0; i < m_highHandCards.size()-1; i++)
	{
		try
		{
			if (i == 0 && m_highHandCards.at(i).getRank() == 'A' && m_highHandCards.at(i + 1).getRank() == '5') continue;
			if (m_highHandCards.at(i) != m_highHandCards.at(i + 1) + 1) return false;
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	return true;
}

bool Hand::is3OfAKind() const {
	//Check if any 3 sequential cards of the same suit
	for (size_t i = 0; i < m_highHandCards.size() - 2; i++)
	{
		try
		{
			if (m_highHandCards.at(i) == m_highHandCards.at(i + 1) 
				&& m_highHandCards.at(i + 1) == m_highHandCards.at(i + 2)) {
				return true;
			}
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	return false;
}

bool Hand::isTwoPair() const {
	for (size_t i = 0; i < m_highHandCards.size() - 3; i++)
	{
		for (size_t j = i+2; j < m_highHandCards.size()-1; j++)
		{
			try
			{
				if (m_highHandCards.at(i) == m_highHandCards.at(i + 1)
					&& m_highHandCards.at(j) == m_highHandCards.at(j + 1)) return true;
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
		}
	}
	return false;
}

bool Hand::isOnePair() const {
	for (size_t i = 0; i < m_highHandCards.size() - 1; i++)
	{
		try
		{
			if (m_highHandCards.at(i) == m_highHandCards.at(i + 1)) return true;
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	return false;
}