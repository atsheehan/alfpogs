// Creates and handles any menus

#include "Menu.h"

// Constructor
CMenu::CMenu( CMenu* p_parentMenu )	:
m_parentMenu( p_parentMenu )	{

	// Set the iterator to the beginning of the list
	m_itemsIter = m_items.begin();

}



// Destructor
CMenu::~CMenu()	{

	// delete all of the menu items
	for ( m_itemsIter = m_items.begin(); m_itemsIter != m_items.end();
	m_itemsIter++ )	{

		// Check to see if it ahs already been deleted
		if ( *m_itemsIter != 0 )	{
			delete *m_itemsIter;
			*m_itemsIter = 0;
		}
	}
}



// Move around the menu
void CMenu::MoveToNextItem()		{

	// Deactive the current item
	(*m_itemsIter)->IsInactive();

    	
    // Check to see if the item is selectable
	do	{

		// Check to see if the iterator should loop back to the
		// beginning
		m_itemsIter++;
		if ( m_itemsIter >= m_items.end() )	{
			m_itemsIter = m_items.begin();
		}

	} while ( (*m_itemsIter)->IsSelectable() == false );

	// Active the new item (sets the active animation)
	(*m_itemsIter)->IsActive();
}


// Move around the menu
void CMenu::MoveToPreviousItem()		{

	// Deactive the current item
	(*m_itemsIter)->IsInactive();

	do {
		if ( m_itemsIter <= m_items.begin() )	{
			m_itemsIter = m_items.end();
			m_itemsIter--;
		} else	{
			m_itemsIter--;
		}
	} while ( (*m_itemsIter)->IsSelectable() == false );

	// Active the new item (sets the active animation)
	(*m_itemsIter)->IsActive();

}



// Cycle through the different options for some menus
void CMenu::CycleLeft()		{

	// Call the current menu items cycle function
	(*m_itemsIter)->CycleLeft();
}




void CMenu::CycleRight()		{

	(*m_itemsIter)->CycleRight();
}




// Select the current menu item
void CMenu::SelectItem()		{
	(*m_itemsIter)->Select();
}




// Adds a menu item and returns the index
int CMenu::AddMenuItem( CMenuItem* p_newItem )		{

	if ( p_newItem == 0 )	{
		return -1;
	}

	m_items.push_back( p_newItem );

	// Set the iterator at the first item
	m_itemsIter = m_items.begin();
	(*m_itemsIter)->IsActive();

	return ( m_items.size() - 1 );
}



// Returns a pointer to the parent menu
CMenu* CMenu::GetParent()		{
	return m_parentMenu;
}

// Returns a vector containing all of the menu item sprites
vector< CMenuItem* >& CMenu::GetItemList()		{
	return m_items;
}