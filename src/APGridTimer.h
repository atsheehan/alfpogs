// Moves the blocks down on the main grid
#ifndef APGRIDTIMER_H
#define APGRIDTIMER_H

#include "Timer.h"

class CGrid;

class CGridTimer : public CTimer	{

public:
	
	// Constructor
	CGridTimer( CMessageHandler* p_messageHandler, int p_interval, CGrid* p_grid );

	// Destructor
	~CGridTimer();

	// Called every interal
	void OnTimer();

private:

	// A pointer to the grid that handles the blocks
	CGrid* m_grid;

};



#endif	// APGRIDTIMER