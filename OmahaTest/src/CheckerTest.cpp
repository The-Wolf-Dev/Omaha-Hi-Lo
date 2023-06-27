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

TEST_F(CheckerTest, NewCheckerIsInvalid) {
	EXPECT_THAT(checker.isStraight(), IsFalse());
	EXPECT_THAT(checker.isFlush(), IsFalse());
	EXPECT_THAT(checker.isStraightFlush(), IsFalse());
	EXPECT_THAT(checker.is4OfAKind(), IsFalse());
	EXPECT_THAT(checker.isFullHouse(), IsFalse());
	EXPECT_THAT(checker.is3OfAKind(), IsFalse());
	EXPECT_THAT(checker.isTwoPair(), IsFalse());
	EXPECT_THAT(checker.isOnePair(), IsFalse());
}

TEST_F(CheckerTest, InvalidStraightWithInvalidCards) {
	std::vector<Card> cards{Card(Rank::_5, Suit::Spaders), Card(Rank::A, Suit::Diamonds), Card(Rank::J, Suit::Spaders), Card(Rank::_4, Suit::Spaders), Card(Rank::_5, Suit::Diamonds) };
	checker.update(cards);
	EXPECT_THAT(checker.isStraight(), IsFalse());
}

TEST_F(CheckerTest, InvalidStraightWithValidCards) {
	std::vector<Card> cards{ Card(Rank::_7, Suit::Spaders), Card(Rank::_6, Suit::Clubs), Card(Rank::_5, Suit::Spaders), Card(Rank::_4, Suit::Diamonds), Card(Rank::_3, Suit::Spaders) };
	checker.update(cards);
	EXPECT_THAT(checker.isStraight(), IsTrue());
}


TEST_F(CheckerTest, ValidStraightWithLowAce) {
	std::vector<Card> cards{ Card(Rank::A, Suit::Spaders), Card(Rank::_5, Suit::Spaders), Card(Rank::_4, Suit::Spaders), Card(Rank::_3, Suit::Spaders), Card(Rank::_2, Suit::Spaders) };
	checker.update(cards);
	EXPECT_THAT(checker.isStraight(), IsTrue());
}

TEST_F(CheckerTest, ValidStraightWithHighAce) {
	std::vector<Card> cards{ Card(Rank::A, Suit::Spaders), Card(Rank::K, Suit::Spaders), Card(Rank::Q, Suit::Spaders), Card(Rank::J, Suit::Spaders), Card(Rank::T, Suit::Spaders) };
	checker.update(cards);
	EXPECT_THAT(checker.isStraight(), IsTrue());
}

TEST_F(CheckerTest, ValidFlushWithValidCards) {
	std::vector<Card> cards{ Card(Rank::A, Suit::Spaders), Card(Rank::K, Suit::Spaders), Card(Rank::Q, Suit::Spaders), Card(Rank::J, Suit::Spaders), Card(Rank::T, Suit::Spaders) };
	checker.update(cards);
	EXPECT_THAT(checker.isFlush(), IsTrue());
}

TEST_F(CheckerTest, ValidFlushWithInvalidCards) {
	std::vector<Card> cards{ Card(Rank::A, Suit::Spaders), Card(Rank::K, Suit::Diamonds), Card(Rank::Q, Suit::Spaders), Card(Rank::J, Suit::Clubs), Card(Rank::T, Suit::Spaders) };
	checker.update(cards);
	EXPECT_THAT(checker.isFlush(), IsFalse());
}

TEST_F(CheckerTest, ValidStraightFlushWithValidCards) {
	std::vector<Card> cards{ Card(Rank::A, Suit::Diamonds), Card(Rank::K, Suit::Diamonds), Card(Rank::Q, Suit::Diamonds), Card(Rank::J, Suit::Diamonds), Card(Rank::T, Suit::Diamonds) };
	checker.update(cards);
	EXPECT_THAT(checker.isStraightFlush(), IsTrue());
}

TEST_F(CheckerTest, ValidStraightFlushWithInvalidCards) {
	std::vector<Card> cards{ Card(Rank::_3, Suit::Spaders), Card(Rank::K, Suit::Diamonds), Card(Rank::Q, Suit::Spaders), Card(Rank::J, Suit::Clubs), Card(Rank::T, Suit::Spaders) };
	checker.update(cards);
	EXPECT_THAT(checker.isStraightFlush(), IsFalse());
}

