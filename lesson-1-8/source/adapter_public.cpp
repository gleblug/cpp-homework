#include <iostream>

class Fahrenheit_Sensor
{
public:
	double get_temperature() const
	{
		double t = 451.0;
		// ...
		return t;
	}
};

class Sensor
{
public:
	virtual double get_temperature() const = 0;
	virtual ~Sensor() = default;
};

class Adapter : public Sensor
{
public:
	explicit Adapter(Fahrenheit_Sensor * ptr) : m_ptr(ptr)
	{}
	~Adapter()
	{
		delete m_ptr;
	}
	virtual double get_temperature() const override
	{
		return (m_ptr->get_temperature() - 32.0) * 5.0 / 9.0;
	}
private:
	Fahrenheit_Sensor * m_ptr;
};

int main()
{
	Sensor * p = new Adapter(new Fahrenheit_Sensor);

	std::cout << "Celsius temperature = " << p->get_temperature() << std::endl;

	delete p;

	system("pause");

	return EXIT_SUCCESS;
}