#include <utility>
#include <cmath>
#include <stdexcept>
#include "Charge.h"

#include "Enemy.h"

using namespace std;


/*
 * Constructor method.
 */
Enemy::Enemy( double enemyXPos, double enemyYPos, double enemyLength, double enemySpeed, int enemyValue, pair<double, double>* matrixSize ) {
	if ( ( 0 <= enemyXPos ) && ( enemyXPos <= matrixSize->first ) )
		xPos = enemyXPos;
	else
		throw runtime_error{ "Error: Enemy.xPos must be within bounds of matrixSize." };

	yPos = enemyYPos;

	if ( enemyLength >= 0 )
		length = enemyLength;
	else
		throw runtime_error{ "Error: Enemy.length must be greater than or equal to 0." };

	height = sqrt( pow( length, 2 ) - pow( length / 2.0, 2 ) );

	if ( enemySpeed >= 0 )
		speed = enemySpeed;
	else
		throw runtime_error{ "Error: Enemy.speed must be greater than or equal to 0." };

	if ( enemyValue >= 0 )
		value = enemyValue;
	else
		throw runtime_error{ "Error: Enemy.value must be greater than or equal to 0." };
}

/*
 * Getter methods.
 */
double Enemy::getXPos() {
	return xPos;
}
double Enemy::getYPos() {
	return yPos;
}
double Enemy::getLength() {
	return length;
}
double Enemy::getHeight() {
	return height;
}
double Enemy::getSpeed() {
	return speed;
}
int Enemy::getValue() {
	return value;
}

/*
 * Setter method.
 */
void Enemy::setYPos( double enemyYPos ) {
	yPos = enemyYPos;
}

/*
 * Returns true if enemy is colliding with other enemy.
 */
bool Enemy::isCollidingWith( Enemy* enemy ) {
	if (  sqrt( pow( xPos - enemy->xPos, 2 ) + pow( yPos - enemy->yPos, 2 ) )  <  ( (height + enemy->height) / 2.0 )  )
		return true;
	else
		return false;
}

/*
 * Returns true if enemy is colliding with charge.
 */
bool Enemy::isCollidingWith( Charge* charge ) {
	if ( abs( xPos - charge->getXPos() ) < ( ( length + charge->getWidth() ) / 2.0 ) &&
		 abs( yPos - charge->getYPos() ) < ( ( height + charge->getHeight() ) / 2.0 ) )
		return true;
	else
		return false;
}

