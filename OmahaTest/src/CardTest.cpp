#include <gtest/gtest.h>
#include <Card.h>
#include <Enums.h>

class CardTest: public ::testing::Test
{
protected:
	Card card;

	CardTest();
	~CardTest();
};

CardTest::CardTest() : card{ '2', 'c' } {};
CardTest::~CardTest() {};

TEST_F(CardTest, RankCheck) {
	ASSERT_EQ(card.getRank(), '2');
}

TEST_F(CardTest, SuitCheck) {
	ASSERT_EQ(card.getSuit(), Suit::Clubs);
}