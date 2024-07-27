#include <Card.h>
#include <Tools.h>

Card::Card(Rank rank, Suit suit) : m_rank{ rank }, m_suit{ suit } {
}

Rank Card::getRank() const {
	return m_rank;
}

Suit Card::getSuit() const {
	return m_suit;
}

bool operator<(const Card& lhs, const Card& rhs)
{
	return lhs.m_rank < rhs.m_rank;
}

bool operator>(const Card& lhs, const Card& rhs)
{
	return lhs.m_rank > rhs.m_rank;
}

bool operator>(const Card& lhs, const Rank& rhs)
{
	return lhs.m_rank > rhs;
}

bool operator==(const Card& lhs, const Card& rhs)
{
	return lhs.m_rank == rhs.m_rank;
}

bool operator==(const Card& lhs, const Rank& rhs)
{
	return lhs.m_rank == rhs;
}

bool operator!=(const Card& lhs, const Card& rhs)
{
	return !(lhs == rhs);
}

int operator+(const Card& lhs, const Card& rhs) {
	return (int)lhs.m_rank + (int)rhs.m_rank;
}

int operator+(const int lhs, const Card& rhs) {
	return lhs + (int)rhs.m_rank;
}

std::ostream& operator<<(std::ostream& os, const Card& card)
{
	os << cardRankToChar(card.m_rank);
	return os;
}