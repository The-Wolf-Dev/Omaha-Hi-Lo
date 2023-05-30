#ifndef POKER_H
#define POKER_H

#include <iostream>

#include <Hand.h>
#include <Board.h>

class Poker {
	Hand m_handA;
	Hand m_handB;
	Board m_board;
public:
	Poker(std::string handASetup, std::string handBSetup, std::string boardSetup);
	void findWinner();
};

#endif // POKER_H