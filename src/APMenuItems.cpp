// These menu items are specific to the ALF POGS game

#include "APMenuItems.h"
#include "AllGameStates.h"


CMainMenu_Start::CMainMenu_Start( CMenu* p_parentMenu, CMenu* p_newMenu, CMenu** p_activeMenu, bool* p_changeMenu )	: 
CMenuItem( p_parentMenu ),
m_activeMenu( p_activeMenu ),
m_newMenu( p_newMenu ),
m_changeMenu( p_changeMenu )	{
}



void CMainMenu_Start::Select()		{
	// Change the menu to the option menu
	*m_activeMenu = m_newMenu;
	*m_changeMenu = true;
}



CMainMenu_Help::CMainMenu_Help( CMenu* p_parentMenu, CMenu* p_newMenu, CMenu** p_activeMenu, bool* p_changeMenu )	: 
CMenuItem( p_parentMenu ),
m_activeMenu( p_activeMenu ),
m_newMenu( p_newMenu ),
m_changeMenu( p_changeMenu )	{
}



void CMainMenu_Help::Select()		{
	// Change the menu to the help menu
	*m_activeMenu = m_newMenu;
	*m_changeMenu = true;
}



CMainMenu_HiScores::CMainMenu_HiScores( CMenu* p_parentMenu, CMenu* p_newMenu, CMenu** p_activeMenu, bool* p_changeMenu )	: 
CMenuItem( p_parentMenu ),
m_activeMenu( p_activeMenu ),
m_newMenu( p_newMenu ),
m_changeMenu( p_changeMenu )	{
}



void CMainMenu_HiScores::Select()	{
	// Change the menu to the hi score menu
	*m_activeMenu = m_newMenu;
	*m_changeMenu = true;
}



CMainMenu_Quit::CMainMenu_Quit( CMenu* p_parentMenu )	: 
CMenuItem( p_parentMenu )	{

	m_event.type = SDL_QUIT;
}



void CMainMenu_Quit::Select()		{
	SDL_PushEvent( &m_event );
}



COptionMenu_Level::COptionMenu_Level( CMenu* p_parentMenu )	: 
CMenuItem( p_parentMenu ),
m_currentLevel( 0 )	{
}



void COptionMenu_Level::CycleLeft()	{
	if ( m_currentLevel <= MIN_LEVEL )	{
		m_currentLevel = MAX_LEVEL;
	} else {
		m_currentLevel--;
	}
}



void COptionMenu_Level::CycleRight()		{
	if ( m_currentLevel >= MAX_LEVEL )	{
		m_currentLevel = MIN_LEVEL;
	} else	{
		m_currentLevel++;
	}
}



COptionMenu_Music::COptionMenu_Music( CMenu* p_parentMenu, CAudio* p_audioSystem )	: 
CMenuItem( p_parentMenu ),
m_currentMusic( 1 ),
m_audioSystem( p_audioSystem )	{
}



// Changes the selected music
void COptionMenu_Music::CycleLeft()		{
	if ( m_currentMusic <= MIN_MUSIC )	{
		m_currentMusic = MAX_MUSIC;
	} else	{
		m_currentMusic--;
	}
	
	m_audioSystem->PlayMusic( m_currentMusic - 1 );
}



void COptionMenu_Music::CycleRight()	{
	if ( m_currentMusic >= MAX_MUSIC )	{
		m_currentMusic = MIN_MUSIC;
	} else	{
		m_currentMusic++;
	}

	m_audioSystem->PlayMusic( m_currentMusic - 1 );

}



COptionMenu_Start::COptionMenu_Start( CMenu* p_parentMenu, COptionMenu_Music* p_music, COptionMenu_Level* p_level )	: 
CMenuItem( p_parentMenu ),
m_level( p_level ),
m_music( p_music )	{
}



void COptionMenu_Start::Select()	{
	// Sets the music and level
	g_passLevel = m_level->GetCurrentLevel();
	g_passMusic = m_music->GetCurrentMusic();

	*m_currentState = m_nextState;
}



COptionMenu_Back::COptionMenu_Back( CMenu* p_parentMenu, CMenu** p_activeMenu, bool* p_changeMenu )	: 
CMenuItem( p_parentMenu ),
m_activeMenu( p_activeMenu ),
m_changeMenu( p_changeMenu ) {
}


// Changes the active menu to the main screen
void COptionMenu_Back::Select()		{
	*m_activeMenu = m_parentMenu->GetParent();
	*m_changeMenu = true;
}



CHelpMenu_Back::CHelpMenu_Back( CMenu* p_parentMenu, CMenu** p_activeMenu, bool* p_changeMenu )	: 
CMenuItem( p_parentMenu ),
m_activeMenu( p_activeMenu ),
m_changeMenu( p_changeMenu )	{
}



void CHelpMenu_Back::Select()		{
	*m_activeMenu = m_parentMenu->GetParent();
	*m_changeMenu = true;
}



CScoreMenu_Back::CScoreMenu_Back( CMenu* p_parentMenu, CMenu** p_activeMenu, bool* p_changeMenu )	: 
CMenuItem( p_parentMenu ),
m_activeMenu( p_activeMenu ),
m_changeMenu( p_changeMenu )	{
}



void CScoreMenu_Back::Select()		{
	*m_activeMenu = m_parentMenu->GetParent();
	*m_changeMenu = true;
}



CPauseMenu_Resume::CPauseMenu_Resume( CMenu* p_parentMenu )	: 
CMenuItem( p_parentMenu )	{
}



void CPauseMenu_Resume::Select()	{
	*m_currentState = m_nextState;
}



CPauseMenu_Help::CPauseMenu_Help( CMenu* p_parentMenu, CMenu* p_newMenu, CMenu** p_activeMenu, bool* p_changeMenu )	: 
CMenuItem( p_parentMenu ),
m_activeMenu( p_activeMenu ),
m_newMenu( p_newMenu ),
m_changeMenu( p_changeMenu )	{
}



void CPauseMenu_Help::Select()		{
	*m_activeMenu = m_newMenu;
	*m_changeMenu = true;
}



CPauseMenu_Score::CPauseMenu_Score( CMenu* p_parentMenu, CMenu* p_newMenu, CMenu** p_activeMenu, bool* p_changeMenu )	: 
CMenuItem( p_parentMenu ),
m_activeMenu( p_activeMenu ),
m_newMenu( p_newMenu ),
m_changeMenu( p_changeMenu )	{
}



void CPauseMenu_Score::Select()		{
	*m_activeMenu = m_newMenu;
	*m_changeMenu = true;
}



CPauseMenu_Quit::CPauseMenu_Quit( CMenu* p_parentMenu )	: 
CMenuItem( p_parentMenu )	{
	m_event.type = SDL_QUIT;
}



void CPauseMenu_Quit::Select()		{
	SDL_PushEvent( &m_event );
}


