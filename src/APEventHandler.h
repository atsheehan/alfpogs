// The event handler for the Alf Pogs game, derived from CEventHandler
#ifndef CAPEVENTHANDLER_H
#define CAPEVENTHANDLER_H


#include "Eventhandler.h"
#include "AllGameStates.h"
#include "ImageSet.h"
#include "APAnimation.h"
#include "Audio.h"


// Constants
const int INIT_SCREEN_WIDTH = 640;
const int INIT_SCREEN_HEIGHT = 480;
const int INIT_DEPTH = 32;
const int FPS = 60;
const int AUDIO_CHUNK_SIZE = 4096;


class CAPEventHandler : public CEventHandler	{
public:

	CAPEventHandler();
	virtual ~CAPEventHandler();

	// Called once at the beginning of the game loop. Initializes
	// SDL and loads any images and sounds
	bool OnInit( int argc, char*argv[] );

	// Called once when the program is terminating. Shuts down SDL
	// and frees any memory used.
	void OnExit();

	// Called once during each iteration of the game loop
	void OnIdle();

	// Called when a key is pressed
	void OnKeyDown( SDLKey sym, SDLMod mod, Uint16 unicode );

private:

	// Resolution of the display
	int m_screenWidth;
	int m_screenHeight;
	int m_screenDepth;

	// Canvas object that contains the surface that is displayed on the screen
	CCanvas* m_display;

	// The different game states
	CGSMenu m_menuState;
	CGSRun m_runningState;
	CGSExit m_exitingState;

	// A pointer to the current game state
	CGameState* m_currentState;

	// Used to maintain the FPS
	int m_timerDelay;
	int m_newTime;

	// Handles all of the game audio
	CAudio m_audio;

	// Handles the hi scores
	CHiScores m_hiScores;

};


#endif	// CAPEVENTHANDLER_H