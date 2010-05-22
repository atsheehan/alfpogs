// The Artist object handles what is currently being drawn on the screen

#ifndef ARTIST_H
#define ARTIST_H

#include "Canvas.h"
#include "Sprite.h"
#include <vector>
using std::vector;

class CArtist	{

public:

	// Constructor
	CArtist();

	// Destructor
	virtual ~CArtist();

	// Draws everything on the screen
	void Render();

	// Clears and flips the screen
	void Flip();

	// Sets the surface that all of the objects will be drawn onto
	void SetDisplaySurface( CCanvas* p_display );

	// Adds a new sprite object to the list of things to be drawn
	void AddSprite( CSprite* p_newSprite );

	// Adds a vector of sprites to the list
	void AddList( vector< CSprite* >& p_list );

	// Clears out all of the images to be drawn
	void Clear();

private:

	// Contains pointers to all of the sprites being drawn
	vector< CSprite* > m_sprites;
	vector< CSprite* >::const_iterator m_iterSprites;

	// Display screen
	CCanvas* m_display;
    
};

#endif	// ARTIST_H