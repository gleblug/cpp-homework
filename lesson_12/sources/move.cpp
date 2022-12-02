#include <iostream>
#include <utility>

class X {};

void g(X &) 
{
	std::cout << "g() for variable\n";
}

void g(const X &)
{
	std::cout << "g() for constant\n";
}

void g(X &&) 
{
	std::cout << "g() for movable object\n";
}

void f(X & v) 
{
	g(v);
}

void f(const X & v) 
{
	g(v);
}

void f(X && v) 
{
	g(std::move(v));
}

int main(int argc, char ** argv)
{
	X v;
	const X c;

	f(v);             // f() for nonconstant object calls f(X &) => calls g(X &)
	f(c);             // f() for constant object calls f(const X &) => calls g(const X &)
	f(X());           // f() for temporary calls f(X &&) => calls g(X &&)
	f(std::move(v));  // f() for movable variable calls f(X &&) => calls g(X &&)

	system("pause");

	return EXIT_SUCCESS;
}