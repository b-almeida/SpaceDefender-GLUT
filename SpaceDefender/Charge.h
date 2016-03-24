#ifndef CHARGE_H_INCLUDED
#define CHARGE_H_INCLUDED

#include <utility>

using namespace std;


/*
 * Charge game object.
 * Can move vertically and destroy enemies.
 */
class Charge {
public:
	Charge( double chargeXPos, double chargeYPos, double chargeWidth, double chargeHeight, double chargeSpeed, pair<double, double>* matrixSize );

	double getXPos();
	double getYPos();
	double getWidth();
	double getHeight();
	double getSpeed();

	void setYPos( double chargeYPos );

private:
	double xPos;	// rectangle centre
	double yPos;	// rectangle centre
	double width;	// of rectangle
	double height;	// of rectangle
	double speed;
};


#endif // CHARGE_H_INCLUDED

