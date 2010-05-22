// The grid contains information for the blocks on the screen
// as well as the falling piece.

#include "Grid.h"
#include "HiScores.h"
#include "sdl.h"

// Constructor
CGrid::CGrid() :	
m_xPos( DEFAULT_PIECE_X ),
m_yPos( DEFAULT_PIECE_Y ),
m_animating( false ),
m_gameOver( false )
{

	// Initialize the grid to 0
	for ( int i = 0; i < GRID_HEIGHT; i++ )		{
		for ( int j = 0; j < GRID_WIDTH; j++ )	{
			m_grid[ (i * GRID_WIDTH) + j ] = 0;
		}
	}

	m_nextPieceConfig = m_nextPiece.GenerateNewPiece();
	m_gridInactive = false;
}



// Destructor	
CGrid::~CGrid()		{
}



// Moves the piece to the right or left
void CGrid::MovePieceRight()	{

	// Check to see if it is ok to move
	if ( m_gridInactive == true )	{
		return;
	}

	// Check to see if the piece is at the edge
	int* tempPiece = m_activePiece.GetConfiguration();

	for ( int i = 0; i < PIECE_HEIGHT; i++ )	{
		for ( int j = 0; j < PIECE_WIDTH; j++ )		{

			// Check to see if there is a block in this location
			if ( tempPiece[ (i * PIECE_WIDTH) + j ] > 0 )	{

				// check to see if it is close to the edge
				if ( (m_xPos + j) >= (GRID_WIDTH - 1) )	{
					return;
				}

				// Check to see if there is a block next to it
				int gridIndex = ((m_yPos + i) * GRID_WIDTH) + m_xPos + j + 1;
				if ( m_grid[ gridIndex ] > 0 )	{
					return;
				}
			}
		}
	}

	// If there is nothing in the way, move the piece
	m_xPos++;
}


void CGrid::MovePieceLeft()		{

	// Check to see if it is ok to move
	if ( m_gridInactive == true )	{
		return;
	}

	// Check to see if the piece is at the edge
	int* tempPiece = m_activePiece.GetConfiguration();

	for ( int i = 0; i < PIECE_HEIGHT; i++ )	{
		for ( int j = 0; j < PIECE_WIDTH; j++ )		{

			// Check to see if there is a block in this location
			if ( tempPiece[ (i * PIECE_WIDTH) + j ] > 0 )	{

				// check to see if it is close to the edge
				if ( (m_xPos + j) <= 0 )	{
					return;
				}

				// Check to see if there is a block next to it
				int gridIndex = ((m_yPos + i) * GRID_WIDTH) + m_xPos + j - 1;
				if ( m_grid[ gridIndex ] > 0 )	{
					return;
				}
			}
		}
	}

	// If there is nothing in the way, move the piece
	m_xPos--;
}


// Drops the piece down one step. Returns 1 if it hits something
int CGrid::MovePieceDown()		{

	// Check to see if it is ok to move
	if ( m_gridInactive == true )	{
		return 1;
	}

	// Check to see if the piece is at the edge or going to hit another piece
	int* tempPiece = m_activePiece.GetConfiguration();

	for ( int i = 0; i < PIECE_HEIGHT; i++ )	{
		for ( int j = 0; j < PIECE_WIDTH; j++ )		{

			// Check to see if there is a block in this location
			if ( tempPiece[ (i * PIECE_WIDTH) + j ] > 0 )	{

				// check to see if it hits the bottom
				if ( (m_yPos + i) >= GRID_HEIGHT - 1 )	{
					
					// Attach the piece to the grid and generate a new piece
					AttachPieceToGrid();
					return 1;
				}

				// Check to see if it hits a block
				int gridIndex = ((m_yPos + i + 1) * GRID_WIDTH) + m_xPos + j;
				if ( m_grid[ gridIndex ] > 0 )	{

					// Attach the piece to the grid 
					AttachPieceToGrid();
					return 1;
				}
			}
		}
	}

	// Move the piece down if there is nothign else in the way
	m_yPos++;
	return 0;
}



