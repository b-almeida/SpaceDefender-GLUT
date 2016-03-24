#include <utility>
#include <stdexcept>

#include "Charge.h"

using namespace std;


/*
 * Constructor method.
 */
Charge::Charge( double chargeXPos, double chargeYPos, double chargeWidth, double chargeHeight, double chargeSpeed, pair<double, double>* matrixSize ) {
	if ( ( 0 <= chargeXPos ) && ( chargeXPos <= matrixSize->first ) )
		xPos = chargeXPos;
	else
		throw runtime_error{ "Error: Charge.xPos must be within bounds of matrixSize." };

	yPos = chargeYPos;

	if ( chargeWidth >= 0 )
		width = chargeWidth;
	else
		throw runtime_error{ "Error: Charge.width must be greater than or equal to 0." };

	if ( chargeHeight >= 0 )
		height = chargeHeight;
	else
		throw runtime_error{ "Error: Charge.height must be greater than or equal to 0." };

	if ( chargeSpeed >= 0)
		speed = chargeSpeed;
	else
		throw runtime_error{ "Error: Charge.speed must be greater than or equal to 0." };
}

/*
 * Getter methods.
 */
double Charge::getXPos() {
	return xPos;
}
double Charge::getYPos() {
	return yPos;
}
double Charge::getWidth() {
	return width;
}
double Charge::getHeight() {
	return height;
}
double Charge::getSpeed() {
	return speed;
}

/*
 * Setter method.
 */
void Charge::setYPos( double chargeYPos ) {
	yPos = chargeYPos;
}

