#ifndef ENUMS_H
#define ENUMS_H

enum class Rank {
	None,
	LA,
	_2,
	_3,
	_4,
	_5,
	_6,
	_7,
	_8,
	_9,
	T,
	J,
	Q,
	K,
	A
};

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

enum CardConst {
	HILO_HAND_SIZE = 5,
	PAIR_FROM_HAND = 2,
	THREE_FROM_BOARD = 3
};

#endif // ENUMS_H