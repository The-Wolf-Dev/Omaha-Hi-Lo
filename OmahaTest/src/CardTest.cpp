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
	Card testCardAs;

	CardTest();
	~CardTest();
};

CardTest::CardTest() : testCardQd{ Rank::Q, Suit::Diamonds }, testCardAs{ Rank::A, Suit::Spaders } {

}

CardTest::~CardTest() {

}

// testCardQd object consrtructed in fixture with values of:
// m_rank = Rank::Q, m_suit = Suit::Diamonds.
// testCardAs object consrtructed in fixture with values of:
// m_rank = Rank::A, m_suit = Suit::Spaders.
TEST_F(CardTest, ConstructorTest) {
	EXPECT_THAT(testCardQd.getRank(), Eq(Rank::Q));
	EXPECT_THAT(testCardQd.getSuit(), Eq(Suit::Diamonds));

	EXPECT_THAT(testCardAs.getRank(), Eq(Rank::A));
	EXPECT_THAT(testCardAs.getSuit(), Eq(Suit::Spaders));
}

// testCardQd object consrtructed in fixture with values of:
// m_rank = Rank::Q, so testCardQd.getRank() is expected to return Rank::Q.
// testCardAs object consrtructed in fixture with values of:
// m_rank = Rank::A, so testCardAs.getRank() is expected to return Rank::A.
TEST_F(CardTest, GetRankTest) {
	EXPECT_THAT(testCardQd.getRank(), Eq(Rank::Q));
	EXPECT_THAT(testCardAs.getRank(), Eq(Rank::A));
}

// testCardQd object consrtructed in fixture with values of: m_suit = Suit::Diamonds,
// so testCardQd.getSuit() is expected to return Suit::Diamonds.
// testCardAs object consrtructed in fixture with values of: m_suit = Suit::Spaders,
// so testCardAs.getSuit() is expected to return Suit::Spaders.
TEST_F(CardTest, GetSuitTest) {
	EXPECT_THAT(testCardQd.getSuit(), Eq(Suit::Diamonds));
	EXPECT_THAT(testCardAs.getSuit(), Eq(Suit::Spaders));
}

// operator< compares the weights of two cards.
// testCardQd object consrtructed in fixture with value of m_rank = Rank::Q,
// so three cases of weight comparison will be considered:
// 1) 12 (Q) < 2 (2)
// 2) 12 (Q) < 13 (K)
// 3) 12 (Q) < 12 (Q)
TEST_F(CardTest, OperatorLessThanTest) {
	EXPECT_FALSE(testCardQd < Card(Rank::_2, Suit::Spaders));
	EXPECT_TRUE(testCardQd < Card(Rank::K, Suit::Diamonds));
	EXPECT_FALSE(testCardQd < Card(Rank::Q, Suit::Diamonds));
}

// operator> compares the weights of two cards or card and integer.
// testCardQd object consrtructed in fixture with value of m_rank = Rank::Q,
// so six cases of weight comparison will be considered:
// 1) 12 (Q) > 2 (2)
// 2) 12 (Q) > 13 (K)
// 3) 12 (Q) > 12 (Q)
// 4) 12 (Q) > 2
// 5) 12 (Q) > 20
// 6) 12 (Q) > 12
TEST_F(CardTest, OperatorGreaterThanTest) {
	EXPECT_TRUE(testCardQd > Card(Rank::_2, Suit::Spaders));
	EXPECT_FALSE(testCardQd > Card(Rank::K, Suit::Diamonds));
	EXPECT_FALSE(testCardQd > Card(Rank::Q, Suit::Diamonds));
	
	EXPECT_TRUE(testCardQd > Rank::_2);
	EXPECT_FALSE(testCardQd > Rank::K);
	EXPECT_FALSE(testCardQd > Rank::Q);
}

// operator== compares the weights of two cards or card and integer.
// testCardQd object consrtructed in fixture with value of m_rank = Rank::Q,
// so four cases of weight comparison will be considered:
// 1) 12 (Q) == 12 (Q)
// 2) 12 (Q) == 13 (K)
// 3) 12 (Q) == 12
// 4) 12 (Q) == 2
TEST_F(CardTest, OperatorEqualTest) {
	EXPECT_TRUE(testCardQd == Card(Rank::Q, Suit::Spaders));
	EXPECT_FALSE(testCardQd == Card(Rank::K, Suit::Diamonds));

	EXPECT_TRUE(testCardQd == Rank::Q);
	EXPECT_FALSE(testCardQd == Rank::K);
}

// operator!= compares the weights of two cards.
// testCardQd object consrtructed in fixture with value of m_rank = Rank::Q,
// so two cases of weight comparison will be considered:
// 1) 12 (Q) != 12 (Q)
// 2) 12 (Q) != 13 (K)
TEST_F(CardTest, OperatorNotEqualTest) {
	EXPECT_FALSE(testCardQd != Card(Rank::Q, Suit::Spaders));
	EXPECT_TRUE(testCardQd != Card(Rank::K, Suit::Diamonds));
}