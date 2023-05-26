#pragma once

#include <vector>
#include <string>

#include "Card.h"
#include "Enums.h"
#include "Board.h"

class Hand {
	std::vector<Card> m_cards;
	std::vector<Card> m_highHandCards;
	std::vector<Card> m_maxHighHandCards;
	std::vector<Card> m_lowHandCards;
	HighHand m_highHand;
	HighHand m_maxHighHand;
	bool m_hasLowHand;

	void findHighHand(const std::vector<Card>& boardCards);
	void findLowHand(const std::vector<Card>& boardCards);

	void checkHighHand();
	bool isStraightFlush() const;
	bool is4OfAKind() const;
	bool isFullHouse() const;
	bool isFlush() const;
	bool isStraight() const;
	bool is3OfAKind() const;
	bool isTwoPair() const;
	bool isOnePair() const;
	void assignHighCard(const std::vector<Card>& boardCards);
public:
	Hand(std::string handSetup);
	
	std::string getHighHand() const;
	std::vector<Card> getHighHandCards() const;
	bool hasLowHand() const;
	std::vector<Card> getLowHandCards() const;

	void findHiLoHand(const Board& board);
};