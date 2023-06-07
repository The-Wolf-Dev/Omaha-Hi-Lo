#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>

#include <Checker.h>
#include <Card.h>

using namespace testing;

class StraightFlushCheckerTest : public Test {
protected:
	StraightFlushChecker Checker;
};

class CheckerTest : public Test {
protected:
	Checker Checker;
};

TEST_F(StraightFlushCheckerTest, NewStraightFlushCheckerIsInvalid) {
	EXPECT_THAT(Checker.isStraight(), IsFalse());
	EXPECT_THAT(Checker.isFlush(), IsFalse());
}

TEST_F(StraightFlushCheckerTest, IsStraightWithWrongCards) {
	std::vector<Card> cards{Card('5', Suit::Spaders), Card('A', Suit::Diamonds), Card('J', Suit::Spaders), Card('4', Suit::Spaders), Card('5', Suit::Diamonds) };
	
	for (const auto& c : cards) {
		Checker.update(c);
	}
	EXPECT_THAT(Checker.isStraight(), IsFalse());
}

TEST_F(StraightFlushCheckerTest, IsStraightWithCorrectCards) {
	std::vector<Card> cards{ Card('7', Suit::Spaders), Card('6', Suit::Clubs), Card('5', Suit::Spaders), Card('4', Suit::Diamonds), Card('3', Suit::Spaders) };
	
	for (const auto& c : cards) {
		Checker.update(c);
	}
	EXPECT_THAT(Checker.isStraight(), IsTrue());
}


TEST_F(StraightFlushCheckerTest, IsStraightWithLowAce) {
	std::vector<Card> cards{ Card('A', Suit::Spaders), Card('5', Suit::Spaders), Card('4', Suit::Spaders), Card('3', Suit::Spaders), Card('2', Suit::Spaders) };
	
	for (const auto& c : cards) {
		Checker.update(c);
	}
	EXPECT_THAT(Checker.isStraight(), IsTrue());
}

TEST_F(StraightFlushCheckerTest, IsStraightWithHighAce) {
	std::vector<Card> cards{ Card('A', Suit::Spaders), Card('K', Suit::Spaders), Card('Q', Suit::Spaders), Card('J', Suit::Spaders), Card('T', Suit::Spaders) };
	
	for (const auto& c : cards) {
		Checker.update(c);
	}
	EXPECT_THAT(Checker.isStraight(), IsTrue());
}

TEST_F(StraightFlushCheckerTest, IsFlushWithCorrectCards) {
	std::vector<Card> cards{ Card('A', Suit::Spaders), Card('K', Suit::Spaders), Card('Q', Suit::Spaders), Card('J', Suit::Spaders), Card('T', Suit::Spaders) };

	for (const auto& c : cards) {
		Checker.update(c);
	}
	EXPECT_THAT(Checker.isFlush(), IsTrue());
}

TEST_F(StraightFlushCheckerTest, IsFlushWithInvalidCards) {
	std::vector<Card> cards{ Card('A', Suit::Spaders), Card('K', Suit::Diamonds), Card('Q', Suit::Spaders), Card('J', Suit::Clubs), Card('T', Suit::Spaders) };

	for (const auto& c : cards) {
		Checker.update(c);
	}
	EXPECT_THAT(Checker.isFlush(), IsFalse());
}

TEST_F(StraightFlushCheckerTest, IsStraightFlushWithCorrectCards) {
	std::vector<Card> cards{ Card('A', Suit::Diamonds), Card('K', Suit::Diamonds), Card('Q', Suit::Diamonds), Card('J', Suit::Diamonds), Card('T', Suit::Diamonds) };

	for (const auto& c : cards) {
		Checker.update(c);
	}
	EXPECT_THAT(Checker.isStraightFlush(), IsTrue());
}

TEST_F(StraightFlushCheckerTest, IsStraightFlushWithInvalidCards) {
	std::vector<Card> cards{ Card('3', Suit::Spaders), Card('K', Suit::Diamonds), Card('Q', Suit::Spaders), Card('J', Suit::Clubs), Card('T', Suit::Spaders) };

	for (const auto& c : cards) {
		Checker.update(c);
	}
	EXPECT_THAT(Checker.isStraightFlush(), IsFalse());
}

TEST_F(CheckerTest, NewCheckerIsInvalid) {
	EXPECT_THAT(Checker.is4OfAKind(), IsFalse());
}

