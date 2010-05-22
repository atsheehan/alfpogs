// Implementation of the menu game state class

#include "GSMenu.h"
#include "GSRun.h"
#include <iostream>
using std::cerr;

// Constructor
CGSMenu::CGSMenu()	:
m_mainMenu(),
m_helpMenu( &m_mainMenu ),
m_optionMenu( &m_mainMenu ),
m_hiScoreMenu( &m_mainMenu ),
m_inGameMenu(),
m_inGameHelp( &m_inGameMenu ),
m_inGameScores( &m_inGameMenu ),
m_changeMenu( false ),
m_displayLevel( false ),
m_displayMusic( false ),
m_displayHiScore( false )	{
}

// Destructor
CGSMenu::~CGSMenu()	{

	APAnimationCleanup( m_background );
	APAnimationCleanup( m_menuStartActive );
	APAnimationCleanup( m_menuStartInactive );
	APAnimationCleanup( m_menuHelpActive );
	APAnimationCleanup( m_menuHelpInactive );
	APAnimationCleanup( m_menuHiScoresActive );
	APAnimationCleanup( m_menuHiScoresInactive );
	APAnimationCleanup( m_menuQuitActive );
	APAnimationCleanup( m_menuQuitInactive );

	APAnimationCleanup( m_menuBackActive );
	APAnimationCleanup( m_menuBackInactive );
	APAnimationCleanup( m_menuMusicActive );
	APAnimationCleanup( m_menuMusicInactive );
	APAnimationCleanup( m_menuLevelActive );
	APAnimationCleanup( m_menuLevelInactive );

	APAnimationCleanup( m_menuHelpDisplay );
}

void CGSMenu::Run()		{

	m_artist.Render();

	// Removes the old sprites and puts in the new ones if the menu was changed
	if ( m_changeMenu == true )		{
		ChangeMenuDisplay();
	}

	if ( m_displayLevel == true )	{
		m_numArtist.DisplayLevelMenu();
	}

	if ( m_displayMusic == true )	{
		m_numArtist.DisplayMusicSelector();
	}

	if ( m_displayHiScore == true )	{
		m_numArtist.DisplayHiScore();
	}

	m_artist.Flip();
}

// Handles input during this game state
void CGSMenu::KeyDown( SDLKey p_sym )		{

	if ( p_sym == SDLK_DOWN )	{
		m_activeMenu->MoveToNextItem();
	}

	if ( p_sym == SDLK_UP )		{
		m_activeMenu->MoveToPreviousItem();
	}

	if ( p_sym == SDLK_RIGHT )	{
		m_activeMenu->CycleRight();
	}

	if ( p_sym == SDLK_LEFT )	{
		m_activeMenu->CycleLeft();
	}

	if ( p_sym == SDLK_RETURN )	{
		m_activeMenu->SelectItem();
	}

}


