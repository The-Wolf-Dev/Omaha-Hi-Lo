#include <algorithm>

#include <Card.h>
#include <Checker.h>

namespace compr {
	bool fourOfKind(Checker::c2s_t const& p) { return p.second == 4; }
	bool triplet(Checker::c2s_t const& p) { return p.second == 3; }
	bool pair(Checker::c2s_t const& p) { return p.second == 2; }
}

void Checker::StraightFlushChecker::update(const Card& card) {
	if (card.getRank() == 'A') cards[Card('L', card.getSuit())];
	cards[card]++;

	suits.insert(card.getSuit());
}

bool Checker::StraightFlushChecker::isStraight() const {
	if (cards.empty() || cards.size() < 5) return false;

	auto cur{ cards.cbegin() }, next{ cur };
	++next;

	if (cur->first.getRank() == 'L' && next->first.getRank() != '2') {
		cur = next;
		++next;
	}

	size_t i = 0;
	for (auto e = cards.cend(); next != e && i < 4; ++cur, ++next, ++i) {
		Card ccard = cur->first, ncard = next->first;
		if (ccard.getWeight() != ncard.getWeight() - 1)
			return false;
	}
	
	return true;
}

bool Checker::StraightFlushChecker::isFlush() const {
	return suits.size() == 1;
}

bool Checker::StraightFlushChecker::isStraightFlush() const {
	return isStraight() && isFlush();
}

void Checker::update(const Card& card) {
	sfchecker.update(card);
	cards[card]++;
}

bool Checker::isStraight() const {
	return sfchecker.isStraight();
}

bool Checker::isFlush() const {
	return sfchecker.isFlush();
}

bool Checker::isStraightFlush() const {
	return sfchecker.isStraightFlush();
}

bool Checker::is4OfAKind() const {
	if (cards.size() != 2) return false;
	auto e = cards.cend();
	return e != std::find_if(cards.cbegin(), e, compr::fourOfKind);
#if 0
	return false;

	for (auto begin{ cards.cbegin() }, end{ cards.cend() }; begin != end; ++begin) {
		size_t cardsCount = begin->second;
		if (cardsCount != 4 && cardsCount != 1) return false;
	}

	return true;
#endif
}

bool Checker::isFullHouse() const {
	if (cards.size() != 2) return false;
	auto e = cards.cend();
	return e != std::find_if(cards.cbegin(), e, compr::triplet);
#if 0
	for (auto begin{ cards.cbegin() }, end{ cards.cend() }; begin != end; ++begin) {
		size_t cardsCount = begin->second;
		if (cardsCount != 3 && cardsCount != 2) return false;
	}

	return true;
#endif
}

bool Checker::is3OfAKind() const {
	if (cards.size() != 3) return false;

	auto e = cards.cend();
	return e != std::find_if(cards.cbegin(), e, compr::triplet);
#if 0
	for (auto begin{ cards.cbegin() }, end{ cards.cend() }; begin != end; ++begin) {
		size_t cardsCount = begin->second;
		if (cardsCount != 3 && cardsCount != 1) return false;
	}

	return true;
#endif
}

bool Checker::isTwoPair() const {
	if (cards.size() != 3) return false;

	auto e = cards.cend();
	auto firstPair = std::find_if(cards.cbegin(), e, compr::pair);
	if (firstPair != e)
		return e != std::find_if(++firstPair, e, compr::pair);
	else return false;
#if 0
	for (auto begin{ cards.cbegin() }, end{ cards.cend() }; begin != end; ++begin) {
		size_t cardsCount = begin->second;
		if (cardsCount != 2 && cardsCount != 1) return false;
	}

	return true;
#endif
}

bool Checker::isOnePair() const {
	if (cards.size() != 4) return false;

	auto e = cards.cend();
	return e != std::find_if(cards.cbegin(), e, compr::pair);
#if 0
	for (auto begin{ cards.cbegin() }, end{ cards.cend() }; begin != end; ++begin) {
		size_t cardsCount = begin->second;
		if (cardsCount != 2 && cardsCount != 1) return false;
	}

	return true;
#endif
}