TEST_F(CheckerTest, Is4OfAKindWithCorrectCards) {
	std::vector<Card> cards{ Card('K', Suit::Spaders), Card('K', Suit::Diamonds), Card('K', Suit::Clubs), Card('K', Suit::Hearts), Card('A', Suit::Spaders) };

	for (const auto& c : cards) {
		Checker.update(c);
	}
	EXPECT_THAT(Checker.is4OfAKind(), IsTrue());
}

TEST_F(CheckerTest, Is4OfAKindWithInvalidCards) {
	std::vector<Card> cards{ Card('K', Suit::Spaders), Card('2', Suit::Diamonds), Card('K', Suit::Clubs), Card('K', Suit::Hearts), Card('A', Suit::Spaders) };

	for (const auto& c : cards) {
		Checker.update(c);
	}
	EXPECT_THAT(Checker.is4OfAKind(), IsFalse());
}

TEST_F(CheckerTest, IsFullHouseWithCorrectCards) {
	std::vector<Card> cards{ Card('K', Suit::Spaders), Card('K', Suit::Diamonds), Card('K', Suit::Clubs), Card('A', Suit::Hearts), Card('A', Suit::Spaders) };

	for (const auto& c : cards) {
		Checker.update(c);
	}
	EXPECT_THAT(Checker.isFullHouse(), IsTrue());
}

TEST_F(CheckerTest, IsFullHouseWithInvalidCards) {
	std::vector<Card> cards{ Card('K', Suit::Spaders), Card('2', Suit::Diamonds), Card('K', Suit::Clubs), Card('K', Suit::Hearts), Card('A', Suit::Spaders) };

	for (const auto& c : cards) {
		Checker.update(c);
	}
	EXPECT_THAT(Checker.isFullHouse(), IsFalse());
}

TEST_F(CheckerTest, Is3OfAKindWithCorrectCards) {
	std::vector<Card> cards{ Card('K', Suit::Spaders), Card('5', Suit::Spaders), Card('K', Suit::Clubs), Card('A', Suit::Hearts), Card('K', Suit::Diamonds) };

	for (const auto& c : cards) {
		Checker.update(c);
	}
	EXPECT_THAT(Checker.is3OfAKind(), IsTrue());
}

TEST_F(CheckerTest, Is3OfAKindWithInvalidCards) {
	std::vector<Card> cards{ Card('K', Suit::Spaders), Card('2', Suit::Diamonds), Card('3', Suit::Clubs), Card('K', Suit::Hearts), Card('A', Suit::Spaders) };

	for (const auto& c : cards) {
		Checker.update(c);
	}
	EXPECT_THAT(Checker.is3OfAKind(), IsFalse());
}

TEST_F(CheckerTest, IsTwoPairWithCorrectCards) {
	std::vector<Card> cards{ Card('K', Suit::Spaders), Card('5', Suit::Spaders), Card('A', Suit::Clubs), Card('A', Suit::Hearts), Card('K', Suit::Diamonds) };

	for (const auto& c : cards) {
		Checker.update(c);
	}
	EXPECT_THAT(Checker.isTwoPair(), IsTrue());
}

TEST_F(CheckerTest, IsTwoPairWithInvalidCards) {
	std::vector<Card> cards{ Card('K', Suit::Spaders), Card('2', Suit::Diamonds), Card('3', Suit::Clubs), Card('K', Suit::Hearts), Card('A', Suit::Spaders) };

	for (const auto& c : cards) {
		Checker.update(c);
	}
	EXPECT_THAT(Checker.isTwoPair(), IsFalse());
}

TEST_F(CheckerTest, IsOnePairWithCorrectCards) {
	std::vector<Card> cards{ Card('A', Suit::Spaders), Card('A', Suit::Diamonds), Card('3', Suit::Clubs), Card('4', Suit::Hearts), Card('K', Suit::Diamonds) };

	for (const auto& c : cards) {
		Checker.update(c);
	}
	EXPECT_THAT(Checker.isOnePair(), IsTrue());
}

TEST_F(CheckerTest, IsOnePairWithInvalidCards) {
	std::vector<Card> cards{ Card('Q', Suit::Spaders), Card('2', Suit::Diamonds), Card('3', Suit::Clubs), Card('K', Suit::Hearts), Card('A', Suit::Spaders) };

	for (const auto& c : cards) {
		Checker.update(c);
	}
	EXPECT_THAT(Checker.isOnePair(), IsFalse());
}