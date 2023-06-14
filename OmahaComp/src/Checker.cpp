#include <algorithm>

#include <Card.h>
#include <Checker.h>

std::vector<Card> HighHand::getCards() const {
	return cards;
}

HighHandRank HighHand::getRank() const {
	return rank;
}

bool operator<(const HighHand& lhs, const HighHand& rhs) {
	return lhs.rank < rhs.rank;
}

bool compr::fourOfKind(Checker::c2s_t const& p) { return p.second == 4; }
bool compr::triplet(Checker::c2s_t const& p) { return p.second == 3; }
bool compr::pair(Checker::c2s_t const& p) { return p.second == 2; }

void Checker::validate(const std::vector<Card>& cards) {
	for (const auto& c : cards) {
		this->cards[c.getRank()]++;
		suits.insert(c.getSuit());
	}

	//HighHand _highHand;
	//if (isStraightFlush()) {
	//	_highHand.rank = HighHandRank::StraightFlush;
	//}
	//else if (is4OfAKind()) {
	//	_highHand.rank = HighHandRank::FourOfAKind;
	//}
	//else if (isFullHouse()) {
	//	_highHand.rank = HighHandRank::FullHouse;
	//}
	//else if (isFlush()) {
	//	_highHand.rank = HighHandRank::Flush;
	//}
	//else if (isStraight()) {
	//	_highHand.rank = HighHandRank::Straight;
	//}
	//else if (is3OfAKind()) {
	//	_highHand.rank = HighHandRank::ThreeOfAKind;
	//}
	//else if (isTwoPair()) {
	//	_highHand.rank = HighHandRank::TwoPair;
	//}
	//else if (isOnePair()) {
	//	_highHand.rank = HighHandRank::OnePair;
	//}
	//else {
	//	_highHand.rank = HighHandRank::HighCard;
	//}
	//_highHand.cards = cards;
	//compareHighHands(_highHand);
}

HighHand Checker::getHighHand() const {
	return highHand;
}

void Checker::compareHighHands(const HighHand& highHand) {
	if (this->highHand < highHand) {
		this->highHand = highHand;
	}
}

bool Checker::isStraight() const {
	if (cards.empty() || cards.size() < 5) return false; // in straight all cards are unique, so size mustn't be <5

	auto cur{ cards.crbegin() }, next{ cur };
	++next;

	if (cur->first == Rank::A && next->first == Rank::_5) {
		return true;
		//cur = next;
		//++next;
	}

	for (auto e = cards.crend(); next != e; ++cur, ++next) {
		Rank ccard = cur->first, ncard = next->first;
		if ((int)ccard != (int)ncard + 1)
			return false;
	}

	return true;
}

bool Checker::isFlush() const {
	return suits.size() == 1;
}

bool Checker::isStraightFlush() const {
	//bool straight = isStraight();
	//bool flush = isFlush();
	//HighHand _highHand;

	//if (straight && flush) {
	//	// ...
	//}
	//else if (straight) {
	//	// ...
	//} else {
	//	// ...
	//}

	//return straight || flush;
	return isStraight() || isFlush();
}

bool Checker::isFullHouse() const {
	if (cards.size() != 2) return false;
	
	auto e = cards.cend();
	return e != std::find_if(cards.cbegin(), e, compr::triplet);
}

bool Checker::is3OfAKind() const {
	if (cards.size() != 3) return false;
	
	auto e = cards.cend();
	return e != std::find_if(cards.cbegin(), e, compr::triplet);
}

bool Checker::is4OfAKind() const {
	if (cards.size() != 2) return false;
	
	auto e = cards.cend();
	return e != std::find_if(cards.cbegin(), e, compr::fourOfKind);
}

bool Checker::isTwoPair() const {
	if (cards.size() != 3) return false;

	auto e = cards.cend();
	auto firstPair = std::find_if(cards.cbegin(), e, compr::pair);
	if (firstPair != e)
		return e != std::find_if(++firstPair, e, compr::pair);
	return false;
}

bool Checker::isOnePair() const {
	if (cards.size() != 4) return false;

	auto e = cards.cend();
	return e != std::find_if(cards.cbegin(), e, compr::pair);
}