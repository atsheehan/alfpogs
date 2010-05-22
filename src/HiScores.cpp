#include "HiScores.h"
#include <iostream>
#include <fstream>
using std::fstream;
using std::ofstream;

// Constructor
CHiScores::CHiScores()	{
	LoadScores();
}

// Destructor
CHiScores::~CHiScores()		{
}

// Loads the hi scores from a save file
bool CHiScores::LoadScores()		{

	fstream scoreFile( "scores.txt" );

	// Read the first five integers and check to see if they are within bounds
	for ( int i = 0; i < MAX_HI_SCORES; i++ )	{
		scoreFile >> m_hiScore[ i ];

		// If they are out of bounds, reset all of the scores to 0 and return false
		if ( ( m_hiScore[ i ] > MAX_SCORE ) || ( m_hiScore[ i ] < 0 ) )	{
			for ( int j = 0; j < MAX_HI_SCORES; j++ )	{
				m_hiScore[ j ] = 0;
			}
			return false;
		}
	}

	// Sort the scores in ascending order
	SortScores();

	return true;
}



// Returns the hi score at the given index
int CHiScores::GetScore( int p_index )		{

	// check to see if the index is out of bounds
	if ( ( p_index < 0 ) || ( p_index >= MAX_HI_SCORES ) )	{
		return -1;
	}

	return m_hiScore[ p_index ];
}



// Compares the given score to the current records to determine if it is worth keeping
void CHiScores::AddScore( int p_newScore )		{

	// Check to see if the new score beats the lowest score
	if ( p_newScore < m_hiScore[ MAX_HI_SCORES - 1 ] )	{
		return;
	} else	{
		// Replace the lowest score with the new score and sort
		m_hiScore[ MAX_HI_SCORES - 1 ] = p_newScore;
		SortScores();
	}

	// Write over the score file
	ofstream out( "scores.txt" );

	for ( int i = 0; i < MAX_HI_SCORES; i++ )	{
		out << m_hiScore[ i ] << "\n";
	}
}



// Sorts the hi scores using a bubble sort algorithm
void CHiScores::SortScores()		{

	int temp;

	for ( int i = MAX_HI_SCORES - 1; i > 0; i-- )	{
		for ( int j = 0; j < i ; j++ )	{

			if ( m_hiScore[ j ] < m_hiScore[ j + 1 ] )	{
				temp = m_hiScore[ j ];
				m_hiScore[ j ] = m_hiScore[ j + 1 ];
				m_hiScore[ j + 1 ] = temp;
			}
		}
	}
}

