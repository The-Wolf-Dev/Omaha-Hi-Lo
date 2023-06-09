#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>

#include <Checker.h>
#include <Card.h>

using namespace testing;

class CheckerTest : public Test {
protected:
	Checker checker;
};

TEST_F(CheckerTest, NewStraightFlushCheckerIsInvalid) {
	EXPECT_THAT(checker.isStraight(), IsFalse());
	EXPECT_THAT(checker.isFlush(), IsFalse());
	EXPECT_THAT(checker.isStraightFlush(), IsFalse());
}

TEST_F(CheckerTest, InvalidStraightWithInvalidCards) {
	std::vector<Card> cards{Card(Rank::_5, Suit::Spaders), Card(Rank::A, Suit::Diamonds), Card(Rank::J, Suit::Spaders), Card(Rank::_4, Suit::Spaders), Card(Rank::_5, Suit::Diamonds) };
	
	for (const auto& c : cards) {
		checker.update(c);
	}
	EXPECT_THAT(checker.isStraight(), IsFalse());
}

TEST_F(CheckerTest, InvalidStraightWithValidCards) {
	std::vector<Card> cards{ Card(Rank::_7, Suit::Spaders), Card(Rank::_6, Suit::Clubs), Card(Rank::_5, Suit::Spaders), Card(Rank::_4, Suit::Diamonds), Card(Rank::_3, Suit::Spaders) };
	
	for (const auto& c : cards) {
		checker.update(c);
	}
	EXPECT_THAT(checker.isStraight(), IsTrue());
}


TEST_F(CheckerTest, ValidStraightWithLowAce) {
	std::vector<Card> cards{ Card(Rank::A, Suit::Spaders), Card(Rank::_5, Suit::Spaders), Card(Rank::_4, Suit::Spaders), Card(Rank::_3, Suit::Spaders), Card(Rank::_2, Suit::Spaders) };
	
	for (const auto& c : cards) {
		checker.update(c);
	}
	EXPECT_THAT(checker.isStraight(), IsTrue());
}

TEST_F(CheckerTest, ValidStraightWithHighAce) {
	std::vector<Card> cards{ Card(Rank::A, Suit::Spaders), Card(Rank::K, Suit::Spaders), Card(Rank::Q, Suit::Spaders), Card(Rank::J, Suit::Spaders), Card(Rank::T, Suit::Spaders) };
	
	for (const auto& c : cards) {
		checker.update(c);
	}
	EXPECT_THAT(checker.isStraight(), IsTrue());
}

TEST_F(CheckerTest, ValidFlushWithValidCards) {
	std::vector<Card> cards{ Card(Rank::A, Suit::Spaders), Card(Rank::K, Suit::Spaders), Card(Rank::Q, Suit::Spaders), Card(Rank::J, Suit::Spaders), Card(Rank::T, Suit::Spaders) };

	for (const auto& c : cards) {
		checker.update(c);
	}
	EXPECT_THAT(checker.isFlush(), IsTrue());
}

TEST_F(CheckerTest, ValidFlushWithInvalidCards) {
	std::vector<Card> cards{ Card(Rank::A, Suit::Spaders), Card(Rank::K, Suit::Diamonds), Card(Rank::Q, Suit::Spaders), Card(Rank::J, Suit::Clubs), Card(Rank::T, Suit::Spaders) };

	for (const auto& c : cards) {
		checker.update(c);
	}
	EXPECT_THAT(checker.isFlush(), IsFalse());
}

TEST_F(CheckerTest, ValidStraightFlushWithValidCards) {
	std::vector<Card> cards{ Card(Rank::A, Suit::Diamonds), Card(Rank::K, Suit::Diamonds), Card(Rank::Q, Suit::Diamonds), Card(Rank::J, Suit::Diamonds), Card(Rank::T, Suit::Diamonds) };

	for (const auto& c : cards) {
		checker.update(c);
	}
	EXPECT_THAT(checker.isStraightFlush(), IsTrue());
}

TEST_F(CheckerTest, ValidStraightFlushWithInvalidCards) {
	std::vector<Card> cards{ Card(Rank::_3, Suit::Spaders), Card(Rank::K, Suit::Diamonds), Card(Rank::Q, Suit::Spaders), Card(Rank::J, Suit::Clubs), Card(Rank::T, Suit::Spaders) };

	for (const auto& c : cards) {
		checker.update(c);
	}
	EXPECT_THAT(checker.isStraightFlush(), IsFalse());
}

