#include <utility>
#include <cmath>
#include <stdexcept>
#include "Enemy.h"

#include "Player.h"

using namespace std;


/*
 * Constructor method.
 */
Player::Player( double playerXPos, double playerYPos, double playerLength, double playerMaxSpeed, pair<double, double>* matrixSize ) {
	if ( ( 0 <= playerXPos ) && ( playerXPos <= matrixSize->first ) )
		xPos = playerXPos;
	else
		throw runtime_error{ "Error: Player.xPos must be within bounds of matrixSize." };

	if ( ( 0 <= playerYPos ) && ( playerYPos <= matrixSize->second ) )
		yPos = playerYPos;
	else
		throw runtime_error{ "Error: Player.yPos must be within bounds of matrixSize." };

	if ( playerLength >= 0 )
		length = playerLength;
	else
		throw runtime_error{ "Error: Player.length must be greater than or equal to 0." };

	height = sqrt( pow( length, 2 ) - pow( length / 2.0, 2 ) );

	if ( playerMaxSpeed >= 0 )
		maxSpeed = playerMaxSpeed;
	else
		throw runtime_error{ "Error: Player.maxSpeed must be greater than or equal to 0." };

	speed = 0;

	score = 0;
}

/*
 * Getter methods.
 */
double Player::getXPos() {
	return xPos;
}
double Player::getYPos() {
	return yPos;
}
double Player::getLength() {
	return length;
}
double Player::getHeight() {
	return height;
}
double Player::getMaxSpeed() {
	return maxSpeed;
}
double Player::getSpeed() {
	return speed;
}
unsigned int Player::getScore() {
	return score;
}

/*
 * Setter methods.
 */
void Player::setXPos( double playerXPos, pair<double, double>* matrixSize ) {
	if ( ( 0 <= playerXPos ) && ( playerXPos <= matrixSize->first ) )
		xPos = playerXPos;
	else
		throw runtime_error{ "Error: Player.xPos must be within bounds of matrixSize." };
}
void Player::setSpeed( double playerSpeed ) {
	if ( abs( playerSpeed ) <= maxSpeed )
		speed = playerSpeed;
	else
		throw runtime_error{ "Error: Absolute value of Player.speed must be less than or equal to Player.maxSpeed." };
}
void Player::setScore( unsigned int playerScore ) {
	score = playerScore;
}

/*
 * Returns true if player is colliding with enemy.
 */
bool Player::isCollidingWith( Enemy* enemy ) {
	if (  sqrt( pow( xPos - enemy->getXPos(), 2 ) + pow( yPos - enemy->getYPos(), 2 ) )  <  ( ( height + enemy->getHeight() ) / 2.0 )  )
		return true;
	else
		return false;
}

