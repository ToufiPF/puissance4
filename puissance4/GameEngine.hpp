#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

using std::vector;
using std::string;

class GameEngine : public sf::Drawable, public sf::Transformable
{
public:
	enum class Jeton {
		Vide = 0, Jaune, Rouge
	};

	static const sf::Vector2i TAILLE;

public:
	GameEngine();
	~GameEngine();

	void processEvent(const sf::Event &e);

protected:
	bool jouerCoup();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
	vector< vector< Jeton > > mGrille;
	int mSelectedColumn;
	Jeton mJoueurActif;
};