// Called once during the programs initiation phase
void CGSMenu::Init( CCanvas* p_display, CGSRun* p_runState, CGameState** p_currentState, CAudio* p_audioSystem, CHiScores* p_hiScores )	{

	m_artist.SetDisplaySurface( p_display );
	m_numArtist.SetDisplaySurface( p_display );
	m_numArtist.SetHiScores( p_hiScores );
	
	// Load all of the images for the menu items
	m_menuStartActive = APAnimationLoader( "Menu Item Template 80x320.bmp", 320, 80, 1, 1, 0, 0, 32 );
	m_menuStartInactive = APAnimationLoader( "Menu Item Template 80x320.bmp", 320, 80, 1, 1, 0, 80, 32 );
	m_menuHelpActive = APAnimationLoader( "Menu Item Template 80x320.bmp", 320, 80, 1, 1, 0, 160, 32 );
	m_menuHelpInactive = APAnimationLoader( "Menu Item Template 80x320.bmp", 320, 80, 1, 1, 0, 240, 32 );
	m_menuHiScoresActive = APAnimationLoader( "Menu Item Template 80x320.bmp", 320, 80, 1, 1, 0, 320, 32 );
	m_menuHiScoresInactive = APAnimationLoader( "Menu Item Template 80x320.bmp", 320, 80, 1, 1, 0, 400, 32 );
	m_menuQuitActive = APAnimationLoader( "Menu Item Template 80x320.bmp", 320, 80, 1, 1, 0, 480, 32 );
	m_menuQuitInactive = APAnimationLoader( "Menu Item Template 80x320.bmp", 320, 80, 1, 1, 0, 560, 32 );
	m_background = APAnimationLoader( "Menu Background 640x480.bmp", 640, 480, 1, 1, 0, 0, 32 );

	// Add the background
	m_backgroundSprite.AddAnimation( m_background );

	// New Game menu item
	CMainMenu_Start* newItem = new CMainMenu_Start( &m_mainMenu, &m_optionMenu, &m_activeMenu, &m_changeMenu );
	newItem->AddAnimation( m_menuStartInactive );
	newItem->AddAnimation( m_menuStartActive );
	newItem->SelectAnimation( MI_INACTIVE );
	newItem->SetLocation( CPoint( 160, 160 ) );
	m_mainMenu.AddMenuItem( newItem );

	// Help menu item
	CMainMenu_Help* newItem2 = new CMainMenu_Help( &m_mainMenu, &m_helpMenu, &m_activeMenu, &m_changeMenu );
	newItem2->AddAnimation( m_menuHelpInactive );
	newItem2->AddAnimation( m_menuHelpActive );
	newItem2->SelectAnimation( MI_INACTIVE );
	newItem2->SetLocation( CPoint( 160, 240 ) );
	m_mainMenu.AddMenuItem( newItem2 );

	// Hi Scores menu item
	CMainMenu_HiScores* newItem3 = new CMainMenu_HiScores( &m_mainMenu, &m_hiScoreMenu, &m_activeMenu, &m_changeMenu );
	newItem3->AddAnimation( m_menuHiScoresInactive );
	newItem3->AddAnimation( m_menuHiScoresActive );
	newItem3->SelectAnimation( MI_INACTIVE );
	newItem3->SetLocation( CPoint( 160, 320 ) );
	m_mainMenu.AddMenuItem( newItem3 );

	// Quit menu item
	CMainMenu_Quit* newItem4 = new CMainMenu_Quit( &m_mainMenu );
	newItem4->AddAnimation( m_menuQuitInactive );
	newItem4->AddAnimation( m_menuQuitActive );
	newItem4->SelectAnimation( MI_INACTIVE );
	newItem4->SetLocation( CPoint( 160, 400 ) );
	m_mainMenu.AddMenuItem( newItem4 );

	// Load the animations for the options menu
	m_menuMusicActive = APAnimationLoader( "Menu Item Template 80x320.bmp", 320, 80, 1, 1, 320, 320, 32 );
	m_menuMusicInactive = APAnimationLoader( "Menu Item Template 80x320.bmp", 320, 80, 1, 1, 320, 400, 32 );
	m_menuLevelActive = APAnimationLoader( "Menu Item Template 80x320.bmp", 320, 80, 1, 1, 320, 160, 32 );
	m_menuLevelInactive = APAnimationLoader( "Menu Item Template 80x320.bmp", 320, 80, 1, 1, 320, 240, 32 );
	m_menuBackActive = APAnimationLoader( "Menu Item Template 80x320.bmp", 320, 80, 1, 1, 320, 0, 32 );
	m_menuBackInactive = APAnimationLoader( "Menu Item Template 80x320.bmp", 320, 80, 1, 1, 320, 80, 32 );
	m_menuResumeActive = APAnimationLoader( "Menu Item Template 80x320.bmp", 320, 80, 1, 1, 320, 480, 32 );
	m_menuResumeInactive = APAnimationLoader( "Menu Item Template 80x320.bmp", 320, 80, 1, 1, 320, 560, 32 );

	COptionMenu_Level* newItem5 = new COptionMenu_Level( &m_optionMenu );
	newItem5->AddAnimation( m_menuLevelInactive );
	newItem5->AddAnimation( m_menuLevelActive );
	newItem5->SelectAnimation( MI_INACTIVE );
	newItem5->SetLocation( CPoint( 0, 160 ) );
	m_optionMenu.AddMenuItem( newItem5 );

	COptionMenu_Music* newItem6 = new COptionMenu_Music( &m_optionMenu, p_audioSystem );
	newItem6->AddAnimation( m_menuMusicInactive );
	newItem6->AddAnimation( m_menuMusicActive );
	newItem6->SelectAnimation( MI_INACTIVE );
	newItem6->SetLocation( CPoint( 0, 240 ) );
	m_optionMenu.AddMenuItem( newItem6 );

	COptionMenu_Start* newItem7 = new COptionMenu_Start( &m_optionMenu, newItem6, newItem5 );
	newItem7->SetGameState( p_currentState, p_runState );
	newItem7->AddAnimation( m_menuStartInactive );
	newItem7->AddAnimation( m_menuStartActive );
	newItem7->SelectAnimation( MI_INACTIVE );
	newItem7->SetLocation( CPoint( 160, 320 ) );
	m_optionMenu.AddMenuItem( newItem7 );

	COptionMenu_Back* newItem8 = new COptionMenu_Back( &m_optionMenu, &m_activeMenu, &m_changeMenu );
	newItem8->AddAnimation( m_menuBackInactive );
	newItem8->AddAnimation( m_menuBackActive );
	newItem8->SelectAnimation( MI_INACTIVE );
	newItem8->SetLocation( CPoint( 160, 400 ) );
	m_optionMenu.AddMenuItem( newItem8 );

	// Add the option menu items to the number artist
	m_numArtist.SetLevelMenuItem( newItem5 );
	m_numArtist.SetMusicMenuItem( newItem6 );

	m_menuHelpDisplay = APAnimationLoader( "Help 640x240.bmp", 640, 240, 1, 1, 0, 0, 32 );

	CHelpMenu_Back* newItem10 = new CHelpMenu_Back( &m_helpMenu, &m_activeMenu, &m_changeMenu );
	newItem10->AddAnimation( m_menuBackInactive );
	newItem10->AddAnimation( m_menuBackActive );
	newItem10->SelectAnimation( MI_INACTIVE );
	newItem10->SetLocation( CPoint( 160, 400 ) );
	m_helpMenu.AddMenuItem( newItem10 );
	
	CMenuItem* newItem9 = new CMenuItem( &m_helpMenu, false );
	newItem9->AddAnimation( m_menuHelpDisplay );
	newItem9->SelectAnimation( MI_INACTIVE );
	newItem9->SetLocation( CPoint( 0, 160 ));
	m_helpMenu.AddMenuItem( newItem9 );

	CScoreMenu_Back* newItem11 = new CScoreMenu_Back( &m_hiScoreMenu, &m_activeMenu, &m_changeMenu );
	newItem11->AddAnimation( m_menuBackInactive );
	newItem11->AddAnimation( m_menuBackActive );
	newItem11->SelectAnimation( MI_INACTIVE );
	newItem11->SetLocation( CPoint( 160, 400 ) );
	m_hiScoreMenu.AddMenuItem( newItem11 );

	CPauseMenu_Resume* newItem12 = new CPauseMenu_Resume( &m_inGameMenu );
	newItem12->SetGameState( p_currentState, p_runState );
	newItem12->AddAnimation( m_menuResumeInactive );
	newItem12->AddAnimation( m_menuResumeActive );
	newItem12->SelectAnimation( MI_INACTIVE );
	newItem12->SetLocation( CPoint( 160, 160 ));
	m_inGameMenu.AddMenuItem( newItem12 );

	CPauseMenu_Help* newItem13 = new CPauseMenu_Help( &m_inGameMenu, &m_inGameHelp, &m_activeMenu, &m_changeMenu );
	newItem13->AddAnimation( m_menuHelpInactive );
	newItem13->AddAnimation( m_menuHelpActive );
	newItem13->SelectAnimation( MI_INACTIVE );
	newItem13->SetLocation( CPoint( 160, 240 ) );
	m_inGameMenu.AddMenuItem( newItem13 );

	CPauseMenu_Score* newItem14 = new CPauseMenu_Score( &m_inGameMenu, &m_inGameScores, &m_activeMenu, &m_changeMenu );
	newItem14->AddAnimation( m_menuHiScoresInactive );
	newItem14->AddAnimation( m_menuHiScoresActive );
	newItem14->SelectAnimation( MI_INACTIVE );
	newItem14->SetLocation( CPoint( 160, 320 ));
	m_inGameMenu.AddMenuItem( newItem14 );

	CPauseMenu_Quit* newItem15 = new CPauseMenu_Quit( &m_inGameMenu );
	newItem15->AddAnimation( m_menuQuitInactive );
	newItem15->AddAnimation( m_menuQuitActive );
	newItem15->SelectAnimation( MI_INACTIVE );
	newItem15->SetLocation( CPoint( 160, 400 ));
	m_inGameMenu.AddMenuItem( newItem15 );

	CHelpMenu_Back* newItem16 = new CHelpMenu_Back( &m_inGameHelp, &m_activeMenu, &m_changeMenu );
	newItem16->AddAnimation( m_menuBackInactive );
	newItem16->AddAnimation( m_menuBackActive );
	newItem16->SelectAnimation( MI_INACTIVE );
	newItem16->SetLocation( CPoint( 160, 400 ) );
	m_inGameHelp.AddMenuItem( newItem16 );
	
	CMenuItem* newItem17 = new CMenuItem( &m_inGameHelp, false );
	newItem17->AddAnimation( m_menuHelpDisplay );
	newItem17->SelectAnimation( MI_INACTIVE );
	newItem17->SetLocation( CPoint( 0, 160 ));
	m_inGameHelp.AddMenuItem( newItem17 );

	CScoreMenu_Back* newItem18 = new CScoreMenu_Back( &m_inGameScores, &m_activeMenu, &m_changeMenu );
	newItem18->AddAnimation( m_menuBackInactive );
	newItem18->AddAnimation( m_menuBackActive );
	newItem18->SelectAnimation( MI_INACTIVE );
	newItem18->SetLocation( CPoint( 160, 400 ) );
	m_inGameScores.AddMenuItem( newItem18 );



	// Set the active menu to the main menu
	m_activeMenu = &m_mainMenu;
	ChangeMenuDisplay();

}

