// This class is used to display numbers, such as the scores, the level, the number of lines, etc.
#ifndef NUMBERARTIST_H
#define NUMBERARTIST_H


#include "APAnimation.h"
#include "APMenuItems.h"
#include "HiScores.h"

const int NUMBER_WIDTH = 20;
const int NUMBER_HEIGHT = 25;

const int LARGE_NUMBER_WIDTH = 32;
const int LARGE_NUMBER_HEIGHT = 60;

// Specifies the location of the scores, level, and line cleared items FOR RUNNING GAME STATE
const int SCORE_X = 50;
const int SCORE_Y = 75;

const int LEVEL_X = 100;
const int LEVEL_Y = 165;

const int LINES_X = 100;
const int LINES_Y = 255;

const int SCORE_DIGITS = 6;

// Specifies the location of the numbers on the menus

const int MENU_LEVEL_X = 320;
const int MENU_LEVEL_Y = 160;

const int MENU_MUSIC_X = 320;
const int MENU_MUSIC_Y = 240;

const int MENU_HISCORE_X = 224;
const int MENU_HISCORE_Y = 160;

// forward declaration
class CScorer;

class CNumberArtist		{

public:

	// Constructor
	CNumberArtist();

	// Destructor
	~CNumberArtist();

	// Sets the display surface
	void SetDisplaySurface( CCanvas* p_display );

	// Sets the scorer
	void SetScorer( CScorer* p_scorer );

	// Sets the hi score item
	void SetHiScores( CHiScores* p_hiScores )	{ m_hiScores = p_hiScores;	}

	// Displays a number with the specified number of digits
	void DisplayNumber( CPoint& p_location, int p_number, int p_digits );

	// Displays the score during the game
	void DisplayScore();

	// Displays the level
	void DisplayLevel();

	// Displays the number of lines cleared
	void DisplayLinesCleared();

	// Displays the level selector in the option menu
	void DisplayLevelMenu();

	// Displays the music selector in the option menu
	void DisplayMusicSelector();

	// Displays the high score table in the menu
	void DisplayHiScore();

	void SetLevelMenuItem( COptionMenu_Level* p_levelMenuItem )		{ m_levelMenuItem = p_levelMenuItem;	}
	void SetMusicMenuItem( COptionMenu_Music* p_musicMenuItem )		{ m_musicMenuItem = p_musicMenuItem;	}

private:

	// The surface to blit to
	CCanvas* m_display;

	// Contains the information about scores, level, and lines cleared
	CScorer* m_scorer;
	CHiScores* m_hiScores;

	// Holds the animations for the highlighted numbers
	CAnimation* m_highlightedNumbers[ 10 ];

	// Holds the animations for the unhighlighted numbers
	CAnimation* m_unhighlightedNumbers[ 10 ];

	CAnimation* m_highlightedLargeNumbers[ 10 ];
	CAnimation* m_unhighlightedLargeNumbers[ 10 ];

	// Holds information on which level and music are selected
	COptionMenu_Level* m_levelMenuItem;
	COptionMenu_Music* m_musicMenuItem;


};


#endif	// NUMBERARTIST_H