#ifndef ENUMS_H
#define ENUMS_H

enum class Suit {
	None,
	Diamonds,
	Clubs,
	Hearts,
	Spaders
};

enum class HighHand {
	None,
	HighCard,
	OnePair,
	TwoPair,
	ThreeOfAKind,
	Straight,
	Flush,
	FullHouse,
	FourOfAKind,
	StraightFlush
};

enum class CardConst {
	HIGH_HAND_ACE = 14,
	LOW_HAND_ACE = 1,
	LOW_HAND_MAX_RANK = 8,
	LOW_HAND_SIZE = 5,
	HIGH_HAND_SIZE = 5,
	HAND_SIZE = 4,
	PAIR_FROM_HAND = 2,
	THREE_FROM_BOARD = 3
};

#endif // ENUMS_H