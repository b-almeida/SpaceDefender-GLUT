#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <utility>
#include "Enemy.h"

using namespace std;


/*
 * Player game object.
 * Can move horizontally and fire charges.
 * Can be destroyed by an enemy.
 */
class Player {
public:
	Player( double playerXPos, double playerYPos, double playerLength, double playerMaxSpeed, pair<double, double>* matrixSize );

	double getXPos();
	double getYPos();
	double getLength();
	double getHeight();
	double getMaxSpeed();
	double getSpeed();
	unsigned int getScore();

	void setXPos( double playerXPos, pair<double, double>* matrixSize );
	void setSpeed( double playerSpeed );
	void setScore( unsigned int playerScore );

	bool isCollidingWith( Enemy* enemy );

private:
	double xPos;	// triangle centre
	double yPos;	// triangle centre
	double length;	// of triangle
	double height;	// of triangle
	double maxSpeed;
	double speed;
	unsigned int score;
};


#endif // PLAYER_H_INCLUDED

