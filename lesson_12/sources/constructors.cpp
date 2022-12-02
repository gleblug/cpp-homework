#include <iostream>
#include <string>
#include <utility>

class Person
{
public:
	
	explicit Person(const std::string & name) : 
		m_name(name) 
	{
		std::cout << "copying string for '" << m_name << "'\n";
	}

	explicit Person(std::string && name) : 
		m_name(std::move(name)) 
	{
		std::cout << "moving string for '" << m_name << "'\n";
	}
	
	Person(const Person & person) :
		m_name(person.m_name)
	{
		std::cout << "COPY-CTOR Person '" << m_name << "'\n";
	}

	Person(Person&& p) : 
		m_name(std::move(p.m_name)) 
	{
		std::cout << "MOVE-CTOR Person '" << m_name << "'\n";
	}

	~Person() noexcept = default;

private:

	std::string m_name;
};

int main(int argc, char ** argv)
{
	std::string s = "Ivan";

	Person p1(s);
	Person p2("tmp");
	Person p3(p1);
	Person p4(std::move(p1));

	system("pause");

	return EXIT_SUCCESS;
}