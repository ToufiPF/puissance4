#include "GameEngine.hpp"

const sf::Color GameEngine::BACKGROUND_COLOR(120, 120, 120);
const sf::Color GameEngine::GRID_COLOR(20, 20, 250);
const sf::Color GameEngine::JET_JAUNE_COLOR(200, 200, 50);
const sf::Color GameEngine::JET_ROUGE_COLOR(250, 30, 15);

const sf::Vector2i GameEngine::GRIDSIZE = sf::Vector2i(7, 6);
const float GameEngine::JETON_RADIUS = 25.f;
const float GameEngine::OFFSET_GRID = GameEngine::JETON_RADIUS * 2 + 20;
const float GameEngine::CASE_SIZE = GameEngine::JETON_RADIUS * 2 + 2 * 7.5f;

const double PI = 3.14159265358979323846;

GameEngine::GameEngine()
{
	mSelectedColumn = GRIDSIZE.x / 2;

	mGrid.resize(GRIDSIZE.x);
	for (int i = 0; i < GRIDSIZE.x; ++i)
		mGrid[i].resize(GRIDSIZE.y, Jeton::Vide);

	mBackgroundShape.setPosition(0, 0);
	mBackgroundShape.setSize(getSize());
	mBackgroundShape.setFillColor(BACKGROUND_COLOR);

	mGridShape.setPosition(0, OFFSET_GRID);
	mGridShape.setSize(sf::Vector2f(GRIDSIZE.x * CASE_SIZE, GRIDSIZE.y * CASE_SIZE));
	mGridShape.setFillColor(GRID_COLOR);

	mJetonVide.setPointCount(20);
	mJetonVide.setFillColor(BACKGROUND_COLOR);
	mJetonVide.setRadius(JETON_RADIUS);

	mJetonJaune.setPointCount(20);
	mJetonJaune.setFillColor(JET_JAUNE_COLOR);
	mJetonJaune.setRadius(JETON_RADIUS);

	mJetonRouge.setPointCount(20);
	mJetonRouge.setFillColor(JET_ROUGE_COLOR);
	mJetonRouge.setRadius(JETON_RADIUS);

	mJoueurActif = Jeton::Jaune;
}
GameEngine::~GameEngine() {
}

void GameEngine::processEvent(const sf::Event & e) {
	if (e.type == sf::Event::EventType::KeyPressed) {
		bool gameEnded = false;
		Jeton gagnant = Jeton::Vide;

		switch (e.key.code)
		{
		case sf::Keyboard::Q:
		case sf::Keyboard::Left:
			--mSelectedColumn;
			if (mSelectedColumn < 0)
				mSelectedColumn = GRIDSIZE.x - 1;
			break;
		case sf::Keyboard::D:
		case sf::Keyboard::Right:
			++mSelectedColumn;
			if (mSelectedColumn >= GRIDSIZE.x)
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

void GameEngine::jouerCoup()
{
	mGameEnded = false;
	mGagnant = Jeton::Vide;

	if (placerJeton()) {
		mGagnant = checkPuissance4();
		if (mGagnant == Jeton::Jaune)
			mGameEnded = true;
		else if (mGagnant == Jeton::Rouge)
			mGameEnded = true;
		else if (checkGridFull())
			mGameEnded = true;

		if (mGameEnded)
			return;

		if (mJoueurActif == Jeton::Jaune)
			mJoueurActif = Jeton::Rouge;
		else
			mJoueurActif = Jeton::Jaune;
	}
}

bool GameEngine::placerJeton()
{
	for (RevVectIt rIt = mGrid.at(mSelectedColumn).rbegin(); rIt != mGrid.at(mSelectedColumn).rend(); ++rIt) {
		if (*rIt == Jeton::Vide) {
			*rIt = mJoueurActif;
			return true;
		}
	}
	return false;
}
bool GameEngine::checkGridFull() const
{
	for (int x = 0; x < GRIDSIZE.x; ++x)
		for (int y = 0; y < GRIDSIZE.y; ++y)
			if (mGrid.at(x).at(y) == Jeton::Vide)
				return false;
	return true;
}
GameEngine::Jeton GameEngine::checkPuissance4() const
{
	return Jeton::Vide;
}

void GameEngine::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mBackgroundShape, states);
	target.draw(mGridShape, states);

	sf::RenderStates stateJeton(states);
	for (int x = 0; x < GRIDSIZE.x; ++x) {
		for (int y = 0; y < GRIDSIZE.y; ++y) {
			stateJeton.transform = states.transform *
				sf::Transform().translate(x * CASE_SIZE + CASE_SIZE / 2 - JETON_RADIUS, OFFSET_GRID + y * CASE_SIZE + CASE_SIZE / 2 - JETON_RADIUS);

			if (mGrid.at(x).at(y) == Jeton::Jaune)
				target.draw(mJetonJaune, stateJeton);
			else if (mGrid.at(x).at(y) == Jeton::Rouge)
				target.draw(mJetonRouge, stateJeton);
			else
				target.draw(mJetonVide, stateJeton);
		}
	}
	stateJeton.transform = states.transform * sf::Transform().translate(mSelectedColumn * CASE_SIZE + CASE_SIZE / 2 - JETON_RADIUS, OFFSET_GRID / 2 - JETON_RADIUS);
	if (mJoueurActif == Jeton::Jaune)
		target.draw(mJetonJaune, stateJeton);
	else if (mJoueurActif == Jeton::Rouge)
		target.draw(mJetonRouge, stateJeton);
}