TEST_F(CheckerTest, Valid4OfAKindWithValidCards) {
	std::vector<Card> cards{ Card(Rank::K, Suit::Spaders), Card(Rank::K, Suit::Diamonds), Card(Rank::K, Suit::Clubs), Card(Rank::K, Suit::Hearts), Card(Rank::A, Suit::Spaders) };
	checker.update(cards);
	EXPECT_THAT(checker.is4OfAKind(), IsTrue());
}

TEST_F(CheckerTest, Invalid4OfAKindWithInvalidCards) {
	std::vector<Card> cards{ Card(Rank::K, Suit::Spaders), Card(Rank::_2, Suit::Diamonds), Card(Rank::K, Suit::Clubs), Card(Rank::K, Suit::Hearts), Card(Rank::A, Suit::Spaders) };
	checker.update(cards);
	EXPECT_THAT(checker.is4OfAKind(), IsFalse());
}

TEST_F(CheckerTest, ValidFullHouseWithValidCards) {
	std::vector<Card> cards{ Card(Rank::K, Suit::Spaders), Card(Rank::K, Suit::Diamonds), Card(Rank::K, Suit::Clubs), Card(Rank::A, Suit::Hearts), Card(Rank::A, Suit::Spaders) };
	checker.update(cards);
	EXPECT_THAT(checker.isFullHouse(), IsTrue());
}

TEST_F(CheckerTest, InvalidFullHouseWithInvalidCards) {
	std::vector<Card> cards{ Card(Rank::K, Suit::Spaders), Card(Rank::_2, Suit::Diamonds), Card(Rank::K, Suit::Clubs), Card(Rank::K, Suit::Hearts), Card(Rank::A, Suit::Spaders) };
	checker.update(cards);
	EXPECT_THAT(checker.isFullHouse(), IsFalse());
}

TEST_F(CheckerTest, Valid3OfAKindWithValidCards) {
	std::vector<Card> cards{ Card(Rank::K, Suit::Spaders), Card(Rank::_5, Suit::Spaders), Card(Rank::K, Suit::Clubs), Card(Rank::A, Suit::Hearts), Card(Rank::K, Suit::Diamonds) };
	checker.update(cards);
	EXPECT_THAT(checker.is3OfAKind(), IsTrue());
}

TEST_F(CheckerTest, Invalid3OfAKindWithInvalidCards) {
	std::vector<Card> cards{ Card(Rank::K, Suit::Spaders), Card(Rank::_2, Suit::Diamonds), Card(Rank::_3, Suit::Clubs), Card(Rank::K, Suit::Hearts), Card(Rank::A, Suit::Spaders) };
	checker.update(cards);
	EXPECT_THAT(checker.is3OfAKind(), IsFalse());
}

TEST_F(CheckerTest, ValidTwoPairWithValidCards) {
	std::vector<Card> cards{ Card(Rank::K, Suit::Spaders), Card(Rank::_5, Suit::Spaders), Card(Rank::A, Suit::Clubs), Card(Rank::A, Suit::Hearts), Card(Rank::K, Suit::Diamonds) };
	checker.update(cards);
	EXPECT_THAT(checker.isTwoPair(), IsTrue());
}

TEST_F(CheckerTest, InvalidTwoPairWithInvalidCards) {
	std::vector<Card> cards{ Card(Rank::K, Suit::Spaders), Card(Rank::_2, Suit::Diamonds), Card(Rank::_3, Suit::Clubs), Card(Rank::K, Suit::Hearts), Card(Rank::A, Suit::Spaders) };
	checker.update(cards);
	EXPECT_THAT(checker.isTwoPair(), IsFalse());
}

TEST_F(CheckerTest, ValidOnePairWithValidCards) {
	std::vector<Card> cards{ Card(Rank::A, Suit::Spaders), Card(Rank::A, Suit::Diamonds), Card(Rank::_3, Suit::Clubs), Card(Rank::_4, Suit::Hearts), Card(Rank::K, Suit::Diamonds) };
	checker.update(cards);
	EXPECT_THAT(checker.isOnePair(), IsTrue());
}

TEST_F(CheckerTest, InvalidOnePairWithInvalidCards) {
	std::vector<Card> cards{ Card(Rank::Q, Suit::Spaders), Card(Rank::_2, Suit::Diamonds), Card(Rank::_3, Suit::Clubs), Card(Rank::K, Suit::Hearts), Card(Rank::A, Suit::Spaders) };
	checker.update(cards);
	EXPECT_THAT(checker.isOnePair(), IsFalse());
}

TEST(ComparatorTest, Valid4OfKindWithValidCards) {
	EXPECT_THAT(compr::fourOfKind({ Rank::A, 4 }), IsTrue());
}

