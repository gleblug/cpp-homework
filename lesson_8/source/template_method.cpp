#include <iostream>
#include <vector>

class Base
{
private:
	void a() const
	{
		std::cout << "a ";
	}
	void c() const
	{
		std::cout << "c ";
	}
	void e() const
	{
		std::cout << "e ";
	}
	virtual void step_1() const = 0;
	virtual void step_2() const = 0;
public:
	void execute() const
	{
		a();
		step_1();
		c();
		step_2();
		e();
	}
};

class One : public Base
{
	virtual void step_1() const override
	{
		std::cout << "b ";
	}
	virtual void step_2() const override
	{
		std::cout << "d ";
	}
};

class Two : public Base
{
	virtual void step_1() const override
	{
		std::cout << "B ";
	}
	virtual void step_2() const override
	{
		std::cout << "D ";
	}
};

int main(int argc, char ** argv)
{
	std::vector < Base * > v;

	v.push_back(new One());
	v.push_back(new Two());

	for (auto i = 0U; i < v.size(); ++i)
	{
		v[i]->execute();

		std::cout << std::endl;
	}

	for (auto i = 0U; i < v.size(); ++i)
	{
		delete v[i];
	}

	system("pause");

	return EXIT_SUCCESS;
}
