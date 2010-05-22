// Creates and handles any menus

#ifndef MENU_H
#define MENU_H

#include "MenuItem.h"

class CMenu		{

public:

	// Constructor
	CMenu( CMenu* p_parentMenu = 0 );

	// Destructor
	~CMenu();

	// Move around the menu
	void MoveToNextItem();
	void MoveToPreviousItem();

	// Cycle through the different options for some menus
	void CycleLeft();
	void CycleRight();

	// Select the current menu item
	void SelectItem();

	// Adds a menu item and returns the index
	int AddMenuItem( CMenuItem* p_newItem );

	// Returns a pointer to the parent menu
	CMenu* GetParent();

	// Returns the menu item at the given index
	//CMenuItem* GetMenuItem( int p_index );

	// Returns a vector containing all of the menu items
	vector< CMenuItem* >& GetItemList();

private:

	// All of the individual items on the menu
	vector< CMenuItem* > m_items;
	vector< CMenuItem* >::iterator m_itemsIter;

	// The background image
	CSprite* m_background;

	// The parent menu
	CMenu* m_parentMenu;
};

#endif	// MENU_H