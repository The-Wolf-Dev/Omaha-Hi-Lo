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

int parseWeight(const char rank) {
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
		return rank - '0';
	case 'T':
		return 10;
	case 'J':
		return 11;
	case 'Q':
		return 12;
	case 'K':
		return 13;
	case 'A':
		return 14;
	case 'L':
		return 1;
	default:
		return 0;
	}
}

void removeDuplicates(std::vector<Card>& vec) {
	std::sort(vec.begin(), vec.end());
	auto last = std::unique(vec.begin(), vec.end());
	vec.erase(last, vec.end());
}

void changeAceWeight(std::vector<Card>::iterator& It) {
	(*It).setWeight((int)CardConst::LOW_HAND_ACE);
}

bool operator<(const std::vector<Card>& lhs, const std::vector<Card>& rhs) {
	int lhsSum = std::accumulate(lhs.begin(), lhs.end(), 0);
	int rhsSum = std::accumulate(rhs.begin(), rhs.end(), 0);
	return lhsSum < rhsSum;
}

std::vector<Card>::iterator findHighAce(std::vector<Card>& vec) {
	return std::find(vec.begin(), vec.end(), (int)CardConst::HIGH_HAND_ACE);
}

std::vector<Card>::const_iterator findNotSuitableCard(std::vector<Card>& vec) {
	return std::find_if(vec.cbegin(), vec.cend(),
		[](const Card& card) { return card > (int)CardConst::LOW_HAND_MAX_RANK; }); //std::greater<Card>((int)CardConst::LOW_HAND_MAX_RANK, std::placeholders::_1)
}

void handleExceptionalStraightFlush(std::vector<Card>& highHandCards) {
	if (!highHandCards.empty()
		&& highHandCards[0].getRank() == 'A' && highHandCards[1].getRank() == '5') {
		highHandCards[0].setWeight(1);
	}
}