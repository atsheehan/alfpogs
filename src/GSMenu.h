// The menu game state. 

#ifndef GSMENU_H
#define GSMENU_H

#include "GameStates.h"
#include "Artist.h"
#include "NumberArtist.h"
#include "APAnimation.h"
#include "Menu.h"
#include "APMenuItems.h"
#include "HiScores.h"
#include "Audio.h"

// forward declaration
class CGSRun;

class CGSMenu : public CGameState	{
public:

	// Constructor
	CGSMenu();

	// Destructor
	virtual ~CGSMenu();

	// Called once during the programs initiation phase
	void Init( CCanvas* p_display, CGSRun* p_runState, CGameState** p_currentState, CAudio* p_audioSystem, CHiScores* p_hiScores );

	void Run();

	// Handles input during this game state
	void KeyDown( SDLKey p_sym );

	// Sets the pause menu as the active menu
	void SetPauseMenu();

	// Sets the main menu as the active menu
	void SetMainMenu();

private:

	// Changes the menu display to the new active menu
	void ChangeMenuDisplay();

	// The menu that is currently active
	CMenu* m_activeMenu;

	// True when the menu has just been changed
	bool m_changeMenu;
	bool m_displayLevel;
	bool m_displayMusic;
	bool m_displayHiScore;

	// The different menus in the game
	CMenu m_mainMenu;
	CMenu m_optionMenu;
	CMenu m_helpMenu;
	CMenu m_hiScoreMenu;
	CMenu m_inGameMenu;
	CMenu m_inGameHelp;
	CMenu m_inGameScores;

	//Draws the images for the menu
	CArtist m_artist;
	CNumberArtist m_numArtist;

	// The sprites used in the menu game state
	CAnimation* m_background;
	CSprite m_backgroundSprite;
	CAnimation* m_menuStartInactive;
	CAnimation* m_menuStartActive;
	CAnimation* m_menuHelpInactive;
	CAnimation* m_menuHelpActive;
	CAnimation* m_menuHiScoresInactive;
	CAnimation* m_menuHiScoresActive;
	CAnimation* m_menuQuitInactive;
	CAnimation* m_menuQuitActive;
	CAnimation* m_menuBackActive;
	CAnimation* m_menuBackInactive;
	CAnimation* m_menuMusicActive;
	CAnimation* m_menuMusicInactive;
	CAnimation* m_menuLevelActive;
	CAnimation* m_menuLevelInactive;
	CAnimation* m_menuHelpDisplay;
	CAnimation* m_menuResumeInactive;
	CAnimation* m_menuResumeActive;
};

#endif	// GSMENU_H