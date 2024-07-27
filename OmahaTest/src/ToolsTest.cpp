#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Tools.h>

using namespace testing;

class ParseWeightFixture :
	public TestWithParam<std::tuple<char, Rank>>
{
};

class ParseSuitFixture :
	public TestWithParam<std::tuple<char, Suit>>
{
};

// This test uses tuple which contain rank as first value
// and weight of corresponding rank as second value.
// First value is put in the testCardQd.parseWeight(),
// so it is expected to return the second value.
TEST_P(ParseWeightFixture, ParseRankTest) {
	auto param = GetParam();
	EXPECT_THAT(parseRank(std::get<0>(param)), Eq(std::get<1>(param)));
}

// Values for tuple
INSTANTIATE_TEST_SUITE_P(CardTest, ParseWeightFixture, Values(
	std::make_tuple('A', Rank::A),
	std::make_tuple('K', Rank::K),
	std::make_tuple('Q', Rank::Q),
	std::make_tuple('J', Rank::J),
	std::make_tuple('T', Rank::T),
	std::make_tuple('9', Rank::_9),
	std::make_tuple('8', Rank::_8),
	std::make_tuple('7', Rank::_7),
	std::make_tuple('6', Rank::_6),
	std::make_tuple('5', Rank::_5),
	std::make_tuple('4', Rank::_4),
	std::make_tuple('3', Rank::_3),
	std::make_tuple('2', Rank::_2)));

// This test uses tuple which contain char suit as first value
// and corresponding enum Suit value as second value.
// First value is put in the testCardQd.parseSuit(),
// so it is expected to return the second value.
TEST_P(ParseSuitFixture, ParseSuitTest) {
	auto param = GetParam();
	EXPECT_THAT(parseSuit(std::get<0>(param)), Eq(std::get<1>(param)));
}

// Values for tuple
INSTANTIATE_TEST_SUITE_P(CardTest, ParseSuitFixture, Values(
	std::make_tuple('d', Suit::Diamonds),
	std::make_tuple('s', Suit::Spaders),
	std::make_tuple('c', Suit::Clubs),
	std::make_tuple('h', Suit::Hearts),
	std::make_tuple('a', Suit::None)));

TEST(OperatorTest, OperatorLessWithMapsWithTwoPair) {
	std::map<Rank, size_t> smallerCards{
		{ Rank::A, 2ULL },
		{ Rank::_9, 1ULL },
		{ Rank::_6, 2ULL }
	};
	std::map<Rank, size_t> biggerCards{ 
		{ Rank::A, 2ULL },
		{ Rank::J, 2ULL },
		{ Rank::_9, 1ULL }
	};

	EXPECT_THAT(smallerCards < biggerCards, IsTrue());
}

TEST(OperatorTest, OperatorLessWithMapsWithFullHouse) {
	std::map<Rank, size_t> smallerCards{
		{ Rank::A, 2ULL },
		{ Rank::_9, 3ULL },
	};
	std::map<Rank, size_t> biggerCards{
		{ Rank::A, 3ULL },
		{ Rank::_9, 2ULL }
	};

	EXPECT_THAT(smallerCards < biggerCards, IsTrue());
}

TEST(OperatorTest, OperatorLessWithMapsWithStraight) {
	std::map<Rank, size_t> smallerCards{
		{ Rank::A, 1ULL },
		{ Rank::_5, 1ULL },
		{ Rank::_4, 1ULL },
		{ Rank::_3, 1ULL },
		{ Rank::_2, 1ULL }
	};
	std::map<Rank, size_t> biggerCards{
		{ Rank::A, 1ULL },
		{ Rank::K, 1ULL },
		{ Rank::Q, 1ULL },
		{ Rank::J, 1ULL },
		{ Rank::T, 1ULL }
	};

	EXPECT_THAT(smallerCards < biggerCards, IsTrue());
}

TEST(OperatorTest, OperatorLessWithMapsWithEqualStraight) {
	std::map<Rank, size_t> smallerCards{
		{ Rank::A, 1ULL },
		{ Rank::_5, 1ULL },
		{ Rank::_4, 1ULL },
		{ Rank::_3, 1ULL },
		{ Rank::_2, 1ULL }
	};
	std::map<Rank, size_t> biggerCards{
		{ Rank::A, 1ULL },
		{ Rank::_5, 1ULL },
		{ Rank::_4, 1ULL },
		{ Rank::_3, 1ULL },
		{ Rank::_2, 1ULL }
	};

	EXPECT_THAT(smallerCards < biggerCards, IsFalse());
}

TEST(OperatorTest, OperatorLessWithMapsWithDifferentSize) {
	std::map<Rank, size_t> smallerCards{
		{ Rank::A, 2ULL },
		{ Rank::_5, 1ULL },
		{ Rank::_4, 2ULL }
	};
	std::map<Rank, size_t> biggerCards{
		{ Rank::A, 1ULL },
		{ Rank::_5, 1ULL },
		{ Rank::_4, 1ULL },
		{ Rank::_3, 1ULL },
		{ Rank::_2, 1ULL }
	};

	EXPECT_THAT(smallerCards < biggerCards, IsFalse());
}