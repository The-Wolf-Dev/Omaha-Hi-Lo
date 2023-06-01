#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Card.h>
#include <Enums.h>
#include <tuple>

using namespace ::testing;

class CardTest : public Test
{
protected:
	Card card;

	CardTest();
	~CardTest();
};

CardTest::CardTest() : card{ 'Q', 'd' } {

}

CardTest::~CardTest() {

}

class ParseWeightFixture: //public CardTest, // it will generate an error
	public TestWithParam<std::tuple<char, int>>
{
};

class ParseSuitFixture: //public CardTest, // it will generate error
	public TestWithParam<std::tuple<char, Suit>>
{
};

TEST_F(CardTest, ConstructorTest) {
	// should I change access specifier or use member-methods?
	EXPECT_THAT(card.getRank(), Eq('Q'));
	EXPECT_THAT(card.getWeight(), Eq(12));
	EXPECT_THAT(card.getSuit(), Eq(Suit::Diamonds));
}

TEST_F(CardTest, GetRankTest) {
	EXPECT_THAT(card.getRank(), Eq('Q'));
}

TEST_F(CardTest, GetSuitTest) {
	EXPECT_THAT(card.getSuit(), Eq(Suit::Diamonds));
}

TEST_F(CardTest, GetWeightTest) {
	EXPECT_THAT(card.getWeight(), Eq(12));
}

TEST_F(CardTest, SetWeightTest) {
	card.setWeight(1);
	EXPECT_THAT(card.getWeight(), Eq(1));
}

TEST_P(ParseWeightFixture, ParseWeightTest) {
	Card card {'2', 'c'};
	auto param = GetParam();
	EXPECT_THAT(card.parseWeight(std::get<0>(param)), Eq(std::get<1>(param)));
}

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

TEST_P(ParseSuitFixture, ParseSuitTest) {
	Card card{ '2', 'c' };
	auto param = GetParam();
	EXPECT_THAT(card.parseSuit(std::get<0>(param)), Eq(std::get<1>(param)));
}

INSTANTIATE_TEST_SUITE_P(CardTest, ParseSuitFixture, Values(
	std::make_tuple('d', Suit::Diamonds),
	std::make_tuple('s', Suit::Spaders),
	std::make_tuple('c', Suit::Clubs),
	std::make_tuple('h', Suit::Hearts),
	std::make_tuple('a', Suit::None)));

TEST_F(CardTest, OperatorLessThanTest) {
	EXPECT_FALSE(card < Card('2', 's'));
	EXPECT_TRUE(card < Card('K', 'd'));
	EXPECT_FALSE(card < Card('Q', 'd'));
}

TEST_F(CardTest, OperatorGreaterThanTest) {
	EXPECT_TRUE(card > Card('2', 's'));
	EXPECT_FALSE(card > Card('K', 'd'));
	EXPECT_FALSE(card > Card('Q', 'd'));
	
	EXPECT_TRUE(card > 2);
	EXPECT_FALSE(card > 20);
	EXPECT_FALSE(card > 12);
}

TEST_F(CardTest, OperatorEqualTest) {
	EXPECT_TRUE(card == Card('Q', 's'));
	EXPECT_FALSE(card == Card('K', 'd'));

	EXPECT_TRUE(card == 12);
	EXPECT_FALSE(card == 20);
}

TEST_F(CardTest, OperatorNotEqualTest) {
	EXPECT_FALSE(card != Card('Q', 's'));
	EXPECT_TRUE(card != Card('K', 'd'));
}