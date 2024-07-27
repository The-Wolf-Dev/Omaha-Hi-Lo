#ifndef POKER_H
#define POKER_H

#include <iostream>

#include <Hand.h>
#include <Board.h>

class Poker {
	Hand m_handA;
	Hand m_handB;
	Board m_board;

	typedef std::pair<std::string, HighHandRank> hipair_t;
	hipair_t getHiWinner() const;
	typedef std::pair<std::string, std::map<Rank, size_t>> lopair_t;
	lopair_t getLoWinner() const;
	typedef std::pair<hipair_t, lopair_t> winpair_t;
public:
	Poker(const std::vector<Card>& handASetup, const std::vector<Card>& handBSetup, const std::vector<Card>& boardSetup);
	winpair_t getWinner();
};

#endif // POKER_H