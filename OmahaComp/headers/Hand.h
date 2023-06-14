#ifndef HAND_H
#define HAND_H

#include <vector>
#include <string>

#include <Card.h>
#include <Enums.h>
#include <Board.h>
#include <Checker.h>

class Hand {
	std::vector<Card> m_cards;
	HighHand highHand;
	std::vector<Card> m_lowHandCards;
	bool m_hasLowHand;

	HighHandRank checkHighHandCards(std::vector<Card>&);
	void checkHighHandRank(const HighHandRank&, const std::vector<Card>&);
	void checkLowHandCards(std::vector<Card>&);
public:
	Hand(std::string handSetup);
	
	void findHiLoHand(const Board& board);

	HighHand getHighHand() const;
	std::vector<Card> getLowHand() const;
};

#endif // HAND_H