#ifndef CHECKER_H
#define CHECKER_H

#include <map>
#include <unordered_set>

class Card;
enum class Suit;
enum class HighHandRank;

class HighHand {
	friend class Checker;
	std::vector<Card> cards;
	HighHandRank rank;
public:
	std::vector<Card> getCards() const;
	HighHandRank getRank() const;
	friend bool operator<(const HighHand& lhs, const HighHand& rhs);
};

class Checker {
	std::map<Rank, size_t> cards;
	std::unordered_set<Suit> suits;
	HighHand highHand;
public:
	typedef std::map<Rank, size_t>::value_type c2s_t;
	bool isStraight() const;
	bool isFlush() const;
	bool isStraightFlush() const;
	bool is4OfAKind() const;
	bool isFullHouse() const;
	bool is3OfAKind() const;
	bool isTwoPair() const;
	bool isOnePair() const;

	void validate(const std::vector<Card>& card);
	HighHand getHighHand() const;
	void compareHighHands(const HighHand& highHand);
};

namespace compr {
	bool fourOfKind(Checker::c2s_t const& p);
	bool triplet(Checker::c2s_t const& p);
	bool pair(Checker::c2s_t const& p);
}

#endif // CHECKER_H
