#include "../Header Files/Card.h"

Card::Card(char rank, char suit) : m_rank{ rank }, m_suit{ }, m_weight{ 0 } {
	m_weight = parseWeight(rank);
	m_suit = parseSuit(suit);
}

char Card::getRank() const {
	return m_rank;
}

Suit Card::getSuit() const {
	return m_suit;
}

int Card::getWeight() const {
	return m_weight;
}

void Card::setWeight(int weight) {
	m_weight = weight;
}

int Card::parseWeight(const char rank) {
	switch (rank)
	{
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		return rank - '0';
	case 'T':
		return 10;
	case 'J':
		return 11;
	case 'Q':
		return 12;
	case 'K':
		return 13;
	case 'A':
		return 14;
	default:
		return 0;
	}
}

Suit Card::parseSuit(const char suit) {
	switch (suit)
	{
	case 'd':
		return Suit::Diamonds;
	case 'c':
		return Suit::Clubs;
	case 'h':
		return Suit::Hearts;
	case 's':
		return Suit::Spaders;
	default:
		return Suit::None;
	}
}

bool operator<(const Card& lhs, const Card& rhs)
{
	return lhs.m_weight < rhs.m_weight;
}

bool operator>(const Card& lhs, const Card& rhs)
{
	return lhs.m_weight > rhs.m_weight;
}

bool operator>(const Card& lhs, const int& rhs)
{
	return lhs.m_weight > rhs;
}

bool operator==(const Card& lhs, const Card& rhs)
{
	return lhs.m_weight == rhs.m_weight;
}

bool operator==(const Card& lhs, const int& rhs)
{
	return lhs.m_weight == rhs;
}

bool operator!=(const Card& lhs, const Card& rhs)
{
	return !(lhs == rhs);
}

Card& Card::operator+=(const int& rhs) {
	this->m_weight += rhs;
	return *this;
}

Card operator+(Card lhs, const int& rhs) {
	lhs += rhs;
	return lhs;
}

std::ostream& operator<<(std::ostream& os, const Card& card)
{
	os << card.m_rank;
	return os;
}