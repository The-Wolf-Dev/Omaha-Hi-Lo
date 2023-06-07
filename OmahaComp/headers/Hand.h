#ifndef HAND_H
#define HAND_H

#include <vector>
#include <string>

#include <Card.h>
#include <Enums.h>
#include <Board.h>

class Hand {
	std::vector<Card> m_cards;
	std::vector<Card> m_maxHighHandCards;
	std::vector<Card> m_lowHandCards;
	HighHand m_maxHighHandRank;
	bool m_hasLowHand;

	void findHighHand(const std::vector<Card>&);
	void findLowHand(const std::vector<Card>&);

	HighHand checkHighHandCards(std::vector<Card>&);
	void checkHighHandRank(const HighHand&, const std::vector<Card>&);
	void handleExceptionalStraightFlush(std::vector<Card>&);
public:
	Hand(std::string handSetup);
	
	HighHand getHighHandRank() const;
	std::vector<Card> getHighHandCards() const;
	bool hasLowHand() const;
	std::vector<Card> getLowHandCards() const;

	void findHiLoHand(const Board& board);
};

#endif // HAND_H