TEST(ComparatorTest, Invalid4OfKindWithInvalidCards) {
	EXPECT_THAT(compr::fourOfKind({ Rank::A, 3 }), IsFalse());
}

TEST(ComparatorTest, ValidTripletWithValidCards) {
	EXPECT_THAT(compr::triplet({ Rank::A, 3 }), IsTrue());
}

TEST(ComparatorTest, InvalidTripletWithInvalidCards) {
	EXPECT_THAT(compr::triplet({ Rank::A, 2 }), IsFalse());
}

TEST(ComparatorTest, ValidPairWithValidCards) {
	EXPECT_THAT(compr::pair({ Rank::Q, 2 }), IsTrue());
}

TEST(ComparatorTest, InvalidPairWithInvalidCards) {
	EXPECT_THAT(compr::pair({ Rank::_2, 1 }), IsFalse());
}

class CheckerFixture : public TestWithParam<std::tuple<std::vector<Card>, HighHandRank, std::map<Rank, size_t>>> {
protected:
	Checker checker;
};

TEST_P(CheckerFixture, GetPotentialHighHand) {
	auto hhtuple = GetParam();
	checker.update(std::get<0>(hhtuple));
	HighHand hh = checker.getPotentialHighHand();
	EXPECT_THAT(hh.getRank(), Eq(std::get<1>(hhtuple)));
	EXPECT_THAT(hh.getCards(), Eq(std::get<2>(hhtuple)));
}

INSTANTIATE_TEST_SUITE_P(GetPotentialHighHandParamTest, CheckerFixture, Values(
		std::make_tuple(
			std::vector<Card>({ Card(Rank::A, Suit::Diamonds), Card(Rank::K, Suit::Diamonds), Card(Rank::Q, Suit::Diamonds), Card(Rank::J, Suit::Diamonds), Card(Rank::T, Suit::Diamonds) }),
			HighHandRank::StraightFlush,
			std::map<Rank, size_t>({ {Rank::A, 1ULL}, {Rank::K, 1ULL}, {Rank::Q, 1ULL}, {Rank::J, 1ULL}, {Rank::T, 1ULL} })
		),
		std::make_tuple(
			std::vector<Card>({ Card(Rank::K, Suit::Hearts), Card(Rank::K, Suit::Diamonds), Card(Rank::K, Suit::Spaders), Card(Rank::K, Suit::Clubs), Card(Rank::A, Suit::Hearts) }),
			HighHandRank::FourOfAKind,
			std::map<Rank, size_t>({ {Rank::K, 4ULL}, {Rank::A, 1ULL} })
		),
		std::make_tuple(
			std::vector<Card>({ Card(Rank::A, Suit::Hearts), Card(Rank::A, Suit::Clubs), Card(Rank::A, Suit::Diamonds), Card(Rank::K, Suit::Clubs), Card(Rank::K, Suit::Hearts) }),
			HighHandRank::FullHouse,
			std::map<Rank, size_t>({ {Rank::A, 3ULL}, {Rank::K, 2ULL} })
		),
		std::make_tuple(
			std::vector<Card>({ Card(Rank::_3, Suit::Diamonds), Card(Rank::_6, Suit::Diamonds), Card(Rank::T, Suit::Diamonds), Card(Rank::J, Suit::Diamonds), Card(Rank::K, Suit::Diamonds) }),
			HighHandRank::Flush,
			std::map<Rank, size_t>({ {Rank::_3, 1ULL}, {Rank::K, 1ULL}, {Rank::_6, 1ULL}, {Rank::J, 1ULL}, {Rank::T, 1ULL} })
		),
		std::make_tuple(
			std::vector<Card>({ Card(Rank::A, Suit::Diamonds), Card(Rank::_2, Suit::Hearts), Card(Rank::_3, Suit::Clubs), Card(Rank::_4, Suit::Diamonds), Card(Rank::_5, Suit::Diamonds) }),
			HighHandRank::Straight,
			std::map<Rank, size_t>({ {Rank::LA, 1ULL}, {Rank::_2, 1ULL}, {Rank::_3, 1ULL}, {Rank::_4, 1ULL}, {Rank::_5, 1ULL} })
		),
		std::make_tuple(
			std::vector<Card>({ Card(Rank::A, Suit::Hearts), Card(Rank::K, Suit::Clubs), Card(Rank::_5, Suit::Diamonds), Card(Rank::_5, Suit::Spaders), Card(Rank::_5, Suit::Hearts) }),
			HighHandRank::ThreeOfAKind,
			std::map<Rank, size_t>({ {Rank::A, 1ULL}, {Rank::K, 1ULL}, {Rank::_5, 3ULL} })
		),
		std::make_tuple(
			std::vector<Card>({ Card(Rank::A, Suit::Hearts), Card(Rank::A, Suit::Spaders), Card(Rank::K, Suit::Hearts), Card(Rank::K, Suit::Diamonds), Card(Rank::Q, Suit::Hearts) }),
			HighHandRank::TwoPair,
			std::map<Rank, size_t>({ {Rank::A, 2ULL}, {Rank::K, 2ULL}, {Rank::Q, 1ULL} })
		),
		std::make_tuple(
			std::vector<Card>({ Card(Rank::A, Suit::Spaders), Card(Rank::A, Suit::Hearts), Card(Rank::K, Suit::Hearts), Card(Rank::Q, Suit::Hearts), Card(Rank::J, Suit::Diamonds) }),
			HighHandRank::OnePair,
			std::map<Rank, size_t>({ {Rank::A, 2ULL}, {Rank::K, 1ULL}, {Rank::Q, 1ULL}, {Rank::J, 1ULL} })
		),
		std::make_tuple(
			std::vector<Card>({ Card(Rank::A, Suit::Hearts), Card(Rank::K, Suit::Spaders), Card(Rank::Q, Suit::Hearts), Card(Rank::J, Suit::Clubs), Card(Rank::_9, Suit::Hearts) }),
			HighHandRank::HighCard,
			std::map<Rank, size_t>({ {Rank::A, 1ULL}, {Rank::K, 1ULL}, {Rank::Q, 1ULL}, {Rank::J, 1ULL}, {Rank::_9, 1ULL} })
		)
	));

