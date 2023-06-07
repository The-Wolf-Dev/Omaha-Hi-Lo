#ifndef CHECKER_H
#define CHECKER_H

#include <map>
#include <unordered_set>

class Card;
enum class Suit;

class Checker {
	std::map<Card, size_t> cards;
public:
	bool is4OfAKind() const;
	bool isFullHouse() const;
	bool is3OfAKind() const;
	bool isTwoPair() const;
	bool isOnePair() const;

	void update(const Card& card);
};

class StraightFlushChecker {
	std::map<Card, size_t> cards;
	std::unordered_set<Suit> suits;
public:
	bool isStraight() const;
	bool isFlush() const;
	bool isStraightFlush() const;

	void update(const Card& card);
};

#endif // CHECKER_H
