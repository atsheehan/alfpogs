// Moves the blocks down on the main grid

#include "APGridTimer.h"
#include "Grid.h"


CGridTimer::CGridTimer( CMessageHandler* p_messageHandler, int p_interval, CGrid* p_grid )	:
CTimer( p_messageHandler, p_interval ),
m_grid( p_grid )	{

}


CGridTimer::~CGridTimer()	{
}


// Moves the piece down
void CGridTimer::OnTimer()		{

	m_grid->MovePieceDown();

}