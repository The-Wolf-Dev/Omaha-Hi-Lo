#include <algorithm>
#include <numeric>

#include <Card.h>
#include <Checker.h>
#include <Tools.h>

HighHand::HighHand()
	: m_rank(HighHandRank::HighCard)
{
}

std::map<Rank, size_t> HighHand::getCards() const {
	return m_cards;
}

HighHandRank HighHand::getRank() const {
	return m_rank;
}

LowHand::LowHand()
	: m_qualified{ false }
{
}

std::map<Rank, size_t> LowHand::getCards() const {
	return m_cards;
}

bool LowHand::isQualified() const {
	return m_qualified;
}

void Checker::update(const std::vector<Card>& cards) {
	m_cards.clear();
	m_suits.clear();
	for (const auto& c : cards) {
		m_cards[c.getRank()]++;
		m_suits.insert(c.getSuit());
	}

	auto begin{ m_cards.crbegin() }, next{ begin };
	++next;
	if (m_cards.size() == 5 && begin->first == Rank::A && next->first == Rank::_5) {
		makeLowAce();
	}

	HighHand potentialHighHand = getPotentialHighHand();
	if (isValidPotentialHighHand(potentialHighHand))
		m_highHand = potentialHighHand;

	auto end{ m_cards.cend() };
	if (m_cards.find(Rank::A) != end) {
		makeLowAce();
	}
	LowHand potentialLowHand = getPotentialLowHand();
	if (isValidPotentialLowHand(potentialLowHand))
		m_lowHand = potentialLowHand;
}

void Checker::makeLowAce() {
	m_cards.erase(Rank::A);
	m_cards[Rank::LA]++;
}

LowHand Checker::getPotentialLowHand() const {
	LowHand _lowHand;
	if (m_cards.size() < 5) return _lowHand;
	
	auto notSuitableCard = findNotSuitableCard(m_cards);
	if (notSuitableCard != m_cards.cend()) return _lowHand;

	_lowHand.m_cards = m_cards;
	_lowHand.m_qualified = true;
	return _lowHand;
}

bool Checker::isValidPotentialLowHand(const LowHand& lh) const {
	if (!lh.m_qualified) {
		return false;
	}
	else if (lh.m_cards < m_lowHand.m_cards || m_lowHand.m_cards.empty()) {
		return true;
	}
	return false;
}

HighHand Checker::getPotentialHighHand() const {
	HighHand _highHand;
	if (isStraightFlush()) {
		_highHand.m_rank = HighHandRank::StraightFlush;
	}
	else if (is4OfAKind()) {
		_highHand.m_rank = HighHandRank::FourOfAKind;
	}
	else if (isFullHouse()) {
		_highHand.m_rank = HighHandRank::FullHouse;
	}
	else if (isFlush()) {
		_highHand.m_rank = HighHandRank::Flush;
	}
	else if (isStraight()) {
		_highHand.m_rank = HighHandRank::Straight;
	}
	else if (is3OfAKind()) {
		_highHand.m_rank = HighHandRank::ThreeOfAKind;
	}
	else if (isTwoPair()) {
		_highHand.m_rank = HighHandRank::TwoPair;
	}
	else if (isOnePair()) {
		_highHand.m_rank = HighHandRank::OnePair;
	}
	else {
		_highHand.m_rank = HighHandRank::HighCard;
	}
	_highHand.m_cards = m_cards;
	return _highHand;
}

bool Checker::isValidPotentialHighHand(const HighHand& hh) const {
	if (m_highHand.m_rank < hh.m_rank || m_highHand.m_rank == hh.m_rank && m_highHand.m_cards < hh.m_cards) {
		return true;
	}
	return false;
}

HighHand Checker::getHighHand() const {
	return m_highHand;
}

LowHand Checker::getLowHand() const {
	return m_lowHand;
}

bool compr::fourOfKind(Checker::c2s_t const& p) { return p.second == 4; }
bool compr::triplet(Checker::c2s_t const& p) { return p.second == 3; }
bool compr::pair(Checker::c2s_t const& p) { return p.second == 2; }

bool Checker::isStraight() const {
	if (m_cards.empty() || m_cards.size() < 5) return false;

	auto cur{ m_cards.cbegin() }, next{ cur };
	++next;

	size_t i = 0;
	for (auto end{ m_cards.cend() }; next != end && i < 4; ++cur, ++next, ++i) {
		Rank ccard = cur->first, ncard = next->first;
		if ((int)ccard != (int)ncard - 1)
			return false;
	}
	
	return true;
}

bool Checker::isFlush() const {
	return m_suits.size() == 1;
}

bool Checker::isStraightFlush() const {
	return isStraight() && isFlush();
}

bool Checker::is4OfAKind() const {
	if (m_cards.size() != 2) return false;
	auto e = m_cards.cend();
	return e != std::find_if(m_cards.cbegin(), e, compr::fourOfKind);
}

bool Checker::isFullHouse() const {
	if (m_cards.size() != 2) return false;

	auto e = m_cards.cend();
	return e != std::find_if(m_cards.cbegin(), e, compr::triplet);
}

bool Checker::is3OfAKind() const {
	if (m_cards.size() != 3) return false;

	auto e = m_cards.cend();
	return e != std::find_if(m_cards.cbegin(), e, compr::triplet);
}

bool Checker::isTwoPair() const {
	if (m_cards.size() != 3) return false;

	auto e = m_cards.cend();
	auto firstPair = std::find_if(m_cards.cbegin(), e, compr::pair);
	if (firstPair != e)
		return e != std::find_if(++firstPair, e, compr::pair);
	return false;
}

bool Checker::isOnePair() const {
	if (m_cards.size() != 4) return false;

	auto e = m_cards.cend();
	return e != std::find_if(m_cards.cbegin(), e, compr::pair);
}