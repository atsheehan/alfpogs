// This class is used to display numbers, such as the scores, the level, the number of lines, etc.

#include "NumberArtist.h"
#include "Scorer.h"


// Constructor
CNumberArtist::CNumberArtist()		{

	// The transparent color key
	CColor colorKey( 255, 0, 255 );

	int x_pos = 0;
	int y_pos = 0;
	
	// Load the animations
	for ( int i = 0; i < 10; i++ )	{
		m_highlightedNumbers[ i ] = APAnimationLoader( "Numbers 20x25.bmp", NUMBER_WIDTH, NUMBER_HEIGHT, 1, 1, x_pos, y_pos, 32 );
		m_highlightedNumbers[ i ]->SetColorKey( colorKey );
		x_pos += NUMBER_WIDTH;
	}

	// The unhighlighted numbers are on the second row
	y_pos = NUMBER_HEIGHT;
	x_pos = 0;

	for ( int i = 0; i < 10; i++ )	{
		m_unhighlightedNumbers[ i ] = APAnimationLoader( "Numbers 20x25.bmp", NUMBER_WIDTH, NUMBER_HEIGHT, 1, 1, x_pos, y_pos, 32 );
		m_highlightedNumbers[ i ]->SetColorKey( colorKey );
		x_pos += NUMBER_WIDTH;
	}


	// Load the large numbers for the menu
	x_pos = 0;
	y_pos = 0;
	
	// Load the animations
	for ( int i = 0; i < 10; i++ )	{
		m_highlightedLargeNumbers[ i ] = APAnimationLoader( "Numbers 32x60.bmp", LARGE_NUMBER_WIDTH, LARGE_NUMBER_HEIGHT, 1, 1, x_pos, y_pos, 32 );
		m_highlightedLargeNumbers[ i ]->SetColorKey( colorKey );
		x_pos += LARGE_NUMBER_WIDTH;
	}

	// The unhighlighted numbers are on the second row
	y_pos = LARGE_NUMBER_HEIGHT;
	x_pos = 0;

	for ( int i = 0; i < 10; i++ )	{
		m_unhighlightedLargeNumbers[ i ] = APAnimationLoader( "Numbers 32x60.bmp", LARGE_NUMBER_WIDTH, LARGE_NUMBER_HEIGHT, 1, 1, x_pos, y_pos, 32 );
		m_highlightedLargeNumbers[ i ]->SetColorKey( colorKey );
		x_pos += LARGE_NUMBER_WIDTH;
	}


}

// Destructor
CNumberArtist::~CNumberArtist()		{

	// Release the loaded images
	for ( int i = 0; i < 10; i++ )	{
		APAnimationCleanup( m_unhighlightedNumbers[ i ] );
	}

	for ( int i = 0; i < 10; i++ )	{
		APAnimationCleanup( m_highlightedNumbers[ i ] );
	}

	for ( int i = 0; i < 10; i++ )	{
		APAnimationCleanup( m_highlightedLargeNumbers[ i ] );
	}

	for ( int i = 0; i < 10; i++ )	{
		APAnimationCleanup( m_unhighlightedLargeNumbers[ i ] );
	}
}


// Sets the display surface to blit to
void CNumberArtist::SetDisplaySurface( CCanvas* p_display )	{
	if ( p_display != 0 )	{
		m_display = p_display;
	}
}


// Sets the scorer
void CNumberArtist::SetScorer( CScorer* p_scorer )		{
	m_scorer = p_scorer;
}


