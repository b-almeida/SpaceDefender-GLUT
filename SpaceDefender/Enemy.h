#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include <utility>
#include "Charge.h"

using namespace std;


/*
 * Enemy game object.
 * Can move vertically and destroy player.
 * Can be destroyed by a charge.
 */
class Enemy {
public:
	Enemy( double enemyXPos, double enemyYPos, double enemyLength, double enemySpeed, int enemyValue, pair<double, double>* matrixSize );

	double getXPos();
	double getYPos();
	double getLength();
	double getHeight();
	double getSpeed();
	int getValue();

	void setYPos( double enemyYPos );

	bool isCollidingWith( Enemy* enemy );
	bool isCollidingWith( Charge* charge );

private:
	double xPos;	// triangle centre
	double yPos;	// triangle centre
	double length;	// of triangle
	double height;	// of triangle
	double speed;
	int value;		// score
};


#endif // ENEMY_H_INCLUDED

