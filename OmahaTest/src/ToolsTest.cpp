#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Tools.h>

using namespace testing;

class ParseWeightFixture : //public CardTest, // it will generate an error
	public TestWithParam<std::tuple<char, int>>
{
};

class ParseSuitFixture : //public CardTest, // it will generate an error
	public TestWithParam<std::tuple<char, Suit>>
{
};

// This test uses tuple which contain rank as first value
// and weight of corresponding rank as second value.
// First value is put in the testCardQd.parseWeight(),
// so it is expected to return the second value.
TEST_P(ParseWeightFixture, ParseWeightTest) {
	auto param = GetParam();
	EXPECT_THAT(parseWeight(std::get<0>(param)), Eq(std::get<1>(param)));
}

// Values for tuple
INSTANTIATE_TEST_SUITE_P(CardTest, ParseWeightFixture, Values(
	std::make_tuple('A', 14),
	std::make_tuple('K', 13),
	std::make_tuple('Q', 12),
	std::make_tuple('J', 11),
	std::make_tuple('T', 10),
	std::make_tuple('9', 9),
	std::make_tuple('8', 8),
	std::make_tuple('7', 7),
	std::make_tuple('6', 6),
	std::make_tuple('5', 5),
	std::make_tuple('4', 4),
	std::make_tuple('3', 3),
	std::make_tuple('2', 2)));

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