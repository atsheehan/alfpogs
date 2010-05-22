// Contains animations and locations for an object.

#include "Sprite.h"

// Constructor
CSprite::CSprite( int p_xLoc, int p_yLoc, int p_xSpeed, int p_ySpeed, int p_xSpeedDelay, int p_ySpeedDelay )	:
m_totalAnimations( 0 ),
m_currentAnimation( 0 ),
m_location( p_xLoc, p_yLoc ),
m_xSpeed( p_xSpeed ),
m_ySpeed( p_ySpeed ),
m_xSpeedDelay( p_xSpeedDelay ),
m_ySpeedDelay( p_ySpeedDelay ),
m_xSpeedCounter( 0 ),
m_ySpeedCounter( 0 )	{

}



// Destructor
CSprite::~CSprite()		{
}



//Draws the sprite onto the destination surface.
void CSprite::Draw( CCanvas* p_destination )	{

	m_animations[ m_currentAnimation ]->Animate( p_destination, &m_location );
}



// Updates the sprites location
void CSprite::Update()		{

	// Update the frames of animation
	m_animations[ m_currentAnimation ]->Update();

	// Check to see if the object should move based on the delays
	if ( m_xSpeedCounter >= m_xSpeedDelay )		{
		m_location.X() += m_xSpeed;
		m_xSpeedCounter = 0;
	} else	{
		m_xSpeedCounter++;
	}

	if ( m_ySpeedCounter >= m_ySpeedDelay )		{
		m_location.Y() += m_ySpeed;
		m_ySpeedCounter = 0;
	} else	{
		m_ySpeedCounter++;
	}

}



// Adds an animation to the sprite and returns the index
int CSprite::AddAnimation( CAnimation* p_newAnimation )		{

	// Test to see if it points to something
	if ( p_newAnimation == 0 )	{
		return -1;
	}

	m_animations.push_back( p_newAnimation );
	m_totalAnimations++;

	// The index for the last animation will be one less than the total (starts at 0)
	return ( m_totalAnimations - 1 );
}




// Selects an animation based on an index
void CSprite::SelectAnimation( int p_index )	{ 

	// Test to see if out of bounds
	if ( ( p_index < 0 ) || ( p_index >= m_totalAnimations ) )	{
		return;
	}

	m_currentAnimation = p_index;
}



// Sets the location of the sprite
void CSprite::SetLocation( CPoint& p_newLocation )		{
	m_location = p_newLocation;
}



// Returns the current location of the sprite
CPoint CSprite::GetLocation()		{
	return m_location;
}



// Changes the speed  or delay of the sprite
void CSprite::SetXSpeed( int p_newXSpeed )		{
	m_xSpeed = p_newXSpeed;
}


void CSprite::SetYSpeed( int p_newYSpeed )		{
	m_ySpeed = p_newYSpeed;
}


void CSprite::SetXDelay( int p_newXDelay )		{
	m_xSpeedDelay = p_newXDelay;
}


void CSprite::SetYDelay( int p_newYDelay )		{
	m_ySpeedDelay = p_newYDelay;
}


// Adjusts the current speed and returns the new value
int CSprite::AdjustXSpeed( int p_step )		{
	m_xSpeed += p_step;
	return m_xSpeed;
}


int CSprite::AdjustYSpeed( int p_step )		{
	m_ySpeed += p_step;
	return m_ySpeed;
}



// Returns the number of animations available
int CSprite::GetNumberOfAnimations()	{
	return m_totalAnimations;
}
