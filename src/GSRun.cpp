// Implementation of the running game state class

#include "GSRun.h"
#include "GSMenu.h"

// Constructor
CGSRun::CGSRun()	:
m_gridTimer( NULL, DEFAULT_DELAY, &m_grid ),
m_startOver( true ),
m_paused( false ),
m_resume( false ),
m_running( false )	{

	m_grid.Pause();


}

// Destructor
CGSRun::~CGSRun()	{
	APAnimationCleanup( m_backgroundImage );
}


void CGSRun::Run()		{

	m_artist.Flip();

	m_gridArtist.DrawGrid();
	m_artist.Render();
	m_numArtist.DisplayLevel();
	m_numArtist.DisplayScore();
	m_numArtist.DisplayLinesCleared();

	if ( m_paused == true )	{
		m_paused = false;
		m_running = true;
		m_grid.Resume();
	}

	if ( m_startOver == true )	{
		m_startOver = false;
		m_running = true;
		m_grid.Reset();
	}

	m_grid.Update();



}

void CGSRun::Init( CCanvas* p_display, CGameState** p_activeState, CGSMenu* p_menuState, CHiScores* p_hiScores )		{

	m_activeState = p_activeState;
	m_menuState = p_menuState;
	m_grid.SetHiScores( p_hiScores );

	m_gridArtist.SetDisplay( p_display );
	m_gridArtist.SetGrid( &m_grid );
	m_numArtist.SetDisplaySurface( p_display );
	m_numArtist.SetScorer( m_grid.GetScorer() );
	m_artist.SetDisplaySurface( p_display );

	m_backgroundImage = APAnimationLoader( "Background 640x480.bmp", 640, 480, 1, 1, 0, 0, 32 );
	m_backgroundImage->SetColorKey( CColor( 255, 0, 255 ));
	m_background = new CSprite();
	m_background->AddAnimation( m_backgroundImage );
	m_background->SelectAnimation( 0 );
	
	m_artist.AddSprite( m_background );
	m_grid.SetScoreTimer( &m_gridTimer );
	m_grid.Reset();
}


// Handles input during this game state
void CGSRun::KeyDown( SDLKey p_sym )		{

	if ( p_sym == SDLK_DOWN )	{
		m_grid.MovePieceDown();
	}

	if ( p_sym == SDLK_LEFT )	{
		m_grid.MovePieceLeft();
	}

	if ( p_sym == SDLK_RIGHT )	{
		m_grid.MovePieceRight();
	}

	if ( p_sym == SDLK_SPACE )	{
		m_grid.RotatePiece();
	}

	if ( p_sym == SDLK_UP )	{
		m_grid.DropPiece();
	}

	if ( p_sym == SDLK_KP_ENTER )	{
		m_grid.Reset();
	}

	if ( p_sym == SDLK_ESCAPE )		{

		if ( m_grid.IsGameOver() == true )	{
			MainMenu();
			m_startOver = true;
		} else	{
			InGameMenu();
		}

	}


}

// Loads the in game menu
void CGSRun::InGameMenu()		{

	m_menuState->SetPauseMenu();

	*m_activeState = m_menuState;
	m_paused = true;
	m_grid.Pause();

}


// Loads the main menu
void CGSRun::MainMenu()		{

	m_menuState->SetMainMenu();

	*m_activeState = m_menuState;
	m_paused = true;
	m_grid.Pause();
}