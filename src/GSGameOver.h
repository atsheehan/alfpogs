// The game has ended.

#ifndef GSGAMEOVER_H
#define GSGAMEOVER_H

#include "GameStates.h"

class CGSGameOver : public CGameState	{
public:

	// Constructor
	CGSGameOver();

	// Destructor
	virtual ~CGSGameOver();

	void Run();

	// Handles input during this game state
	void KeyDown( SDLKey p_sym );

private:

};

#endif	// GSGAMEOVER_H