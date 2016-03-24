#include <iostream>
#include <cstdlib>
#include <ctime>
#include <utility>
#include <vector>
#include <stdexcept>
#include "Player.h"
#include "Enemy.h"
#include "Charge.h"

#include "Game.h"

using namespace std;


/*
 * Constructor method.
 */
Game::Game() {
	windowSize = new pair<int, int> ( 800, 800 );
	matrixSize = new pair<double, double> ( 400.0, 400.0 );
	fps = 60;

	startDelay = 5000;
	endDelay = 5000;

	playerLength = 50.0;
	playerSpeed = 200.0;

	enemyLength = 40.0;
	enemySpeed = 50.0;
	enemySpawnRate = 2.0;
	enemyValue = 100;

	chargeWidth = 1.0;
	chargeHeight = 20.0;
	chargeSpeed = 1000.0;

	timeCurrent = 0;
	timeBase = 0;

	try {
		player = new Player( matrixSize->first / 2.0,
							playerLength / 2.0,
							playerLength,
							playerSpeed,
							matrixSize );
		enemies = new vector<Enemy*>;
		charges = new vector<Charge*>;
	}
	catch (runtime_error& e) {
		cout << e.what() << endl;
	}

	// generate random number sequence
	srand( time( NULL ) );
}

/*
 * Destructor method.
 */
Game::~Game() {
	delete windowSize;
	delete matrixSize;

	delete player;
	for ( int iEnemy = 0; iEnemy < enemies->size(); iEnemy++ )
		delete enemies->at( iEnemy );
	for ( int iCharge = 0; iCharge < charges->size(); iCharge++ )
		delete charges->at( iCharge );
}

/*
 * Getter methods.
 */
pair<int, int>* Game::getWindowSize() {
	return windowSize;
}
pair<double, double>* Game::getMatrixSize() {
	return matrixSize;
}
int Game::getFps() {
	return fps;
}
int Game::getStartDelay() {
	return startDelay;
}
int Game::getEndDelay() {
	return endDelay;
}
double Game::getPlayerLength() {
	return playerLength;
}
double Game::getPlayerSpeed() {
	return playerSpeed;
}
double Game::getChargeWidth() {
	return chargeWidth;
}
double Game::getChargeHeight() {
	return chargeHeight;
}
double Game::getChargeSpeed() {
	return chargeSpeed;
}
int Game::getTimeCurrent() {
	return timeCurrent;
}
Player* Game::getPlayer() {
	return player;
}
vector<Enemy*>* Game::getEnemies() {
	return enemies;
}
vector<Charge*>* Game::getCharges() {
	return charges;
}

/*
 * Setter methods.
 */
void Game::setTimeCurrent( int gameTimeCurrent ) {
	if ( gameTimeCurrent >= 0 )
		timeCurrent = gameTimeCurrent;
	else
		throw runtime_error{ "Error: Game.timeCurrent must be greater than or equal to 0." };
}
void Game::setTimeBase( int gameTimeBase ) {
	if ( gameTimeBase >= 0 )
		timeBase = gameTimeBase;
	else
		throw runtime_error{ "Error: Game.timeBase must be greater than or equal to 0." };
}

/*
 * Updates player (once per frame).
 */
void Game::updatePlayer() {
	// update player position (within window boundaries)
	double xPos = player->getXPos() + (player->getSpeed() * (timeCurrent - timeBase) / 1000.0);
	xPos = max( xPos, player->getLength() / 2.0 );							// check left window edge
	xPos = min( xPos, matrixSize->first - (player->getLength() / 2.0) );	// check right window edge

	try {
		player->setXPos( xPos, matrixSize );
	}
	catch (runtime_error& e) {
		cout << e.what() << endl;
	}

}

/*
 * Updates enemies (once per frame).
 */
void Game::updateEnemies() {
	// update enemy positions
	for ( int iEnemy = 0; iEnemy < enemies->size(); iEnemy++ ) {
		Enemy* enemy = enemies->at( iEnemy );

		enemy->setYPos( enemy->getYPos() - (enemy->getSpeed() * (timeCurrent - timeBase) / 1000.0) );
	}

	// create new enemy if random number is 0
	bool addEnemy = (rand() % (int)(fps / enemySpawnRate) == 0);
	while ( addEnemy ) {
		// create test enemy
		Enemy* newEnemy = NULL;
		try {
			newEnemy = new Enemy( rand() % (int)(matrixSize->first - enemyLength + 1.0) + (enemyLength / 2.0),
										matrixSize->second - (enemyLength / 2.0),
										enemyLength,
										enemySpeed,
										enemyValue,
										matrixSize );
		}
		catch (runtime_error& e) {
			cout << e.what() << endl;
		}

		// if test enemy does not collide with another enemy, add it to enemy list
		bool isColliding = false;

		for ( int iEnemy = 0; iEnemy < enemies->size(); iEnemy++ ) {
			Enemy* enemy = enemies->at( iEnemy );

			if ( enemy->isCollidingWith( newEnemy ) ) {
				isColliding = true;
				break;
			}
		}

		if ( !isColliding ) {
			enemies->push_back( newEnemy );
			addEnemy = false;
		}
	}
}

/*
 * Updates charges (once per frame).
 */
void Game::updateCharges() {
	// update charge positions
	for ( int iCharge = 0; iCharge < charges->size(); iCharge++ ) {
		Charge* charge = charges->at( iCharge );

		charge->setYPos( charge->getYPos() + (charge->getSpeed() * (timeCurrent - timeBase) / 1000.0) );
	}

	// delete charges that go off screen
	for ( int iCharge = charges->size() - 1; iCharge >= 0; iCharge-- ) {
		Charge* charge = charges->at( iCharge );

		if ( charge->getYPos() + (charge->getHeight() / 2.0) > matrixSize->second ) {
			delete charge;
			charges->erase( charges->begin() + iCharge );
		}
	}
}

/*
 * Detects enemy/charge collisions. Updates enemies, charges, and score (once per frame).
 */
void Game::updateCollisions() {
	// delete enemies and charges that collide, update score
	for ( int iEnemy = enemies->size() - 1; iEnemy >= 0; iEnemy-- ) {
		Enemy* enemy = enemies->at( iEnemy );

		for ( int iCharge = charges->size() - 1; iCharge >= 0; iCharge-- ) {
			Charge* charge = charges->at( iCharge );

			if ( enemy->isCollidingWith( charge ) ) {
				player->setScore( player->getScore() + enemy->getValue() );

				delete enemy;
				enemies->erase( enemies->begin() + iEnemy );

				delete charge;
				charges->erase( charges->begin() + iCharge );

				break;
			}
		}
	}
}