// Changes the menu display to the new active menu
void CGSMenu::ChangeMenuDisplay()		{

	// Clear the current menu's objects in the artist object
	m_artist.Clear();

	// Adds the background
	m_artist.AddSprite( &m_backgroundSprite );

	// Add the new menu items to the list
	vector< CSprite* > tempSpriteVector;
	vector< CMenuItem* > tempItemVector;
	vector< CMenuItem* >::const_iterator tempItemIter;

	tempItemVector = m_activeMenu->GetItemList();
	//Load the menu item pointers into the vector as sprite pointers
	for ( tempItemIter = tempItemVector.begin(); tempItemIter != tempItemVector.end(); tempItemIter++ )		{
		tempSpriteVector.push_back( (*tempItemIter) );
	}

	m_artist.AddList( tempSpriteVector );

	m_changeMenu = false;

	if ( m_activeMenu == &m_optionMenu )	{
		m_displayLevel = true;
		m_displayMusic = true;
	} else	{
		m_displayLevel = false;
		m_displayMusic = false;
	}

	if ( (m_activeMenu == &m_hiScoreMenu) || (m_activeMenu == &m_inGameScores) )	{
		m_displayHiScore = true;
	} else	{
		m_displayHiScore = false;
	}
}


// Sets the pause menu as the active menu
void CGSMenu::SetPauseMenu()	{
	m_activeMenu = &m_inGameMenu;
	m_changeMenu = true;
}



// Sets the main menu as the active menu
void CGSMenu::SetMainMenu()		{
	m_activeMenu = &m_mainMenu;
	m_changeMenu = true;
}