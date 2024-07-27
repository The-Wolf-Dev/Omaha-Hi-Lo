#ifndef CHECKER_H
#define CHECKER_H

#include <map>
#include <unordered_set>

#include <Enums.h>

class Card;

class HighHand {
	friend class Checker;
	HighHandRank m_rank;
	std::map<Rank, size_t> m_cards;
public:
	HighHand();
	std::map<Rank, size_t> getCards() const;
	HighHandRank getRank() const;
};

class LowHand {
	friend class Checker;
	bool m_qualified;
	std::map<Rank, size_t> m_cards;
public:
	LowHand();
	std::map<Rank, size_t> getCards() const;
	bool isQualified() const;
};

class Checker {
	std::map<Rank, size_t> m_cards;
	std::unordered_set<Suit> m_suits;
	HighHand m_highHand;
	LowHand m_lowHand;

	void makeLowAce();
public:
	typedef std::map<Rank, size_t>::value_type c2s_t;
	bool isStraightFlush() const;
	bool isStraight() const;
	bool isFlush() const;
	bool is4OfAKind() const;
	bool isFullHouse() const;
	bool is3OfAKind() const;
	bool isTwoPair() const;
	bool isOnePair() const;

	void update(const std::vector<Card>& cards);

	HighHand getPotentialHighHand() const;
	bool Checker::isValidPotentialHighHand(const HighHand& hh) const;

	LowHand getPotentialLowHand() const;
	bool isValidPotentialLowHand(const LowHand& lh) const;

	HighHand getHighHand() const;
	LowHand getLowHand() const;
};

namespace compr {
	bool fourOfKind(Checker::c2s_t const& p);
	bool triplet(Checker::c2s_t const& p);
	bool pair(Checker::c2s_t const& p);
}

#endif // CHECKER_H
