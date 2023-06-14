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
	HighHandRank m_maxHighHandRank;
	bool m_hasLowHand;

	HighHandRank checkHighHandCards(std::vector<Card>&);
	void checkHighHandRank(const HighHandRank&, const std::vector<Card>&);
	void checkLowHandCards(std::vector<Card>&);
public:
	Hand(std::string handSetup);
	
	void findHiLoHand(const Board& board);

	HighHandRank getHighHandRank() const;
	std::vector<Card> getHighHandCards() const;
	bool hasLowHand() const;
	std::vector<Card> getLowHandCards() const;
};

#endif // HAND_H