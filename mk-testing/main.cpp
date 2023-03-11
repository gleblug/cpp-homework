#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>

class TestClass:
public testing::Test,
public testing::WithParamInterface<std::string> // нужно для параметризованных значением тестов
{
public:
	void SetUp() override
	{
		std::cout << "Preparing to test..." << std::endl;
	}

	void TearDown() override
	{
		std::cout << "End of test." << std::endl;
	}
protected:
	const int number = 5;
};


int Summ(int a, int b)
{
	return a + b;
}


TEST_F(TestClass, test1)
{
	EXPECT_EQ(Summ(2,3), number) << "Something went wrong...";
}

TEST_P(TestClass, test2)
{
	auto param = GetParam();
	std::cout << param << std::endl;
	EXPECT_EQ(Summ(2,3), number) << "Something went wrong...";
}


// параметризованные значением тесты
std::vector<std::string> test_params = {"one", "two", "three"};
INSTANTIATE_TEST_SUITE_P(ValueParamTest, TestClass, testing::ValuesIn(test_params));

TEST(TestSumm, PositiveNumbers)
{
	EXPECT_EQ(Summ(4,5), 9); // non fatal failure
	// ASSERT_EQ(Summ(4,-1), 3); // fatal failure
	EXPECT_EQ(Summ(1,5), 6);
	EXPECT_EQ(Summ(123,123), 246);
}

TEST(TestSumm, NegativeNumbers)
{
	EXPECT_EQ(Summ(-2,-3), -5);
	EXPECT_EQ(Summ(-23,-1), -24);
	EXPECT_EQ(Summ(-111,-1111), -1222);
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}