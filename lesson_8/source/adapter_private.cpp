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
	virtual ~Sensor() = default;
	virtual double get_temperature() const = 0;
};

class Adapter : public Sensor, private Fahrenheit_Sensor
{
public:
	Adapter() = default;
	virtual double get_temperature() const override
	{
		return (Fahrenheit_Sensor::get_temperature() - 32.0) * 5.0 / 9.0;
	}
};

int main()
{
	Sensor * p = new Adapter();

	std::cout << "Celsius temperature = " << p->get_temperature() << std::endl;

	delete p;

	system("pause");

	return EXIT_SUCCESS;
}