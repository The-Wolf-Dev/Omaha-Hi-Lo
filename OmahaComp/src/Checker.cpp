#include <algorithm>

#include <Card.h>
#include <Checker.h>

void StraightFlushChecker::update(const Card& card) {
	if (card.getRank() == 'A') cards[Card('L', card.getSuit())];
	cards[card]++;

	suits.insert(card.getSuit());
}

bool StraightFlushChecker::isStraight() const {
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

bool StraightFlushChecker::isFlush() const {
	return suits.size() == 1;
}

bool StraightFlushChecker::isStraightFlush() const {
	return isStraight() && isFlush();
}

void Checker::update(const Card& card) {
	cards[card]++;
}

bool Checker::is4OfAKind() const {
	if (cards.size() != 2) return false;

	for (auto begin{ cards.cbegin() }, end{ cards.cend() }; begin != end; ++begin) {
		size_t cardsCount = begin->second;
		if (cardsCount != 4 && cardsCount != 1) return false;
	}

	return true;
}

bool Checker::isFullHouse() const {
	if (cards.size() != 2) return false;

	for (auto begin{ cards.cbegin() }, end{ cards.cend() }; begin != end; ++begin) {
		size_t cardsCount = begin->second;
		if (cardsCount != 3 && cardsCount != 2) return false;
	}

	return true;
}

bool Checker::is3OfAKind() const {
	if (cards.size() != 3) return false;

	for (auto begin{ cards.cbegin() }, end{ cards.cend() }; begin != end; ++begin) {
		size_t cardsCount = begin->second;
		if (cardsCount != 3 && cardsCount != 1) return false;
	}

	return true;
}

bool Checker::isTwoPair() const {
	if (cards.size() != 3) return false;

	for (auto begin{ cards.cbegin() }, end{ cards.cend() }; begin != end; ++begin) {
		size_t cardsCount = begin->second;
		if (cardsCount != 2 && cardsCount != 1) return false;
	}

	return true;
}

bool Checker::isOnePair() const {
	if (cards.size() != 4) return false;

	for (auto begin{ cards.cbegin() }, end{ cards.cend() }; begin != end; ++begin) {
		size_t cardsCount = begin->second;
		if (cardsCount != 2 && cardsCount != 1) return false;
	}

	return true;
}