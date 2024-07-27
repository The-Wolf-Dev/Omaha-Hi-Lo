#ifndef CARD_H
#define CARD_H

#include <iostream>

#include <Enums.h>

class Card {
	mutable Rank m_rank;
	Suit m_suit;
public:
	Card(Rank m_rank, Suit m_suit);

	Rank getRank() const;
	Suit getSuit() const;

	friend bool operator<(const Card&, const Card&);
	friend bool operator>(const Card&, const Card&);
	friend bool operator>(const Card&, const Rank&);
	friend bool operator==(const Card&, const Card&);
	friend bool operator==(const Card&, const Rank&);
	friend bool operator!=(const Card&, const Card&);
	friend int operator+(const Card&, const Card&);	// for std::accumulate
	friend int operator+(const int, const Card&);	// for std::accumulate
	friend std::ostream& operator<<(std::ostream&, const Card&);
};

#endif // CARD_H