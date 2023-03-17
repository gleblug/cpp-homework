#include "gtest/gtest.h"
#include <regex>

#include <gtest/gtest.h>
#include <utility>


auto is_email(const std::string & string)
{
	std::regex pattern(R"((\w+([.=-]\w+)*)@(([\w-]+[.]){1,2}(\w*[[:alpha:]]+\w*)))");

	std::string domain_name;
	std::regex_replace(std::back_inserter(domain_name), string.begin(), string.end(), pattern, "$3");

	return make_pair(regex_match(string, pattern), domain_name);
}

using param_t = std::pair<std::string, bool>;

class TestClass :
public testing::Test,
public testing::WithParamInterface<param_t>
{
public:
	inline static const std::vector<param_t> email_list{
		{"galera951@gmail.com", true},
		{"landsberg.gs@phystech.edu", true},
		{"landsberg.gs@phystechedu", false},
		{"coffee.c.a.p@busy.office.art", true},
		{"test.domain@my-domain.org", true},
		{"_hel..lo@private.fun", false},
		{"John..Doe@example.com", false},
		{"Jim-Helpert@tyu.run.as.view", false},
		{"ivanov.ak@mipt.123", false},
		{"ivanov.ak@mipt.123m1m1", true},
		{"dasf@as@f.asdwe", false},
		{"03ui87ybwd;o;p0''jfiwe", false},
		{"98jk3b'ap3][-20]1e;", false},
		{"mister--heizenmann@pure.ni", false},
	};
};

INSTANTIATE_TEST_SUITE_P(
	EmailValidationTest, TestClass, 
	testing::ValuesIn(TestClass::email_list)
);

TEST_P(TestClass, RandomEmails)
{
	auto [email, state] = GetParam();
	auto [is_valid, domain] = is_email(email);
	if (is_valid)
		std::cerr << "Domain name: " << domain << std::endl;
	EXPECT_EQ(is_valid, state);
}

TEST(TestText, RandomText)
{

}

int main(int argc, char *argv[])
{
	std::regex pattern(R"((\s\w+([.=-]\w+)*)@(([\w-]+[.]){1,2}(\w*[[:alpha:]]+\w*)))");

	std::string text = R"(
Рабочие email адреса:
1. sarah.brown@school.edu
2. david123@yahoo.com
3. amy-lee@hotmail.dsasd.ds.123
4. jennifer.smith@lawfirm.net
5. peter_jones@outlook.com
6. kate.johnson@consultingfirm.com
7. tom_wilson@techstartup.io
8. john.doe@example.com
9. mike@company.net
10. jane_smith1234@gmail.com
11. peter_jones@outlook.
12. sarah.brown@school.
13. tom_wilson@techstartup.
14. amy-lee@hotmail.com
15. jennifer.smith@lawfirm.
16. david123@
17. john.doe@.com
18. mike@company.
19. kate.johnson@consultingfirm.
20. jane_smith1234@.com)";

	std::copy(
		std::sregex_token_iterator(text.begin(), text.end(), pattern, { 3 }),
		std::sregex_token_iterator(),
		std::ostream_iterator < std::string >(std::cout, "\n"));

	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}