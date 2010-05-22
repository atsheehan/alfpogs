// Implementation of the event handler for Alf Pogs
#include "APEventHandler.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
using std::cerr;


// Constructor doesn't do anything, SDL is initialized in the base class
CAPEventHandler::CAPEventHandler()	:	m_screenWidth( INIT_SCREEN_WIDTH ),
	m_screenHeight( INIT_SCREEN_HEIGHT ),
	m_screenDepth( INIT_DEPTH ),
	m_display( 0 ),
	m_currentState( 0 )
{
	srand( time( 0 ));

		// Calculate the timer delay
		m_timerDelay = 1000 / FPS;	// 1000 ms
		m_newTime = SDL_GetTicks();
}




// Destructor doesn't do anything, calls destructor for base class
CAPEventHandler::~CAPEventHandler()		{
}




// Called once at the beginning of the game loop. Initializes
// SDL and loads any images and sounds
bool CAPEventHandler::OnInit( int argc, char*argv[] )	{

	// Create the display window
	SDL_Surface* display = SDL_SetVideoMode( m_screenWidth, m_screenHeight, 
		m_screenDepth, SDL_ANYFORMAT );

	if ( display == 0	)	{
		cerr << "Could not create the display surface.\n";
		return false;
	}

	// Create the CCanvas object that will hold the display screen surface
	m_display = new CCanvas( display );

	m_display->SetColorKey( CColor( 0, 0, 0 ) );

	// Set the game state to the menu screen
	m_currentState = &m_menuState;

	m_runningState.Init( m_display, &m_currentState, &m_menuState, &m_hiScores );
	m_runningState.SetGameStatePointer( m_currentState );
	m_menuState.Init( m_display, &m_runningState, &m_currentState, &m_audio, &m_hiScores );
	m_menuState.SetGameStatePointer( m_currentState );

	return true;
}




// Called once when the program is terminating. Shuts down SDL
// and frees any memory used.
void CAPEventHandler::OnExit()	{

}


// Called once during each iteration of the main game loop
void CAPEventHandler::OnIdle()		{

	m_currentState->Run();

	// Used to set the frame rate
	while ( SDL_GetTicks() < m_newTime )	{
	}

	m_newTime = SDL_GetTicks() + m_timerDelay;
}


// Called when a key is pressed
void CAPEventHandler::OnKeyDown( SDLKey sym, SDLMod mod, Uint16 unicode )	{

	m_currentState->KeyDown( sym );
}



// The instance of the eventhandler
CAPEventHandler mainProgram;