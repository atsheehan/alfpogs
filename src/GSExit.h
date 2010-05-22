// The game is shutting down.

#ifndef GSEXIT_H
#define GSEXIT_H

#include "GameStates.h"

class CGSExit : public CGameState	{
public:

	// Constructor
	CGSExit();

	// Destructor
	virtual ~CGSExit();

	void Run();

	// Handles input during this game state
	void KeyDown( SDLKey p_sym );

private:

};

#endif	// GSEXIT_H