#include <iostream>
#include <algorithm>
#include <functional>

#include <Board.h>
#include <Tools.h>

Board::Board(std::string boardSetup) {
	for (size_t i{ 0U }, end{ boardSetup.length() }; i < end; ++i)
	{
		if (i % 3 == 0) {
			m_cards.emplace_back(boardSetup[i], parseSuit(boardSetup[i + 1U]));
		}
	}
	std::sort(m_cards.begin(), m_cards.end(), std::greater<Card>());
}

std::vector<Card> Board::getCards() const {
	return m_cards;
}