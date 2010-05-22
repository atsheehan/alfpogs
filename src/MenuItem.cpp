// Menus are composed of several menu items that can be selected or displayed.
// Derived from the Sprite class.

#include "MenuItem.h"
#include "AllGameStates.h"


// Constructor
CMenuItem::CMenuItem( CMenu* p_parentMenu, bool p_selectable )	:
m_isSelectable( p_selectable )	{
	m_parentMenu = p_parentMenu;
}

// Adds the current game state pointer
void CMenuItem::SetGameState( CGameState** p_currentState, CGSRun* p_nextState )		{
	m_currentState = p_currentState;
	m_nextState = p_nextState;
}


// Destructor
CMenuItem::~CMenuItem()		{
}

// Cycles through the options for this menu item
void CMenuItem::CycleLeft()		{
}



void CMenuItem::CycleRight()		{
}




// Performs an action when selected
void CMenuItem::Select()	{
}



// Changes the animation to the highlighted selection
void CMenuItem::IsActive()		{
	
	int animationsAvailable = GetNumberOfAnimations();

	// Check to see if there are two animations available
	if ( animationsAvailable < 2 )	{
		return;
	}

	// Change the animation
	SelectAnimation( MI_ACTIVE );

}

// Changes the animiation to the inactive state
void CMenuItem::IsInactive()		{

	// Change the animation back to the inactive state
	SelectAnimation( MI_INACTIVE );

}
