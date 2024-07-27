#include <iostream>
#include <algorithm>
#include <functional>

#include <Board.h>
#include <Tools.h>

Board::Board(const std::vector<Card>& boardSetup) 
	: m_cards{ boardSetup } {
}

std::vector<Card> Board::getCards() const {
	return m_cards;
}