#pragma once

#include <iostream>

#include "Enums.h"

namespace cards_constant {
	const int HIGH_ACE = 14;
	const int LOW_ACE = 1;
	const int MAX_LOW_HAND_RANK = 8;
	const int LOW_HAND_SIZE = 5;
}

class Card {
	char m_rank;
	Suit m_suit;
	int m_weight;
public:
	Card(char m_rank, char m_suit);

	char getRank() const;
	Suit getSuit() const;
	int getWeight() const;
	void setWeight(int);
	int parseWeight(const char);
	Suit parseSuit(const char);

	friend bool operator<(const Card&, const Card&);
	friend bool operator>(const Card&, const Card&);
	friend bool operator>(const Card&, const int&);
	friend bool operator==(const Card&, const Card&);
	friend bool operator==(const Card&, const int&);
	friend bool operator!=(const Card&, const Card&);
	Card& operator+=(const int&);
	friend Card operator+(Card, const int&);
	friend std::ostream& operator<<(std::ostream&, const Card&);
};