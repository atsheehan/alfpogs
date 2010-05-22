// The game state when the game is about to begin.

#ifndef GSSTART_H
#define GSSTART_H

#include "GameStates.h"

class CGSStart : public CGameState	{
public:

	// Constructor
	CGSStart();

	// Destructor
	virtual ~CGSStart();

	void Run();

	// Handles input during this game state
	void KeyDown( SDLKey p_sym );

private:

};

#endif	// GSSTART_H