// Drops the piece until it hits another block or the bottom
void CGrid::DropPiece()		{

	// Check to see if it is ok to move
	if ( m_gridInactive == true )	{
		return;
	}

	while ( MovePieceDown() != 1 )	{
	}
}



// Rotates the piece clockwise
void CGrid::RotatePiece()	{

	// Check to see if it is ok to move
	if ( m_gridInactive == true )	{
		return;
	}

	// Check to see if the rotated piece interferes with any other blocks
	m_activePiece.Rotate();

	// Check to see if the piece is at the edge or going to hit another piece
	int* tempPiece = m_activePiece.GetConfiguration();

	for ( int i = 0; i < PIECE_HEIGHT; i++ )	{
		for ( int j = 0; j < PIECE_WIDTH; j++ )		{

			// Check to see if there is a block in this location
			if ( tempPiece[ (i * PIECE_WIDTH) + j ] > 0 )	{

				// check to see if it hits the bottom
				if ( (m_yPos + i) >= GRID_HEIGHT )	{
					// Rotate the piece back
					m_activePiece.RotateClockwise();
					return;
				}
				
				// check to see if it is over the edge
				if ( (m_xPos + j) < 0 )	{
					m_activePiece.RotateClockwise();
					return;
				}

				// check to see if it is close to the edge
				if ( (m_xPos + j) > (GRID_WIDTH - 1) )	{
					m_activePiece.RotateClockwise();
					return;
				}

				// Check to see if it hits a block
				int gridIndex = ((m_yPos + i) * GRID_WIDTH) + m_xPos + j;
				if ( m_grid[ gridIndex ] > 0 )	{
					// Rotate the piece back
					m_activePiece.RotateClockwise();
					return;
				}
			}
		}
	}
}


// Returns the grid array
int* CGrid::GetGrid()		{
	return m_grid;
}



// Returns the piece array
int* CGrid::GetActivePiece()	{
	return m_activePiece.GetConfiguration();
}

int* CGrid::GetNextPiece()	{
	return m_nextPiece.GetConfiguration();
}


// Attaches the piece to the grid
void CGrid::AttachPieceToGrid()		{

	int* tempPiece = m_activePiece.GetConfiguration();
	bool gameOver = false;

	for ( int i = 0; i < PIECE_HEIGHT; i++ )	{

		int lineIndex = i * PIECE_WIDTH;

		for ( int j = 0; j < PIECE_WIDTH; j++ )		{

			// Check to see if there is a block in this location
			if ( tempPiece[ lineIndex + j ] > 0 )	{

				// Check to see if it extends over the top of the grid
				if ( (m_yPos + i ) < GRID_OVERFLOW )	{
					gameOver = true;
				}

				// Copy it onto the grid
				m_grid[ ((i + m_yPos) * GRID_WIDTH) + m_xPos + j ] = tempPiece[ lineIndex + j ];
			}
		}
	}

	// check to see if there are any full lines
	CheckForLines();

	m_activePiece.GenerateNewPiece( m_nextPieceConfig );
	m_nextPieceConfig = m_nextPiece.GenerateNewPiece();
	m_xPos = DEFAULT_PIECE_X;
	m_yPos = DEFAULT_PIECE_Y;

	// Check to see if game over
	if ( gameOver == true )		{
		GameOver();
	}
}


// Checks to see if there are any full lines
void CGrid::CheckForLines()		{

	bool clearLines = false;
	int numberOfLines = 0;

	for ( int i = 0; i < GRID_HEIGHT; i++ )		{

		int lineIndex = i * GRID_WIDTH;

		for ( int j = 0; j < GRID_WIDTH; j++ )		{

			if ( m_grid[ lineIndex + j ] == 0 )	{
				break;
			}

			// Check to see if it is the end of the line and add it to the list
			if ( j == GRID_WIDTH - 1 )	{
				m_lines.push_back( i );
				numberOfLines++;
				clearLines = true;
			}
		}
	}

	// Clear the lines and add the score
	if ( clearLines == true )	{
		DisintegrateLines();
		m_scorer.AddLinesCleared( numberOfLines );
	}
}



