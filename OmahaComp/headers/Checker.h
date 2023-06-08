#ifndef CHECKER_H
#define CHECKER_H

#include <map>
#include <unordered_set>

class Card;
enum class Suit;

class Checker {
	class StraightFlushChecker {
		std::map<Card, size_t> cards;
		std::unordered_set<Suit> suits;
	public:
		bool isStraight() const;
		bool isFlush() const;
		bool isStraightFlush() const;

		void update(const Card& card);
	} sfchecker;
	std::map<Card, size_t> cards;

public:
	typedef std::map<Card, size_t>::value_type c2s_t;
	bool isStraight() const;
	bool isFlush() const;
	bool isStraightFlush() const;
	bool is4OfAKind() const;
	bool isFullHouse() const;
	bool is3OfAKind() const;
	bool isTwoPair() const;
	bool isOnePair() const;

	void update(const Card& card);
};

namespace compr {
	bool fourOfKind(Checker::c2s_t const& p);
	bool triplet(Checker::c2s_t const& p);
	bool pair(Checker::c2s_t const& p);
}

#endif // CHECKER_H
