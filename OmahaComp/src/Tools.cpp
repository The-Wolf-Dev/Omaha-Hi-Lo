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

std::string highHandRankToString(const HighHand suit) {
	switch (suit)
	{
	case HighHand::StraightFlush: return "Straight Flush";
	case HighHand::FourOfAKind: return "4-of-a-Kind";
	case HighHand::FullHouse: return "Full House";
	case HighHand::Flush: return "Flush";
	case HighHand::Straight: return "Straight";
	case HighHand::ThreeOfAKind: return "3-of-a-Kind";
	case HighHand::TwoPair: return "Two Pair";
	case HighHand::OnePair: return "One Pair";
	case HighHand::HighCard: return "High Card";
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

void removeDuplicates(std::vector<Card>& vec) {
	std::sort(vec.begin(), vec.end());
	auto last = std::unique(vec.begin(), vec.end());
	vec.erase(last, vec.end());
}

void makeLowAce(std::vector<Card>::iterator& It) {
	(*It).makeLowAce();
}

bool operator<(const std::vector<Card>& lhs, const std::vector<Card>& rhs) {
	int lhsSum = std::accumulate(lhs.begin(), lhs.end(), 0);
	int rhsSum = std::accumulate(rhs.begin(), rhs.end(), 0);
	return lhsSum < rhsSum;
}

std::vector<Card>::iterator findHighAce(std::vector<Card>& vec) {
	return std::find(vec.begin(), vec.end(), Rank::A);
}

std::vector<Card>::const_iterator findNotSuitableCard(std::vector<Card>& vec) {
	return std::find_if(vec.cbegin(), vec.cend(),
		[](const Card& card) { return card > Rank::_8; }); //std::greater<Card>(Rank::_8, std::placeholders::_1)
}

void handleExceptionalStraightFlush(std::vector<Card>& highHandCards) {
	if (!highHandCards.empty()
		&& highHandCards[0].getRank() == Rank::A && highHandCards[1].getRank() == Rank::_5) {
		highHandCards[0].makeLowAce();
	}
}