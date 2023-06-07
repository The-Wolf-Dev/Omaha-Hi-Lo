#include <Card.h>
#include <Tools.h>

Card::Card(char rank, Suit suit) : m_rank{ rank }, m_suit{ suit }, m_weight{ 0 } {
	m_weight = parseWeight(rank);
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

int operator+(const Card& lhs, const Card& rhs) {
	return lhs.getWeight() + rhs.getWeight();
}

int operator+(const int lhs, const Card& rhs) {
	return lhs + rhs.getWeight();
}

std::ostream& operator<<(std::ostream& os, const Card& card)
{
	os << card.m_rank;
	return os;
}