#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>

#include <Card.h>

class Board {
	std::vector<Card> m_cards;
public:
	Board(std::string boardSetup);

	std::vector<Card> getCards() const;
};

#endif // BOARD_H