TEST_F(CheckerTest, NewCheckerIsInvalid) {
	EXPECT_THAT(checker.is4OfAKind(), IsFalse());
	EXPECT_THAT(checker.isFullHouse(), IsFalse());
	EXPECT_THAT(checker.is3OfAKind(), IsFalse());
	EXPECT_THAT(checker.isTwoPair(), IsFalse());
	EXPECT_THAT(checker.isOnePair(), IsFalse());
}

TEST_F(CheckerTest, Valid4OfAKindWithValidCards) {
	std::vector<Card> cards{ Card(Rank::K, Suit::Spaders), Card(Rank::K, Suit::Diamonds), Card(Rank::K, Suit::Clubs), Card(Rank::K, Suit::Hearts), Card(Rank::A, Suit::Spaders) };

	for (const auto& c : cards) {
		checker.update(c);
	}
	EXPECT_THAT(checker.is4OfAKind(), IsTrue());
}

TEST_F(CheckerTest, Invalid4OfAKindWithInvalidCards) {
	std::vector<Card> cards{ Card(Rank::K, Suit::Spaders), Card(Rank::_2, Suit::Diamonds), Card(Rank::K, Suit::Clubs), Card(Rank::K, Suit::Hearts), Card(Rank::A, Suit::Spaders) };

	for (const auto& c : cards) {
		checker.update(c);
	}
	EXPECT_THAT(checker.is4OfAKind(), IsFalse());
}

TEST_F(CheckerTest, ValidFullHouseWithValidCards) {
	std::vector<Card> cards{ Card(Rank::K, Suit::Spaders), Card(Rank::K, Suit::Diamonds), Card(Rank::K, Suit::Clubs), Card(Rank::A, Suit::Hearts), Card(Rank::A, Suit::Spaders) };

	for (const auto& c : cards) {
		checker.update(c);
	}
	EXPECT_THAT(checker.isFullHouse(), IsTrue());
}

TEST_F(CheckerTest, InvalidFullHouseWithInvalidCards) {
	std::vector<Card> cards{ Card(Rank::K, Suit::Spaders), Card(Rank::_2, Suit::Diamonds), Card(Rank::K, Suit::Clubs), Card(Rank::K, Suit::Hearts), Card(Rank::A, Suit::Spaders) };

	for (const auto& c : cards) {
		checker.update(c);
	}
	EXPECT_THAT(checker.isFullHouse(), IsFalse());
}

TEST_F(CheckerTest, Valid3OfAKindWithValidCards) {
	std::vector<Card> cards{ Card(Rank::K, Suit::Spaders), Card(Rank::_5, Suit::Spaders), Card(Rank::K, Suit::Clubs), Card(Rank::A, Suit::Hearts), Card(Rank::K, Suit::Diamonds) };

	for (const auto& c : cards) {
		checker.update(c);
	}
	EXPECT_THAT(checker.is3OfAKind(), IsTrue());
}

TEST_F(CheckerTest, Invalid3OfAKindWithInvalidCards) {
	std::vector<Card> cards{ Card(Rank::K, Suit::Spaders), Card(Rank::_2, Suit::Diamonds), Card(Rank::_3, Suit::Clubs), Card(Rank::K, Suit::Hearts), Card(Rank::A, Suit::Spaders) };

	for (const auto& c : cards) {
		checker.update(c);
	}
	EXPECT_THAT(checker.is3OfAKind(), IsFalse());
}

TEST_F(CheckerTest, ValidTwoPairWithValidCards) {
	std::vector<Card> cards{ Card(Rank::K, Suit::Spaders), Card(Rank::_5, Suit::Spaders), Card(Rank::A, Suit::Clubs), Card(Rank::A, Suit::Hearts), Card(Rank::K, Suit::Diamonds) };

	for (const auto& c : cards) {
		checker.update(c);
	}
	EXPECT_THAT(checker.isTwoPair(), IsTrue());
}

