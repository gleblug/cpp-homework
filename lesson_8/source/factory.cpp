#include <iostream>
#include <vector>

class Employee
{
public:
	virtual void print() const = 0;
	virtual ~Employee() = default;
};

class Developer : public Employee
{
public:
	virtual void print() const override
	{
		std::cout << "Developer" << std::endl;
	};
};

class Manager : public Employee
{
public:
	virtual void print() const override
	{
		std::cout << "Manager" << std::endl;
	};
};

class Engineer : public Employee
{
public:
	virtual void print() const override
	{
		std::cout << "Engineer" << std::endl;
	};
};

class Factory
{
public:
	virtual Employee * create() const = 0;
	virtual ~Factory() = default;
};

class Developer_Factory : public Factory
{
public:
	virtual Employee * create() const override
	{
		return new Developer;
	}
};

class Manager_Factory : public Factory
{
public:
	virtual Employee * create() const override
	{
		return new Manager;
	}
};

class Engineer_Factory : public Factory
{
public:
	virtual Employee * create() const override
	{
		return new Engineer;
	}
};

int main(int argc, char ** argv)
{
	Developer_Factory * developer_factory = new Developer_Factory;
	Manager_Factory   * manager_factory   = new Manager_Factory;
	Engineer_Factory  * engineer_factory  = new Engineer_Factory;

	std::vector < Employee * > employees;

	employees.push_back(developer_factory->create());
	employees.push_back(manager_factory  ->create());
	employees.push_back(engineer_factory ->create());

	for (auto i = 0U; i < employees.size(); ++i)
	{
		employees[i]->print();
	}

	for (auto i = 0U; i < employees.size(); ++i)
	{
		delete employees[i];
	}

	delete developer_factory;
	delete manager_factory;
	delete engineer_factory;

	system("pause");

	return EXIT_SUCCESS;
}