#include <SFML/Graphics.hpp>
#include "GameEngine.hpp"

int main()
{
	GameEngine ge;
	sf::ContextSettings cs;
	cs.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode((unsigned int)ge.getSize().x, (unsigned int)ge.getSize().y), "SFML works!", sf::Style::Close, cs);
	window.setFramerateLimit(30);
	window.setKeyRepeatEnabled(false);

	while (window.isOpen())
	{
		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				window.close();
			ge.processEvent(e);
		}

		window.clear();
		window.draw(ge);
		window.display();
	}

	return 0;
}
