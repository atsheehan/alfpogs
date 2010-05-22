// These menu items are specific to the ALF POGS game

#ifndef APMENUITEMS_H
#define APMENUITEMS_H


#include "MenuItem.h"
#include "Menu.h"
#include "GameStates.h"
#include "Scorer.h"
#include "Audio.h"


// forward declaration
class CMusic;

// These subclasses are for the main menu
class CMainMenu_Start : public CMenuItem	{

public:

	CMainMenu_Start( CMenu* p_parentMenu, CMenu* p_newMenu, CMenu** p_activeMenu, bool* p_changeMenu );

	void Select();

private:

	// This item changes the menu from the title screen to the options menu where the player selects
	// the difficulty and music for the game
	CMenu** m_activeMenu;
	CMenu* m_newMenu;
	bool* m_changeMenu;

};


class CMainMenu_Help : public CMenuItem	{

public:

	CMainMenu_Help( CMenu* p_parentMenu, CMenu* p_newMenu, CMenu** p_activeMenu, bool* p_changeMenu );

	void Select();

private:

	CMenu** m_activeMenu;
	CMenu* m_newMenu;
	bool* m_changeMenu;
};


class CMainMenu_HiScores : public CMenuItem	{

public:

	CMainMenu_HiScores( CMenu* p_parentMenu, CMenu* p_newMenu, CMenu** p_activeMenu, bool* p_changeMenu );

	void Select();

private:

	CMenu** m_activeMenu;
	CMenu* m_newMenu;
	bool* m_changeMenu;

};


class CMainMenu_Quit : public CMenuItem	{

public:

	CMainMenu_Quit( CMenu* p_parentMenu );

	void Select();

private:

	// Used to send the quit event
	SDL_Event m_event;

};


class COptionMenu_Level : public CMenuItem	{

public:

	COptionMenu_Level( CMenu* p_parentMenu );

	void CycleLeft();
	void CycleRight();
	
	int GetCurrentLevel()	{ return m_currentLevel;	}

private:

	// The current level selected
	int m_currentLevel;

};


class COptionMenu_Music : public CMenuItem	{

public:

	COptionMenu_Music( CMenu* p_parentMenu, CAudio* p_audioSystem );

	void CycleLeft();
	void CycleRight();

	int GetCurrentMusic()	{ return m_currentMusic;	}

private:

	// The current music selected
	int m_currentMusic;
	CAudio* m_audioSystem;


};


class COptionMenu_Start : public CMenuItem	{

public:

	COptionMenu_Start( CMenu* p_parentMenu, COptionMenu_Music* p_music, COptionMenu_Level* p_level );

	void Select();

private:

	COptionMenu_Music* m_music;
	COptionMenu_Level* m_level;

};


class COptionMenu_Back : public CMenuItem	{

public:

	// Changes the active menu to the main screen
	COptionMenu_Back( CMenu* p_parentMenu, CMenu** p_activeMenu, bool* p_changeMenu );

	void Select();

private:

	CMenu** m_activeMenu;
	bool* m_changeMenu;

};


class CHelpMenu_Back : public CMenuItem	{

public:

	CHelpMenu_Back( CMenu* p_parentMenu, CMenu** p_activeMenu, bool* p_changeMenu );

	void Select();

private:

	CMenu** m_activeMenu;
	bool* m_changeMenu;

};


class CScoreMenu_Back : public CMenuItem	{

public:

	CScoreMenu_Back( CMenu* p_parentMenu, CMenu** p_activeMenu, bool* p_changeMenu );

	void Select();

private:

	CMenu** m_activeMenu;
	bool* m_changeMenu;

};


class CPauseMenu_Resume : public CMenuItem	{

public:

	CPauseMenu_Resume( CMenu* p_parentMenu );

	void Select();

};


class CPauseMenu_Help : public CMenuItem	{

public:

	CPauseMenu_Help( CMenu* p_parentMenu, CMenu* p_newMenu, CMenu** p_activeMenu, bool* p_changeMenu );

	void Select();

private:

	CMenu** m_activeMenu;
	CMenu* m_newMenu;
	bool* m_changeMenu;

};


class CPauseMenu_Score : public CMenuItem	{

public:

	CPauseMenu_Score( CMenu* p_parentMenu, CMenu* p_newMenu, CMenu** p_activeMenu, bool* p_changeMenu );

	void Select();

private:

	CMenu** m_activeMenu;
	CMenu* m_newMenu;
	bool* m_changeMenu;

};


class CPauseMenu_Quit : public CMenuItem	{

public:

	CPauseMenu_Quit( CMenu* p_parentMenu );

	void Select();

private:

	// Used to send the quit event
	SDL_Event m_event;

};




#endif	// APMENUITEMS_H