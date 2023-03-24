#include <fstream>
#include <iterator>
#include <string>
#include <iostream>

#include <boost/algorithm/string.hpp>

#include "../json.hpp"


using nlohmann::json;

class Person
{
public:	
	std::string get_alias() const
	{
		return boost::algorithm::to_lower_copy(name + "-" + surname);
	}

	void save_json() const
	{
		auto filename = get_alias() + std::string(".json");

		json json_data;
		std::ofstream file(filename);

		json_data["name"] = name;
		json_data["surname"] = surname;
		json_data["age"] = age;
		json_data["city"] = city;

		file << json_data;
	}
private:
	friend std::istream &operator>>(std::istream &input, Person &person);

	std::string name;
	std::string surname;
	size_t age;
	std::string city;
};

std::istream &operator>>(std::istream &input, Person &person)
{
	input >> person.name >> person.surname >> person.age >> person.city;
	return input;
}

int main(int argc, char const *argv[])
{
	std::cout << "Enter a person info: name, surname, age and city." << std::endl; 

	std::vector<Person> persons;
	while (std::cin)
	{
		Person person;
		std::cin >> person;
		if (std::cin.good())
			persons.push_back(person);
	}

	for (const auto &p : persons)
		p.save_json();

	return 0;
}