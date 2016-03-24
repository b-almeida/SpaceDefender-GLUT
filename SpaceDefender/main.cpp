/*
Bruno Almeida
ICS3U0-A Final Project

Space Defender
Space-themed 2-D shooter game
*/


#include <iostream>
#include <sstream>
#include <utility>
#include <vector>
#include <stdexcept>
#include <GL/glut.h>
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Charge.h"

using namespace std;


// function declarations
void init2D( float r, float g, float b );
void glutKeyboardNormalDown( unsigned char key, int x, int y );
void glutKeyboardSpecialDown( int key, int x, int y );
void glutKeyboardSpecialUp( int key, int x, int y );
void displayPlayer();
void displayEnemies();
void displayCharges();
void displayScore();
void glutDisplay();
bool isGameOver();
void glutUpdate( int value );
void glutDisplayStart();
void glutDisplayEnd();
void exitProgram( int value );
void startScreen( int value );
void gameScreen( int value );
void endScreen( int value );


// game object
Game* game = new Game();


/*
 * Initializes 2-D matrix for window scaling.
 */
void init2D( float r, float g, float b ) {
	glClearColor( r, g, b, 0.0 );
	glMatrixMode( GL_PROJECTION );
	gluOrtho2D( 0.0, game->getMatrixSize()->first, 0.0, game->getMatrixSize()->second );
}

/*
 * GLUT normal keyboard down event function.
 */
void glutKeyboardNormalDown( unsigned char key, int x, int y ) {
	switch ( key ) {
	// space bar - create charge
	case ' ':
		try {
			game->getCharges()->push_back( new Charge( game->getPlayer()->getXPos(),
														game->getPlayer()->getYPos() + (game->getPlayer()->getLength() / 2.0),
														game->getChargeWidth(),
														game->getChargeHeight(),
														game->getChargeSpeed(),
														game->getMatrixSize() ) );
		}
		catch (runtime_error& e) {
			cout << e.what() << endl;
		}

		// sound effect
		cout << "\a";
		break;
	}
}

/*
 * GLUT special keyboard down event function.
 */
void glutKeyboardSpecialDown( int key, int x, int y ) {
	switch ( key ) {
	// left arrow - set player speed left
	case GLUT_KEY_LEFT:
		try {
			game->getPlayer()->setSpeed( -game->getPlayer()->getMaxSpeed() );
		}
		catch (runtime_error& e) {
			cout << e.what() << endl;
		}

		break;

	// right arrow - set player speed right
	case GLUT_KEY_RIGHT:
		try {
			game->getPlayer()->setSpeed( game->getPlayer()->getMaxSpeed() );
		}
		catch (runtime_error& e) {
			cout << e.what() << endl;
		}

		break;
	}
}

/*
 * GLUT special keyboard up event function.
 */
void glutKeyboardSpecialUp( int key, int x, int y ) {
	switch ( key ) {
	// left arrow - stop player
	case GLUT_KEY_LEFT:
		try {
			game->getPlayer()->setSpeed( 0 );
		}
		catch (runtime_error& e) {
			cout << e.what() << endl;
		}

		break;

	// right arrow - stop player
	case GLUT_KEY_RIGHT:
		try {
			game->getPlayer()->setSpeed( 0 );
		}
		catch (runtime_error& e) {
			cout << e.what() << endl;
		}

		break;
	}
}

/*
 * Displays player.
 */
void displayPlayer() {
	// get triangle properties
	Player* player = game->getPlayer();
	double xPos = player->getXPos();
	double yPos = player->getYPos();
	double length = player->getLength();
	double height = player->getHeight();

	// display triangle
	glColor3f( 0.0, 0.0, 1.0 );	// blue
	glBegin( GL_TRIANGLES );
		glVertex2f( xPos, yPos + (height / 2.0) );					// top
		glVertex2f( xPos - (length / 2.0), yPos - (height / 2.0) );	// bottom left
		glVertex2f( xPos + (length / 2.0), yPos - (height / 2.0) );	// bottom right
	glEnd();
}

/*
 * Displays enemies.
 */
