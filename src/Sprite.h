// Contains animations and locations for an object.

#ifndef SPRITE_H
#define SPRITE_H

#include "APAnimation.h"

class CSprite 	{

public:

	// Constructor
	CSprite( int p_xLoc = 0, int p_yLoc = 0, int p_xSpeed = 0, 
		int p_ySpeed = 0, int p_xSpeedDelay = 0, int p_ySpeedDelay = 0 );

	// Destructor
	virtual ~CSprite();

	//Draws the sprite onto the destination surface.
	void Draw( CCanvas* p_destination );

	// Updates the sprites location
	void Update();

	// Adds an animation to the sprite and returns the index
	int AddAnimation( CAnimation* p_newAnimation );

	// Selects an animation based on an index
	void SelectAnimation( int p_index );

	// Sets the location of the sprite
	void SetLocation( CPoint& p_newLocation );

	// Returns the current location of the sprite
	CPoint GetLocation();

	// Changes the speed  or delay of the sprite
	void SetXSpeed( int p_newXSpeed );
	void SetYSpeed( int p_newYSpeed );
	void SetXDelay( int p_newXDelay );
	void SetYDelay( int p_newYDelay );

	// Adjusts the current speed and returns the new value
	int AdjustXSpeed( int p_step );
	int AdjustYSpeed( int p_step );

	// Returns the number of animations available
	int GetNumberOfAnimations();

private:

	// Contains all of the sprites animations
	vector< CAnimation* > m_animations;

	// The total number of animations
	int m_totalAnimations;

	// The current animations being used (index)
	int m_currentAnimation;

	// The position of the sprite on the screen
	CPoint m_location;

	// The speed of the sprite
	int m_xSpeed;
	int m_ySpeed;

	// A speed delay and counter
	int m_xSpeedDelay;
	int m_ySpeedDelay;
	int m_xSpeedCounter;
	int m_ySpeedCounter;

};

#endif	// SPRITE_H

