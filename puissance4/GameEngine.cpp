#include "GameEngine.hpp"

const sf::Vector2i GameEngine::TAILLE = sf::Vector2i(7, 6);
GameEngine::GameEngine()
{
	mSelectedColumn = TAILLE.x / 2 + 1;

	mGrille.resize(TAILLE.x);
	for (int i = 0; i < TAILLE.x; ++i)
		mGrille[i].resize(TAILLE.y, Jeton::Vide);

	mJoueurActif = Jeton::Jaune;
}
GameEngine::~GameEngine() {
}

void GameEngine::processEvent(const sf::Event & e)
{
	if (e.type == sf::Event::EventType::KeyPressed) {
		switch (e.key.code)
		{
		case sf::Keyboard::Q:
		case sf::Keyboard::Left:
			--mSelectedColumn;
			if (mSelectedColumn < 0)
				mSelectedColumn = TAILLE.x - 1;
			break;
		case sf::Keyboard::D:
		case sf::Keyboard::Right:
			++mSelectedColumn;
			if (mSelectedColumn >= TAILLE.x)
				mSelectedColumn = 0;
			break;
		case sf::Keyboard::Space:
		case sf::Keyboard::Return:
			jouerCoup();
			break;

		default:
			break;
		}
	}
}

bool GameEngine::jouerCoup() {
	return true;
}

void GameEngine::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
}