void displayEnemies() {
	vector<Enemy*>* enemies = game->getEnemies();

	for ( int iEnemy = 0; iEnemy < enemies->size(); iEnemy++ ) {
		Enemy* enemy = enemies->at( iEnemy );

		// get triangle properties
		double xPos = enemy->getXPos();
		double yPos = enemy->getYPos();
		double length = enemy->getLength();
		double height = enemy->getHeight();

		// display triangle
		glColor3f( 1.0, 0.0, 0.0 );	// red
		glBegin( GL_TRIANGLES );
			glVertex2f( xPos, yPos - (height / 2.0) );					// bottom
			glVertex2f( xPos - (length / 2.0), yPos + (height / 2.0) );	// top left
			glVertex2f( xPos + (length / 2.0), yPos + (height / 2.0) );	// top right
		glEnd();
	}
}

/*
 * Displays charges.
 */
void displayCharges() {
	vector<Charge*>* charges = game->getCharges();

	for ( int iCharge = 0; iCharge < charges->size(); iCharge++ ) {
		Charge* charge = charges->at( iCharge );

		// get rectangle properties
		double xPos = charge->getXPos();
		double yPos = charge->getYPos();
		double width = charge->getWidth();
		double height = charge->getHeight();

		// display rectangle
		glColor3f( 1.0, 1.0, 0.0 );	// yellow
		glBegin( GL_QUADS );
			glVertex2f( xPos - (width / 2.0), yPos - (height / 2.0) );	// bottom left
			glVertex2f( xPos - (width / 2.0), yPos + (height / 2.0) );	// top left
			glVertex2f( xPos + (width / 2.0), yPos + (height / 2.0) );	// top right
			glVertex2f( xPos + (width / 2.0), yPos - (height / 2.0) );	// bottom right
		glEnd();
	}
}

/*
 * Displays score.
 */
void displayScore() {
	// get string
	stringstream scoreStringStream;
	scoreStringStream << "Score: " << game->getPlayer()->getScore();
	string scoreString = scoreStringStream.str();

	// display string
	glColor3f( 1.0, 1.0, 1.0 );	// white
	glRasterPos2f( 10.0, game->getMatrixSize()->second - 15.0 );
	for ( int iChar = 0; iChar < scoreString.length(); iChar++ )
		glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, scoreString[iChar] );
}

/*
 * GLUT display function.
 */
void glutDisplay() {
	glClear( GL_COLOR_BUFFER_BIT );

	// display player, enemies, charges, score
	displayPlayer();
	displayEnemies();
	displayCharges();
	displayScore();

	glFlush();
}

/*
 * Returns true if an enemy reaches the bottom of the screen or if the player collides with an enemy.
 */
bool isGameOver() {
	// check if an enemy reaches the bottom of the screen
	for ( int iEnemy = 0; iEnemy < game->getEnemies()->size(); iEnemy++ ) {
		Enemy* enemy = game->getEnemies()->at( iEnemy );

		if ( enemy->getYPos() + (enemy->getHeight() / 2.0) < 0 )
			return true;
	}

	// check if player collides with an enemy
	for ( int iEnemy = 0; iEnemy < game->getEnemies()->size(); iEnemy++ ) {
		Enemy* enemy = game->getEnemies()->at( iEnemy );

		if ( game->getPlayer()->isCollidingWith( enemy ) )
			return true;
	}

	return false;
}

/*
 * GLUT update function (once per frame).
 */
void glutUpdate( int value ) {
	// update elapsed time
	try {
		game->setTimeCurrent( glutGet( GLUT_ELAPSED_TIME ) );
	}
	catch (runtime_error& e) {
		cout << e.what() << endl;
	}

	// update player, enemies, charges, collisions
	game->updatePlayer();
	game->updateEnemies();
	game->updateCharges();
	game->updateCollisions();

	// check if game is over
	if ( isGameOver() ){
		// set end screen
		glutTimerFunc( 1, endScreen, 0 );
	}
	else {
		// update time
		try {
			game->setTimeBase( game->getTimeCurrent() );
		}
		catch (runtime_error& e) {
			cout << e.what() << endl;
		}

		// display window, set update timer
		glutPostRedisplay();
		glutTimerFunc( 1000 / game->getFps(), glutUpdate, 0 );
	}
}