// Displays a number with the specified number of digits
void CNumberArtist::DisplayNumber( CPoint& p_location, int p_number, int p_digits )		{

	// Determine which digits to display
	int dig[6] = { 0 };

	if ( p_number > MAX_SCORE )	{
		dig[0] = dig[1] = dig[2] = dig[3] = dig[4] = dig[5] = 9;
	}

	// Determine the individual digits of the score
	if ( p_number < 10 )	{
		dig[0] = dig[1] = dig[2] = dig[3] = dig[4] = 0;
		dig[5] = p_number;
	} else	{
		if ( p_number < 100 )	{
			dig[0] = dig[1] = dig[2] = dig[3] = 0;
			dig[4] = p_number / 10;
			dig[5] = p_number % 10;
		} else	{
			if ( p_number < 1000 )	{
				dig[0] = dig[1] = dig[2] = 0;
				dig[3] = p_number / 100;
				dig[4] = ( p_number % 100 ) / 10;
				dig[5] = p_number % 10;
			} else	{
				if ( p_number < 10000 )	{
					dig[0] = dig[1] = 0;
					dig[2] = p_number / 1000;
					dig[3] = (p_number % 1000) / 100;
					dig[4] = (p_number % 100) / 10;
					dig[5] = p_number % 10;
				} else	{
					if ( p_number < 100000 )	{
						dig[0] = 0;
						dig[1] = p_number / 10000;
						dig[2] = (p_number % 10000) / 1000;
						dig[3] = (p_number % 1000) / 100;
						dig[4] = (p_number % 100) / 10;
						dig[5] = p_number % 10;
					} else	{
						dig[0] = p_number / 100000;
						dig[1] = (p_number % 100000) / 10000;
						dig[2] = (p_number % 10000) / 1000;
						dig[3] = (p_number % 1000) / 100;
						dig[4] = (p_number % 100) / 10;
						dig[5] = p_number % 10;
					}
				}
			}
		}
	}

	for ( int digit = 0; digit < p_digits; digit++ )	{
		m_highlightedLargeNumbers[ dig[ digit ] ]->Animate( m_display, &p_location );
		p_location.X() += LARGE_NUMBER_WIDTH;
	}
}


// Displays the score during the game
void CNumberArtist::DisplayScore()		{

	int score = m_scorer->GetScore();

	// Determine which digits to display
	int dig1, dig2, dig3, dig4, dig5, dig6 = 0;

	if ( score > MAX_SCORE )	{
		dig1 = dig2 = dig3 = dig4 = dig5 = dig6 = 9;
	}

	// Determine the individual digits of the score
	if ( score < 10 )	{
		dig1 = dig2 = dig3 = dig4 = dig5 = 0;
		dig6 = score;
	} else	{
		if ( score < 100 )	{
			dig1 = dig2 = dig3 = dig4 = 0;
			dig5 = score / 10;
			dig6 = score % 10;
		} else	{
			if ( score < 1000 )	{
				dig1 = dig2 = dig3 = 0;
				dig4 = score / 100;
				dig5 = ( score % 100 ) / 10;
				dig6 = score % 10;
			} else	{
				if ( score < 10000 )	{
					dig1 = dig2 = 0;
					dig3 = score / 1000;
					dig4 = (score % 1000) / 100;
					dig5 = (score % 100) / 10;
					dig6 = score % 10;
				} else	{
					if ( score < 100000 )	{
						dig1 = 0;
						dig2 = score / 10000;
						dig3 = (score % 10000) / 1000;
						dig4 = (score % 1000) / 100;
						dig5 = (score % 100) / 10;
						dig6 = score % 10;
					} else	{
						dig1 = score / 100000;
						dig2 = (score % 100000) / 10000;
						dig3 = (score % 10000) / 1000;
						dig4 = (score % 1000) / 100;
						dig5 = (score % 100) / 10;
						dig6 = score % 10;
					}
				}
			}
		}
	}

	CPoint startingLoc( SCORE_X, SCORE_Y );

	// The numbers in the array correspond to their index
	m_highlightedNumbers[ dig1 ]->Animate( m_display, &startingLoc );
	startingLoc.X() += NUMBER_WIDTH;
	
	m_highlightedNumbers[ dig2 ]->Animate( m_display, &startingLoc );
	startingLoc.X() += NUMBER_WIDTH;
	
	m_highlightedNumbers[ dig3 ]->Animate( m_display, &startingLoc );
	startingLoc.X() += NUMBER_WIDTH;
	
	m_highlightedNumbers[ dig4 ]->Animate( m_display, &startingLoc );
	startingLoc.X() += NUMBER_WIDTH;
	
	m_highlightedNumbers[ dig5 ]->Animate( m_display, &startingLoc );
	startingLoc.X() += NUMBER_WIDTH;
	
	m_highlightedNumbers[ dig6 ]->Animate( m_display, &startingLoc );


}

