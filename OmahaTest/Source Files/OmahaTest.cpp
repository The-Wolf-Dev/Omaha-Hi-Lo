#include <gtest/gtest.h>
#include <fstream>
#include <string>

class OmahaTest : public ::testing::Test {
protected:
	std::ifstream actualOutput;
	std::ifstream expectedOutput;
	OmahaTest() : actualOutput{ "../../../../output.txt" },
		expectedOutput{ "../../../../expected_output.txt" } {
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