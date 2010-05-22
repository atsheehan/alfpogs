// The Artist object handles what is currently being drawn on the screen

#include "Artist.h"

// Constructor
CArtist::CArtist()	{
}


// Destructor
CArtist::~CArtist()	{
}


// Draws everything on the screen
void CArtist::Render()		{



	for ( m_iterSprites = m_sprites.begin(); m_iterSprites != m_sprites.end();
	m_iterSprites++ )	{
		(*m_iterSprites)->Draw( m_display );
		(*m_iterSprites)->Update();
	}

}



// Clears and flips the screen
void CArtist::Flip()		{

	m_display->Flip();

	// Clears the screen
	m_display->Clear( CColor( 0, 0, 0 ) );
}


// Sets the surface that all of the objects will be drawn onto
void CArtist::SetDisplaySurface( CCanvas* p_display )	{
	m_display = p_display;
}


// Adds a new sprite object to the list of things to be drawn
void CArtist::AddSprite( CSprite* p_newSprite )		{
	m_sprites.push_back( p_newSprite );
}


// Adds a vector of sprites to the list
void CArtist::AddList( vector< CSprite* >& p_list )		{

	// Use an iterator to run through the vector
	vector< CSprite* >::const_iterator listIter;
	for ( listIter = p_list.begin(); listIter != p_list.end(); listIter++ )		{
		AddSprite( (*listIter) );
	}


}



// Clears out all of the images to be drawn
void CArtist::Clear()		{
	m_sprites.clear();
}