// Displays the level
void CNumberArtist::DisplayLevel()		{

	int level = m_scorer->GetLevel();

	// Determine which digits to display
	int dig1, dig2 = 0;

	if ( level > 99 )	{
		dig1 = dig2 = 9;
	}

	// Determine the individual digits of the score
	if ( level < 10 )	{
		dig1 = 0;
		dig2 = level;
	} else	{
		dig1 = level / 10;
		dig2 = level % 10;
	}

	CPoint startingLoc( LEVEL_X, LEVEL_Y );

	// The numbers in the array correspond to their index
	m_highlightedNumbers[ dig1 ]->Animate( m_display, &startingLoc );
	startingLoc.X() += NUMBER_WIDTH;
	
	m_highlightedNumbers[ dig2 ]->Animate( m_display, &startingLoc );
	startingLoc.X() += NUMBER_WIDTH;

}

// Displays the number of lines cleared
void CNumberArtist::DisplayLinesCleared()		{

	int lines = m_scorer->GetLines();

	// Determine which digits to display
	int dig1, dig2 = 0;

	if ( lines > 99 )	{
		dig1 = dig2 = 9;
	}

	// Determine the individual digits of the score
	if ( lines < 10 )	{
		dig1 = 0;
		dig2 = lines;
	} else	{
		dig1 = lines / 10;
		dig2 = lines % 10;
	}

	CPoint startingLoc( LINES_X, LINES_Y );

	// The numbers in the array correspond to their index
	m_highlightedNumbers[ dig1 ]->Animate( m_display, &startingLoc );
	startingLoc.X() += NUMBER_WIDTH;
	
	m_highlightedNumbers[ dig2 ]->Animate( m_display, &startingLoc );
	startingLoc.X() += NUMBER_WIDTH;

}



// Displays the level selector in the option menu
void CNumberArtist::DisplayLevelMenu()		{

	CPoint startingLoc( MENU_LEVEL_X, MENU_LEVEL_Y );

	// Determine the active number
	int level = m_levelMenuItem->GetCurrentLevel();

	// Display all of the numbers
	for ( int number = MIN_LEVEL; number <= MAX_LEVEL; number++ )	{
		// Is it the highlighted number?
		if ( number == level )	{
			m_highlightedLargeNumbers[ number ]->Animate( m_display, &startingLoc );
		} else	{
			m_unhighlightedLargeNumbers[ number ]->Animate( m_display, &startingLoc );
		}
		startingLoc.X() += LARGE_NUMBER_WIDTH;
	}
}

// Displays the music selector in the option menu
void CNumberArtist::DisplayMusicSelector()		{

	CPoint startingLoc( MENU_MUSIC_X, MENU_MUSIC_Y );

	// Determine the active number
	int music = m_musicMenuItem->GetCurrentMusic();

	// Display all of the numbers
	for ( int number = MIN_MUSIC; number <= MAX_MUSIC; number++ )	{
		// Is it the highlighted number?
		if ( number == music )	{
			m_highlightedLargeNumbers[ number ]->Animate( m_display, &startingLoc );
		} else	{
			m_unhighlightedLargeNumbers[ number ]->Animate( m_display, &startingLoc );
		}
		startingLoc.X() += LARGE_NUMBER_WIDTH;
	}
}

// Displays the high score table in the menu
void CNumberArtist::DisplayHiScore()	{

	int scoreToDisplay;
	CPoint location( MENU_HISCORE_X, MENU_HISCORE_Y );

	// Get each number from the scorer and display them
	for ( int i = 0; i < MAX_HI_SCORES; i++ )	{
		scoreToDisplay = m_hiScores->GetScore( i );
		DisplayNumber( location, scoreToDisplay, SCORE_DIGITS );
		location.Y() += LARGE_NUMBER_HEIGHT;
		location.X() = MENU_HISCORE_X;
	}
}