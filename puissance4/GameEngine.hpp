#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <cmath>

using std::string;

class GameEngine : public sf::Drawable, public sf::Transformable
{
public:
	enum class Jeton {
		Vide = 0, Jaune, Rouge
	};

protected:
	static const sf::Color BACKGROUND_COLOR;
	static const sf::Color GRID_COLOR;
	static const sf::Color JET_JAUNE_COLOR;
	static const sf::Color JET_ROUGE_COLOR;

	static const sf::Vector2i GRIDSIZE;
	static const float JETON_RADIUS;
	static const float OFFSET_GRID;
	static const float CASE_SIZE;

	typedef std::vector< Jeton >::iterator VectIt;
	typedef std::vector< Jeton >::reverse_iterator RevVectIt;

	typedef std::vector< std::vector< Jeton > >::iterator VectVectIt;
	typedef std::vector< std::vector< Jeton > >::reverse_iterator RevVectVectIt;

public:
	GameEngine();
	~GameEngine();

	void reset();

	void processEvent(const sf::Event &e);

	bool isGameEnded() const { return mGameEnded; }
	Jeton getGagnant() const { return mGagnant; }

	sf::Vector2f getSize() const { return sf::Vector2f(GRIDSIZE.x * CASE_SIZE, OFFSET_GRID + GRIDSIZE.y * CASE_SIZE); }

protected:
	void jouerCoup();

	bool placerJeton();
	bool checkGridFull() const;
	Jeton checkPuissance4() const;
	bool check4Aligne(Jeton couleur, sf::Vector2i pos) const;
	bool check4Aligne(Jeton couleur, sf::Vector2i pos, sf::Vector2i increment) const;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:
	std::vector< std::vector< Jeton > > mGrid;
	sf::RectangleShape mBackgroundShape;
	sf::RectangleShape mGridShape;

	sf::CircleShape mJetonVide;
	sf::CircleShape mJetonJaune;
	sf::CircleShape mJetonRouge;

	bool mGameEnded;
	Jeton mGagnant;

	int mSelectedColumn;
	Jeton mJoueurActif;
};
