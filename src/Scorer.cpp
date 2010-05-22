// Keeps track of the number of lines cleared and the total score

#include "Scorer.h"
#include "APGridTimer.h"
#include "NumberArtist.h"
#include <iostream>
#include <fstream>
using std::ifstream;

// These global variables are used to pass information from the menu game state to the running state.
int g_passLevel;
int g_passMusic;

// Constructor
CScorer::CScorer() :
m_level( 0 ),
m_delay( DEFAULT_DELAY ),
m_numberOfLinesCleared( 0 ),
m_totalScore( 0 ),
m_timer( 0 ),
m_linesUntilLevel( NUM_OF_LINES_TO_LEVEL )	{
	g_passLevel = 0;
	g_passMusic = 1;

}


// Destructor
CScorer::~CScorer()		{
}


// Adds lines cleared
void CScorer::AddLinesCleared( int p_numberOfLines )		{

	// Can clear a max of 4 lines at once
	if ( p_numberOfLines < 0 || p_numberOfLines > 4 )	{
		return;
	}

	m_numberOfLinesCleared += p_numberOfLines;

	// The scoring works as such: 100 * #linesclearedatonce^2 * (level + 1)
	int points = BASE_POINTS * p_numberOfLines * p_numberOfLines * (m_level + 1);

	m_totalScore += points;

	// Check to see if the level should go up
	if ( m_level < MAX_LEVEL )	{
		if ( m_numberOfLinesCleared >= m_linesUntilLevel )	{
			IncreaseLevel();
		}
	}
}


// Resets the number of lines and total score
void CScorer::ResetLines()		{
	m_numberOfLinesCleared = 0;
	m_totalScore = 0;
}


// Increases the level and speeds up the blocks
void CScorer::IncreaseLevel()		{

	// Can't go past the max level
	if ( m_level >= MAX_LEVEL )	{
		return;
	}

	// Increase the level and adjust the timer interval
	m_level++;
	m_delay = DEFAULT_DELAY - ( m_level * DELAY_MULTIPLE );
	if ( m_timer != 0 )	{
		m_timer->SetInterval( m_delay );
	}

	// Increase the number of lines till the next level
	m_linesUntilLevel += NUM_OF_LINES_TO_LEVEL;
}


// Sets the level to a specific value
void CScorer::SetLevel( int p_level )		{
	
	if ( p_level > 10 || p_level < 0 )	{
		return;
	}

	m_level = p_level;
	m_delay = DEFAULT_DELAY - ( m_level * DELAY_MULTIPLE );
	if ( m_timer != 0 )		{
		m_timer->SetInterval( m_delay );
	}

}


// Sets the grid timer
void CScorer::SetTimer( CGridTimer* p_timer )	{
	m_timer = p_timer;
	p_timer->SetInterval( m_delay );
}



// Stops and starts the timer
void CScorer::StopTimer()	{
	if ( m_timer != 0 )	{
		m_timer->Stop();
	}
}

void CScorer::StartTimer()	{
	if ( m_timer != 0 )	{
		m_timer->Start();
	}
}


