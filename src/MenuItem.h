// Menus are composed of several menu items that can be selected or displayed.
// Derived from the Sprite class.

#ifndef MENUITEM_H
#define MENUITEM_H

#include "Sprite.h"

// These are used to set the animation to the inactive or active state
const int MI_INACTIVE = 0;
const int MI_ACTIVE = 1;

// Forward declaration
class CMenu;
class CGameState;
class CGSRun;

class CMenuItem : public CSprite	{

public:

	// Constructor
	CMenuItem( CMenu* p_parentMenu, bool selectable = true );

	// Destructor
	virtual ~CMenuItem();

	// Cycles through the options for this menu item
	virtual void CycleLeft();
	virtual void CycleRight();

	// Performs an action when selected
	virtual void Select();

	// Changes the animation to the highlighted selection
	void IsActive();

	// Changes the animation back to the inactive state
	void IsInactive();

	// Checks to see if this item is selectable
	bool CheckSelectable()	{ return m_isSelectable;	}

	// Adds the current game state pointer
	void SetGameState( CGameState** p_currentState, CGSRun* p_nextState = 0 );

	// Returns whether the item is selectable or not
	bool IsSelectable()		{ return m_isSelectable;	}

protected:
	
	// The menu that this object belongs to
	CMenu* m_parentMenu;
	CGSRun* m_nextState;

	CGameState** m_currentState;

private:

	// Is this item being highlighted?
	bool m_isHighlighted;

	// Is this item selectable?
	bool m_isSelectable;

};



#endif	// MENUITEM_H