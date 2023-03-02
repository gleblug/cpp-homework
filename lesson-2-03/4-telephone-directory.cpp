#include <boost/multi_index/ordered_index_fwd.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index_container_fwd.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/composite_key.hpp>

#include <cstddef>
#include <iostream>

struct Person
{
	std::string name;
	std::string surname;
	size_t phone_number;
};

using Dictionary = boost::multi_index_container<
	Person,
	boost::multi_index::indexed_by<
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<struct SortBySurname>,
        	boost::multi_index::member<Person, decltype(Person::surname), &Person::surname>
        >,
        boost::multi_index::random_access<
            boost::multi_index::tag<struct RandomAccess>
        >,
        boost::multi_index::hashed_non_unique<
            boost::multi_index::tag<struct PersonsByNameAndSurname>,
            boost::multi_index::composite_key<	
                Person,
                boost::multi_index::member<Person, decltype(Person::name), &Person::name>,
                boost::multi_index::member<Person, decltype(Person::surname), &Person::surname>
            >
        >
	>
>;

int main(int argc, char const *argv[])
{
	Dictionary dict{
		{"Job", "Krasniy", 757710},
		{"Job", "Krasniy", 757712},
		{"James", "Siniy", 582122},
		{"Job", "Zeleniy", 353782},
		{"Jinco", "Chorniy", 980562},
		{"Julia", "Gold", 633224}
	};

	// sort by surname for city telephone agency 
	std::cout << "Sort by surname for city phone agency:\n";
	const auto &ordered_surname_dict = dict.get<SortBySurname>();
	for (const auto &p : ordered_surname_dict)
		std::cout << p.surname << " " << p.name << "\t phone: " << p.phone_number << std::endl;


	// random access for advertising agency
	std::cout << "\nRandom acess for advertising agency:\n";
	const auto &random_access_dict = dict.get<RandomAccess>();
	for (size_t i = 0; i < random_access_dict.size(); ++i)
		std::cout 
			<< i << ". " 
			<< random_access_dict[i].name
			<< "   \t phone: " << random_access_dict[i].phone_number << std::endl;


	// fast access by name or surname for users
	std::cout 
		<< "\nAccess by name and surname for users:\n"
		<< "searching by name: 'Job Krasniy'...\n";
	const auto &hashed_name_dict = dict.get<PersonsByNameAndSurname>();
	const auto res = hashed_name_dict.equal_range(boost::make_tuple("Job", "Krasniy"));
	std::for_each(res.first, res.second,
		[](Person const& p)
		{std::cout << p.phone_number << std::endl;}
	);

/* RESULT:

Sort by surname for city phone agency:
Chorniy Jinco	phone: 980562
Gold Julia	 	phone: 633224
Krasniy Job	 	phone: 757710
Krasniy Job	 	phone: 757712
Siniy James	 	phone: 582122
Zeleniy Job	 	phone: 353782

Random acess for advertising agency:
0. Job   	 	phone: 757710
1. Job   	 	phone: 757712
2. James   	 	phone: 582122
3. Job   	 	phone: 353782
4. Jinco   	 	phone: 980562
5. Julia   	 	phone: 633224

Access by name and surname for users:
searching by name: 'Job Krasniy'...
757712
757710

*/

	return 0;
}