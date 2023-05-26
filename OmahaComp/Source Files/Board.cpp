#include "../Header Files/Board.h"

#include <iostream>
#include <algorithm>

Board::Board(std::string boardSetup) {
	for (size_t i = 0; i < boardSetup.length(); i++)
	{
		if (i % 3 == 0) {
			m_cards.emplace_back(boardSetup[i], boardSetup[i + 1]);
		}
	}
	std::sort(m_cards.begin(), m_cards.end(), [](auto l, auto r) { return l > r; });
}

std::vector<Card> Board::getCards() const {
	return m_cards;
}