TEST_F(CheckerTest, UpdateWithBiggerHighHandRank) {
	std::vector<Card> fullHouse{ Card(Rank::A, Suit::Hearts), Card(Rank::A, Suit::Clubs), Card(Rank::A, Suit::Diamonds), Card(Rank::K, Suit::Clubs), Card(Rank::K, Suit::Hearts) };
	
	checker.update(fullHouse);
	
	HighHand hh = checker.getHighHand();
	EXPECT_THAT(checker.getHighHand().getRank(), Eq(HighHandRank::FullHouse));
	EXPECT_THAT(hh.getCards(), Eq(std::map<Rank, size_t>({ {Rank::A, 3}, {Rank::K, 2} })));
}

TEST_F(CheckerTest, UpdateWithEqualHighHandRanks) {
	std::vector<Card> smallerFullHouse{ Card(Rank::K, Suit::Hearts), Card(Rank::K, Suit::Clubs), Card(Rank::K, Suit::Diamonds), Card(Rank::Q, Suit::Clubs), Card(Rank::Q, Suit::Hearts) };
	std::vector<Card> biggerFullHouse{ Card(Rank::A, Suit::Hearts), Card(Rank::A, Suit::Clubs), Card(Rank::A, Suit::Diamonds), Card(Rank::K, Suit::Clubs), Card(Rank::K, Suit::Hearts) };
	
	checker.update(smallerFullHouse);
	checker.update(biggerFullHouse);

	HighHand hh = checker.getHighHand();
	EXPECT_THAT(checker.getHighHand().getRank(), Eq(HighHandRank::FullHouse));
	EXPECT_THAT(hh.getCards(), Eq(std::map<Rank, size_t>({ {Rank::A, 3}, {Rank::K, 2} })));
}

TEST_F(CheckerTest, UpdateWithSmallerHighHandRank) {
	std::vector<Card> biggerFullHouse{ Card(Rank::A, Suit::Hearts), Card(Rank::A, Suit::Clubs), Card(Rank::A, Suit::Diamonds), Card(Rank::K, Suit::Clubs), Card(Rank::K, Suit::Hearts) };
	std::vector<Card> smallerFullHouse{ Card(Rank::K, Suit::Hearts), Card(Rank::K, Suit::Clubs), Card(Rank::K, Suit::Diamonds), Card(Rank::Q, Suit::Clubs), Card(Rank::Q, Suit::Hearts) };
	
	checker.update(biggerFullHouse);
	checker.update(smallerFullHouse);

	HighHand hh = checker.getHighHand();
	EXPECT_THAT(checker.getHighHand().getRank(), Eq(HighHandRank::FullHouse));
	EXPECT_THAT(hh.getCards(), Eq(std::map<Rank, size_t>({ {Rank::A, 3}, {Rank::K, 2} })));
}