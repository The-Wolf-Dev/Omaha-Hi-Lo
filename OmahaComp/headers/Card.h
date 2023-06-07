#ifndef CARD_H
#define CARD_H

#include <iostream>

#include <Enums.h>

class Card {
	char m_rank;
	Suit m_suit;
	int m_weight;
public:
	Card(char m_rank, Suit m_suit);

	char getRank() const;
	Suit getSuit() const;
	int getWeight() const;
	void setWeight(int);

	friend bool operator<(const Card&, const Card&);
	friend bool operator>(const Card&, const Card&);
	friend bool operator>(const Card&, const int&);
	friend bool operator==(const Card&, const Card&);
	friend bool operator==(const Card&, const int&);
	friend bool operator!=(const Card&, const Card&);
	friend int operator+(const Card&, const Card&);
	friend int operator+(const int, const Card&);
	friend std::ostream& operator<<(std::ostream&, const Card&);
};

#endif // CARD_H