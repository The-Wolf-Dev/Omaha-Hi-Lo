#include <iostream>
#include <algorithm>
#include <functional>

#include <Board.h>
#include <Tools.h>

Board::Board(std::string boardSetup) {
	for (size_t i{ 0U }, end{ boardSetup.length() }; i < end; ++i)
	{
		if (i % 3 == 0) {
			m_cards.emplace_back(parseRank(boardSetup[i]), parseSuit(boardSetup[i + 1U]));
		}
	}
}

std::vector<Card> Board::getCards() const {
	return m_cards;
}