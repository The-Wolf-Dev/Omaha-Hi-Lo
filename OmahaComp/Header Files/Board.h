#pragma once

#include <string>
#include <vector>

#include "Card.h"

class Board {
	std::vector<Card> m_cards;
public:
	Board(std::string boardSetup);

	std::vector<Card> getCards() const;
};