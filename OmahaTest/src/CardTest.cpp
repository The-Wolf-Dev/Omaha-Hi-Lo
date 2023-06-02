#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Card.h>
#include <Enums.h>
#include <tuple>

using namespace ::testing;

class CardTest : public Test
{
protected:
	Card testCardQd;
	Card testCard5s;

	CardTest();
	~CardTest();
};

CardTest::CardTest() : testCardQd{ 'Q', 'd' }, testCard5s{ '5', 's' } {

}

CardTest::~CardTest() {

}

class ParseWeightFixture: //public CardTest, // it will generate an error
	public TestWithParam<std::tuple<char, int>>
{
};

class ParseSuitFixture: //public CardTest, // it will generate an error
	public TestWithParam<std::tuple<char, Suit>>
{
};

// testCardQd object consrtructed in fixture with values of:
// m_rank = 'Q', m_suit = Suit::Diamonds, m_weight = 12.
// testCard5s object consrtructed in fixture with values of:
// m_rank = '5', m_suit = Suit::Spaders, m_weight = 5.
TEST_F(CardTest, ConstructorTest) {
	EXPECT_THAT(testCardQd.getRank(), Eq('Q'));
	EXPECT_THAT(testCardQd.getWeight(), Eq(12));
	EXPECT_THAT(testCardQd.getSuit(), Eq(Suit::Diamonds));

	EXPECT_THAT(testCard5s.getRank(), Eq('5'));
	EXPECT_THAT(testCard5s.getWeight(), Eq(5));
	EXPECT_THAT(testCard5s.getSuit(), Eq(Suit::Spaders));
}

// testCardQd object consrtructed in fixture with values of:
// m_rank = 'Q', so testCardQd.getRank() is expected to return 'Q'.
// testCard5s object consrtructed in fixture with values of:
// m_rank = '5', so testCardQd.getRank() is expected to return '5'.
TEST_F(CardTest, GetRankTest) {
	EXPECT_THAT(testCardQd.getRank(), Eq('Q'));
	EXPECT_THAT(testCard5s.getRank(), Eq('5'));
}

// testCardQd object consrtructed in fixture with values of: m_suit = Suit::Diamonds,
// so testCardQd.getSuit() is expected to return Suit::Diamonds.
// testCard5s object consrtructed in fixture with values of: m_suit = Suit::Spaders,
// so testCardQd.getSuit() is expected to return Suit::Spaders.
TEST_F(CardTest, GetSuitTest) {
	EXPECT_THAT(testCardQd.getSuit(), Eq(Suit::Diamonds));
	EXPECT_THAT(testCard5s.getSuit(), Eq(Suit::Spaders));
}

// testCardQd object consrtructed in fixture with values of: m_rank = 'Q',
// so testCardQd.getWeight() is expected to return 12.
// testCard5s object consrtructed in fixture with values of: m_rank = '5',
// so testCardQd.getWeight() is expected to return 5. 
TEST_F(CardTest, GetWeightTest) {
	EXPECT_THAT(testCardQd.getWeight(), Eq(12));
	EXPECT_THAT(testCard5s.getWeight(), Eq(5));
}

// testCardQd.setWeight(1) call has to set value of m_weight to 1,
// so testCardQd.getWeight() is expected to return 1.
// testCardQd.setWeight(14) call has to set value of m_weight to 14,
// so testCardQd.getWeight() is expected to return 14.
TEST_F(CardTest, SetWeightTest) {
	testCardQd.setWeight(1);
	EXPECT_THAT(testCardQd.getWeight(), Eq(1));
	testCardQd.setWeight(14);
	EXPECT_THAT(testCardQd.getWeight(), Eq(14));
}

// This test uses tuple which contain rank as first value
// and weight of corresponding rank as second value.
// First value is put in the testCardQd.parseWeight(),
// so it is expected to return the second value.
TEST_P(ParseWeightFixture, ParseWeightTest) {
	Card testCardQd {'2', 'c'};
	auto param = GetParam();
	EXPECT_THAT(testCardQd.parseWeight(std::get<0>(param)), Eq(std::get<1>(param)));
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
	Card testCardQd{ '2', 'c' };
	auto param = GetParam();
	EXPECT_THAT(testCardQd.parseSuit(std::get<0>(param)), Eq(std::get<1>(param)));
}

// Values for tuple
INSTANTIATE_TEST_SUITE_P(CardTest, ParseSuitFixture, Values(
	std::make_tuple('d', Suit::Diamonds),
	std::make_tuple('s', Suit::Spaders),
	std::make_tuple('c', Suit::Clubs),
	std::make_tuple('h', Suit::Hearts),
	std::make_tuple('a', Suit::None)));

// operator< compares the weights of two cards.
// testCardQd object consrtructed in fixture with value of m_rank = 'Q',
// so m_weight = 12, so three cases of weight comparison will be considered:
// 1) 12 (Q) < 2 (2)
// 2) 12 (Q) < 13 (K)
// 3) 12 (Q) < 12 (Q)
TEST_F(CardTest, OperatorLessThanTest) {
	EXPECT_FALSE(testCardQd < Card('2', 's'));
	EXPECT_TRUE(testCardQd < Card('K', 'd'));
	EXPECT_FALSE(testCardQd < Card('Q', 'd'));
}

// operator> compares the weights of two cards or card and integer.
// testCardQd object consrtructed in fixture with value of m_rank = 'Q',
// so m_weight = 12, so six cases of weight comparison will be considered:
// 1) 12 (Q) > 2 (2)
// 2) 12 (Q) > 13 (K)
// 3) 12 (Q) > 12 (Q)
// 4) 12 (Q) > 2
// 5) 12 (Q) > 20
// 6) 12 (Q) > 12
TEST_F(CardTest, OperatorGreaterThanTest) {
	EXPECT_TRUE(testCardQd > Card('2', 's'));
	EXPECT_FALSE(testCardQd > Card('K', 'd'));
	EXPECT_FALSE(testCardQd > Card('Q', 'd'));
	
	EXPECT_TRUE(testCardQd > 2);
	EXPECT_FALSE(testCardQd > 20);
	EXPECT_FALSE(testCardQd > 12);
}

// operator== compares the weights of two cards or card and integer.
// testCardQd object consrtructed in fixture with value of m_rank = 'Q',
// so m_weight = 12, so four cases of weight comparison will be considered:
// 1) 12 (Q) == 12 (Q)
// 2) 12 (Q) == 13 (K)
// 3) 12 (Q) == 12
// 4) 12 (Q) == 2
TEST_F(CardTest, OperatorEqualTest) {
	EXPECT_TRUE(testCardQd == Card('Q', 's'));
	EXPECT_FALSE(testCardQd == Card('K', 'd'));

	EXPECT_TRUE(testCardQd == 12);
	EXPECT_FALSE(testCardQd == 20);
}

// operator!= compares the weights of two cards.
// testCardQd object consrtructed in fixture with value of m_rank = 'Q',
// so m_weight = 12, so two cases of weight comparison will be considered:
// 1) 12 (Q) != 12 (Q)
// 2) 12 (Q) != 13 (K)
TEST_F(CardTest, OperatorNotEqualTest) {
	EXPECT_FALSE(testCardQd != Card('Q', 's'));
	EXPECT_TRUE(testCardQd != Card('K', 'd'));
}