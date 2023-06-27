#ifndef HAND_H
#define HAND_H

#include <vector>
#include <string>

#include <Card.h>
#include <Enums.h>
#include <Board.h>
#include <Checker.h>

class Hand {
	const std::vector<Card>& m_cards;
	Checker m_checker;

	void checkLowHandCards(std::vector<Card>&);
public:
	Hand(const std::vector<Card>& handSetup);
	
	void findHiLoHand(const Board& board);

	HighHand getHighHand() const;
	LowHand getLowHand() const;
};

#endif // HAND_H