#include <algorithm>
#include <numeric>

#include <Tools.h>

Suit parseSuit(const char suit) {
	switch (suit)
	{
	case 'd':
		return Suit::Diamonds;
	case 'c':
		return Suit::Clubs;
	case 'h':
		return Suit::Hearts;
	case 's':
		return Suit::Spaders;
	default:
		return Suit::None;
	}
}

Rank parseRank(const char rank) {
	switch (rank)
	{
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		return static_cast<Rank>(rank - '0');
	case 'T':
		return Rank::T;
	case 'J':
		return Rank::J;
	case 'Q':
		return Rank::Q;
	case 'K':
		return Rank::K;
	case 'A':
		return Rank::A;
	case 'L':
		return Rank::LA;
	default:
		return Rank::None;
	}
}

std::string highHandRankToString(const HighHandRank suit) {
	switch (suit)
	{
	case HighHandRank::StraightFlush: return "Straight Flush";
	case HighHandRank::FourOfAKind: return "4-of-a-Kind";
	case HighHandRank::FullHouse: return "Full House";
	case HighHandRank::Flush: return "Flush";
	case HighHandRank::Straight: return "Straight";
	case HighHandRank::ThreeOfAKind: return "3-of-a-Kind";
	case HighHandRank::TwoPair: return "Two Pair";
	case HighHandRank::OnePair: return "One Pair";
	case HighHandRank::HighCard: return "High Card";
	default:
		return "Unknown HighHand";
	}
}

char cardRankToChar(const Rank rank) {
	switch (rank)
	{
	case Rank::_2:
	case Rank::_3:
	case Rank::_4:
	case Rank::_5:
	case Rank::_6:
	case Rank::_7:
	case Rank::_8:
	case Rank::_9:
		return (int)rank + '0';
	case Rank::T:
		return 'T';
	case Rank::J:
		return 'J';
	case Rank::Q:
		return 'Q';
	case Rank::K:
		return 'K';
	case Rank::A:
	case Rank::LA:
		return 'A';
	default:
		return '0';
	}
}

std::vector<Card> cardSetupToVector(std::string str) {
	std::vector<Card> cards;
	for (size_t i{ 0U }, end{ str.length() }; i < end; ++i)
	{
		if (i % 3 == 0) {
			cards.emplace_back(parseRank(str[i]), parseSuit(str[i + 1U]));
		}
	}
	std::sort(cards.begin(), cards.end(), std::greater<Card>());
	return cards;
}

std::map<Rank, size_t>::const_iterator findNotSuitableCard(const std::map<Rank, size_t>& map) {
	return std::find_if(map.cbegin(), map.cend(),
		[](const std::pair<Rank, size_t>& card) { return card.first > Rank::_8; });
}

bool operator<(const std::vector<Card>& lhs, const std::vector<Card>& rhs) {
	int lhsSum = std::accumulate(lhs.begin(), lhs.end(), 0);
	int rhsSum = std::accumulate(rhs.begin(), rhs.end(), 0);
	return lhsSum < rhsSum;
}

bool pairComparator(std::pair<Rank, size_t>& a, std::pair<Rank, size_t>& b) { return a.second > b.second; }

std::vector<std::pair<Rank, size_t>> makeSortedVectorFromMap(const std::map<Rank, size_t>& map) {
	std::vector<std::pair<Rank, size_t>> vec;
	vec.reserve(map.size());

	for (auto cur{ map.crbegin() }, end{ map.crend() }; cur != end; ++cur) {
		vec.push_back(*cur);
	}

	std::sort(vec.begin(), vec.end(), pairComparator);

	return vec;
}

bool operator<(const std::map<Rank, size_t>& lhs, const std::map<Rank, size_t>& rhs) {
	auto lhs_size{ lhs.size() }, rhs_size{ rhs.size() };
	if (lhs_size != rhs_size) return false;

	auto lhs_cards = makeSortedVectorFromMap(lhs);
	auto rhs_cards = makeSortedVectorFromMap(rhs);

	// In the loop, the first two different cards are searched to determine whether lhs < rhs
	for (auto i{ 0ULL }; i < lhs_size; ++i) {
		if (lhs_cards[i].first > rhs_cards[i].first) return false;
		if (lhs_cards[i].first < rhs_cards[i].first) return true;
	}

	return false;
}

bool operator==(const std::map<Rank, size_t>& lhs, const std::map<Rank, size_t>& rhs) {
	if (lhs.size() != rhs.size()) return false;

	for (auto rhsCur{ rhs.crbegin() }, lhsCur{ lhs.crbegin() }, end{ lhs.crend() }; lhsCur != end; ++lhsCur, ++rhsCur) {
		if (lhsCur->first != rhsCur->first || lhsCur->second != rhsCur->second) return false;
	}

	return true;
}

std::ostream& operator<<(std::ostream& os, const std::map<Rank, size_t>& cards) {
	for (auto cur{ cards.crbegin() }, end{ cards.crend() }; cur != end; ++cur) {
		for (size_t i{ 0ULL }, end1{ cur->second }; i < end1; ++i) {
			os << cardRankToChar(cur->first);
		}
	}
	return os;
}