/*
 * GLUT display function for start screen.
 */
void glutDisplayStart() {
	glClear( GL_COLOR_BUFFER_BIT );

	// get strings
	vector<string> displayStringList;
	displayStringList.push_back( "SPACE DEFENDER" );
	displayStringList.push_back( "Space bar to fire" );
	displayStringList.push_back( "Arrow keys to move" );

	// display strings
	glColor3f( 1.0, 1.0, 1.0 );	// white

	glRasterPos2f( (game->getMatrixSize()->first / 2.0) - 52.0, (game->getMatrixSize()->second - 100.0) );
	for ( int iChar = 0; iChar < displayStringList[0].length(); iChar++ )
		glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, displayStringList[0][iChar] );

	glRasterPos2f( (game->getMatrixSize()->first / 2.0) - 40.0, (game->getMatrixSize()->second - 200.0) );
	for ( int iChar = 0; iChar < displayStringList[1].length(); iChar++ )
		glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, displayStringList[1][iChar] );

	glRasterPos2f( (game->getMatrixSize()->first / 2.0) - 50.0, (game->getMatrixSize()->second - 220.0) );
	for ( int iChar = 0; iChar < displayStringList[2].length(); iChar++ )
		glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, displayStringList[2][iChar] );

	glFlush();
}

/*
 * GLUT display function for end screen.
 */
void glutDisplayEnd() {
	glClear( GL_COLOR_BUFFER_BIT );

	// get string
	string displayString = "GAME OVER";

	// display string
	glColor3f( 1.0, 1.0, 1.0 );	// white
	glRasterPos2f( (game->getMatrixSize()->first / 2.0) - 35.0, (game->getMatrixSize()->second - 200.0) );
	for ( int iChar = 0; iChar < displayString.length(); iChar++ )
		glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, displayString[iChar] );

	glFlush();
}

/*
 * Exits program.
 */
void exitProgram( int value ) {
	exit( 0 );
}

/*
 * Changes program state to start screen.
 */
void startScreen( int value ) {
	// set GLUT display function
	glutDisplayFunc( glutDisplayStart );
	glutPostRedisplay();

	// set game start timer
	glutTimerFunc( game->getStartDelay(), gameScreen, 0 );
}

/*
 * Changes program state to game.
 */
void gameScreen( int value ) {
	// sound alert
	cout << "\a\a\a";

	// set GLUT functions
	glutKeyboardFunc( glutKeyboardNormalDown );
	glutSpecialFunc( glutKeyboardSpecialDown );
	glutSpecialUpFunc( glutKeyboardSpecialUp );
	glutDisplayFunc( glutDisplay );
	glutTimerFunc( 1, glutUpdate, 0 );
	glutPostRedisplay();

	// update time base
	game->setTimeBase( glutGet( GLUT_ELAPSED_TIME ) );
}

/*
 * Changes program state to end screen.
 */
void endScreen( int value ) {
	// sound alert
	cout << "\a\a\a";

	// set GLUT functions
	glutKeyboardFunc( NULL );
	glutSpecialFunc( NULL );
	glutSpecialUpFunc( NULL );
	glutDisplayFunc( glutDisplayEnd );
	glutPostRedisplay();

	// set program exit timer
	glutTimerFunc( game->getEndDelay(), exitProgram, 0 );
}

/*
 * Program initialization.
 */
int main( int argc, char *argv[] ) {
	// initialize GLUT
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
	glutInitWindowSize( game->getWindowSize()->first, game->getWindowSize()->second );
	glutInitWindowPosition( 0, 0 );
	glutCreateWindow( "Space Defender!" );
	init2D( 0.0, 0.0, 0.0 );

	// set start screen
	glutTimerFunc( 1, startScreen, 0 );

	// enter main loop
	glutMainLoop();
}