TEST_F(CheckerTest, InvalidTwoPairWithInvalidCards) {
	std::vector<Card> cards{ Card(Rank::K, Suit::Spaders), Card(Rank::_2, Suit::Diamonds), Card(Rank::_3, Suit::Clubs), Card(Rank::K, Suit::Hearts), Card(Rank::A, Suit::Spaders) };

	for (const auto& c : cards) {
		checker.update(c);
	}
	EXPECT_THAT(checker.isTwoPair(), IsFalse());
}

TEST_F(CheckerTest, ValidOnePairWithValidCards) {
	std::vector<Card> cards{ Card(Rank::A, Suit::Spaders), Card(Rank::A, Suit::Diamonds), Card(Rank::_3, Suit::Clubs), Card(Rank::_4, Suit::Hearts), Card(Rank::K, Suit::Diamonds) };

	for (const auto& c : cards) {
		checker.update(c);
	}
	EXPECT_THAT(checker.isOnePair(), IsTrue());
}

TEST_F(CheckerTest, InvalidOnePairWithInvalidCards) {
	std::vector<Card> cards{ Card(Rank::Q, Suit::Spaders), Card(Rank::_2, Suit::Diamonds), Card(Rank::_3, Suit::Clubs), Card(Rank::K, Suit::Hearts), Card(Rank::A, Suit::Spaders) };

	for (const auto& c : cards) {
		checker.update(c);
	}
	EXPECT_THAT(checker.isOnePair(), IsFalse());
}

TEST(ComparatorTest, Valid4OfKindWithValidCards) {
	std::map<Card, int> cards {
		{ Card(Rank::A, Suit::Clubs), 4 },
		{ Card(Rank::K, Suit::Diamonds), 1 }
	};

	auto e = cards.cend();
	auto result = std::find_if(cards.cbegin(), e, compr::fourOfKind);
	EXPECT_THAT(e != result, IsTrue());
}

TEST(ComparatorTest, Inalid4OfKindWithInalidCards) {
	std::map<Card, int> cards{
		{ Card(Rank::A, Suit::Clubs), 3 },
		{ Card(Rank::K, Suit::Diamonds), 2 }
	};

	auto e = cards.cend();
	auto result = std::find_if(cards.cbegin(), e, compr::fourOfKind);
	EXPECT_THAT(e != result, IsFalse());
}

TEST(ComparatorTest, ValidTripletWithValidCards) {
	std::map<Card, int> cards{
		{ Card(Rank::A, Suit::Clubs), 3 },
		{ Card(Rank::K, Suit::Diamonds), 2 }
	};

	auto e = cards.cend();
	auto result = std::find_if(cards.cbegin(), e, compr::triplet);
	EXPECT_THAT(e != result, IsTrue());
}

TEST(ComparatorTest, InalidTripletWithInalidCards) {
	std::map<Card, int> cards{
		{ Card(Rank::A, Suit::Clubs), 2 },
		{ Card(Rank::Q, Suit::Hearts), 2 },
		{ Card(Rank::K, Suit::Diamonds), 1 }
	};

	auto e = cards.cend();
	auto result = std::find_if(cards.cbegin(), e, compr::triplet);
	EXPECT_THAT(e != result, IsFalse());
}

TEST(ComparatorTest, ValidPairWithValidCards) {
	std::map<Card, int> cards{
		{ Card(Rank::A, Suit::Clubs), 2 },
		{ Card(Rank::Q, Suit::Hearts), 2 },
		{ Card(Rank::K, Suit::Diamonds), 1 }
	};

	auto e = cards.cend();
	auto result = std::find_if(cards.cbegin(), e, compr::pair);
	EXPECT_THAT(e != result, IsTrue());
}

TEST(ComparatorTest, InalidPairWithInalidCards) {
	std::map<Card, int> cards{
		{ Card(Rank::_2, Suit::Clubs), 1 },
		{ Card(Rank::Q, Suit::Hearts), 1 },
		{ Card(Rank::T, Suit::Hearts), 1 },
		{ Card(Rank::_3, Suit::Hearts), 1 },
		{ Card(Rank::A, Suit::Diamonds), 1 }
	};

	auto e = cards.cend();
	auto result = std::find_if(cards.cbegin(), e, compr::pair);
	EXPECT_THAT(e != result, IsFalse());
}