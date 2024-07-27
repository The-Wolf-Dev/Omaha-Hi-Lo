#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <Poker.h>

class OmahaTest : public ::testing::Test {
protected:
	std::ifstream actualOutput;
	std::ifstream expectedOutput;
	OmahaTest() : actualOutput{ "C:/Users/akolchenko/source/repos/Omaha-Hi-Lo/output.txt" },
		expectedOutput{ "C:/Users/akolchenko/source/repos/Omaha-Hi-Lo/expected_output.txt" } {
	}

	~OmahaTest() {
		actualOutput.close();
		expectedOutput.close();
	}
};

TEST_F(OmahaTest, CorrectOutput) {
	ASSERT_TRUE(actualOutput.is_open());
	ASSERT_TRUE(expectedOutput.is_open());
	ASSERT_NE(actualOutput.peek(), std::ifstream::traits_type::eof()) << "Message: output.txt is empty";
	//ASSERT_FALSE(actualOutput.eof()) << "Message: output.txt is empty";

	std::string actualLine, expectedLine;
	while (std::getline(actualOutput, actualLine) && std::getline(expectedOutput, expectedLine)) {
		ASSERT_EQ(actualLine, expectedLine);
	}
}

//TEST(PokerTest, PokerTestWithCards) {
//	Poker poker("Qh-4d-Tc-8s", "Qc-8c-7d-2h", "Ad-As-3c-3d-5d");
//	poker.findWinner();
//}