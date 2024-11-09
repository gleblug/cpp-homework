#include <cmath>
#include <vector>

#include <SFML/Graphics.hpp>

#include "functions.hpp"
#include "system.hpp"

int main(int argc, char ** argv)
{
	sf::RenderWindow window(sf::VideoMode(800U, 600U), "PHYSICS");

	sf::Vector2f min_point(  0.0f,   0.0f);
	sf::Vector2f max_point(775.0f, 575.0f);

	const auto N = 50U;

	const auto R = length(max_point - min_point) * 0.1f;

	const auto C = (min_point + max_point) * 0.5f;

	const auto r = 2.5f;

	std::vector < System::particle_t > particles;

	for (auto i = 0U; i < N; ++i)
	{
		auto angle = 2.0f * 3.141593f / N * i;

		auto position = sf::Vector2f(std::cos(angle), std::sin(angle)) * R + C;

		particles.push_back(std::make_shared < Particle > (position, position,
			sf::Vector2f(0.0f, 10.0f), r));
	}

	System system(min_point, max_point, particles);

	sf::Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		system.update();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			system.push(sf::Vector2f(0.0f, -2.0f));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			system.push(sf::Vector2f(0.0f, 2.0f));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			system.push(sf::Vector2f(-2.0f, 0.0f));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			system.push(sf::Vector2f(2.0f, 0.0f));
		}

		window.clear();

		for (auto i = 0U; i < system.particles().size(); ++i)
		{
			sf::CircleShape circle(2.0f * r);

			circle.setPosition(system.particle(i)->position() + sf::Vector2f(r, r));

			circle.setFillColor(sf::Color::Red);

			window.draw(circle);
		}

		window.display();
	}

	// system("pause");

	return EXIT_SUCCESS;
}
