#include <iostream>

template < class Derived >
class Figure
{
public:

	Derived * self()
	{
		return static_cast < Derived * > (this);
	}

	void draw()
	{
		self()->draw_implementation();
	}
};

class Circle : public Figure < Circle >
{
public:
	void draw_implementation()
	{
		std::cout << "Drawing circle..." << std::endl;
	}
};

class Triangle : public Figure < Triangle >
{
public:
	void draw_implementation()
	{
		std::cout << "Drawing triangle..." << std::endl;
	}
};

template < typename T >
void render(T & figure)
{
	std::cout << "Rendering..." << std::endl;

	figure.draw();
}

int main(int argc, char ** argv)
{
	Circle circle;
	Triangle triangle;
	
	render(circle);
	render(triangle);

	return EXIT_SUCCESS;
}