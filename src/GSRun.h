// The game state while the main game is running.

#ifndef GSRUN_H
#define GSRUN_H

#include "GameStates.h"
#include "Grid.h"
#include "GridArtist.h"
#include "Artist.h"
#include "APGridTimer.h"
#include "NumberArtist.h"
#include "HiScores.h"

class CGSMenu;

class CGSRun : public CGameState	{
public:

	// Constructor
	CGSRun();

	// Destructor
	virtual ~CGSRun();

	void Run();

	void Init( CCanvas* p_display, CGameState** p_activeState, CGSMenu* p_menuState, CHiScores* p_hiScores );

	// Handles input during this game state
	void KeyDown( SDLKey p_sym );

	// Loads the in game menu
	void InGameMenu();

	// Loads the main menu
	void MainMenu();

private:

	// Handles all of the drawing
	CGridArtist m_gridArtist;
	CNumberArtist m_numArtist;
	CArtist m_artist;
	CGrid m_grid;

	// Handles the timing of the blocks falling down
	CGridTimer m_gridTimer;

	// The background
	CAnimation* m_backgroundImage;
	CSprite* m_background;

	// Used to know the game state
	bool m_startOver;
	bool m_paused;
	bool m_resume;
	bool m_running;

	// Holds information about the menu state when switching to the in game menu
	CGameState** m_activeState;
	CGSMenu* m_menuState;

};

#endif	// GSRUN_H