// Clears the lines and drops all of the blocks above it down
void CGrid::ClearLines()	{

	vector<int>::const_iterator lineIter;

	for ( lineIter = m_lines.begin(); lineIter != m_lines.end(); lineIter++ )	{
		
		for ( int i = (*lineIter); i > 0; i-- )		{

			// These refer to two adjacent lines. The blocks drop from the top line to the bottom one
			int lineIndexBottom = i * GRID_WIDTH;
			int lineIndexTop = (i - 1) * GRID_WIDTH;

			for ( int j = 0; j < GRID_WIDTH; j++ )		{
				m_grid[ lineIndexBottom + j ] = m_grid[ lineIndexTop + j ];
			}
		}

		// Zero out the top line (the line number is 0)
		for ( int j = 0; j < GRID_WIDTH; j++ )	{
			m_grid[ j ] = 0;
		}
	}

	// Clear out the line vector
	m_lines.clear();

}

// Sets the disintegrationg animation and pauses the game until they are finished
void CGrid::DisintegrateLines()		{

	// Pause the game and set the wait variable
	Pause();

	m_animating = true;
	m_endTime = SDL_GetTicks() + DISINTEGRATE_DELAY;

	// Set each block in the line to disintegrate
	vector<int>::const_iterator lineIter;

	for ( lineIter = m_lines.begin(); lineIter != m_lines.end(); lineIter++ )	{

		int lineIndex = (*lineIter) * GRID_WIDTH;

		// Set each block in the line to the disintegrate variable
		for ( int j = 0; j < GRID_WIDTH; j++ )	{
			m_grid[ lineIndex + j ] = BLOCK_DISINTEGRATE;
		}
	}

}



// Sets the timer for the grid
void CGrid::SetScoreTimer( CGridTimer* p_timer )	{
	if ( p_timer != 0 )	{
		m_scorer.SetTimer( p_timer );
	}
}



// Stops the game when the grid overflows
void CGrid::GameOver()	{

	// Inactive the grid
	m_gridInactive = true;
	m_gameOver = true;

	// Stop the timer
	m_scorer.StopTimer();

	// Send the hi score to see if it beats the previous score
	m_hiScores->AddScore( m_scorer.GetScore() );

	// Set all of the blocks on the grid to gray
	for ( int i = 0; i < GRID_HEIGHT; i++ )		{

		int lineIndex = i * GRID_WIDTH;

		for ( int j = 0; j < GRID_WIDTH; j++ )		{

			if ( m_grid[ lineIndex + j ] != BLOCK_UNOCCUPIED )	{
				m_grid[ lineIndex + j ] = BLOCK_COLOR_GRAY;
			}
		}
	}
}



// Resets the grid and starts over
void CGrid::Reset()		{
	
	// Reset the score and level
	m_scorer.ResetLines();
	m_scorer.SetLevel( g_passLevel );

	// Clear the grid
	for ( int row = 0; row < GRID_HEIGHT; row++ )	{

		int lineIndex = row * GRID_WIDTH;

		for ( int column = 0; column < GRID_WIDTH; column++ )	{

			m_grid[ lineIndex + column ] = 0;

		}
	}

	// Create new pieces
	m_activePiece.GenerateNewPiece();
	m_nextPieceConfig = m_nextPiece.GenerateNewPiece();

	m_xPos = DEFAULT_PIECE_X;
	m_yPos = DEFAULT_PIECE_Y;

	// Start the timer again
	m_scorer.StartTimer();

	// Reactive the grid
	m_gridInactive = false;
	m_gameOver = false;
}


// Restarts the timer
void CGrid::Resume()	{
	m_scorer.StartTimer();
}

// Stops the timer
void CGrid::Pause()		{
	m_scorer.StopTimer();
}

void CGrid::Update()		{

	// If the blocks are currently in animation
	if ( m_animating == true )	{

		// If the animation has finished, resume the game and get rid of the blocks
		if ( SDL_GetTicks() >= m_endTime )	{
			Resume();
			m_animating = false;
			ClearLines();
		}
	}

}
