#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <utility>
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Charge.h"

using namespace std;


/*
 * Stores game constants and objects.
 * Updates game objects.
 */
class Game {
public:
	Game();

	~Game();

	pair<int, int>* getWindowSize();
	pair<double, double>* getMatrixSize();
	int getFps();
	int getStartDelay();
	int getEndDelay();
	double getPlayerLength();
	double getPlayerSpeed();
	double getChargeWidth();
	double getChargeHeight();
	double getChargeSpeed();
	int getTimeCurrent();
	Player* getPlayer();
	vector<Enemy*>* getEnemies();
	vector<Charge*>* getCharges();

	void setTimeCurrent( int gameTimeCurrent );
	void setTimeBase( int gameTimeBase );

	void updatePlayer();
	void updateEnemies();
	void updateCharges();
	void updateCollisions();

private:
	// window and display constants
	pair<int, int>* windowSize;
	pair<double, double>* matrixSize;
	int fps;

	// timer constants
	int startDelay;	// milliseconds
	int endDelay;	// milliseconds

	// player constants
	double playerLength;
	double playerSpeed;

	// enemy constants
	double enemyLength;
	double enemySpeed;
	double enemySpawnRate;	// per second
	int enemyValue;

	// charge constants
	double chargeWidth;
	double chargeHeight;
	double chargeSpeed;

	// timer variables
	int timeCurrent;	// time since glutInit (milliseconds)
	int timeBase;		// time since last frame (milliseconds)

	// game objects
	Player* player;
	vector<Enemy*>* enemies;
	vector<Charge*>* charges;
};


#endif // GAME_H_INCLUDED

