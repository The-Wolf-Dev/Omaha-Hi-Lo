#pragma once

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