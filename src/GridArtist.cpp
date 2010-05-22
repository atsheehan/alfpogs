// Draws the grid with all fo the blocks

#include "GridArtist.h"

// Constructor
CGridArtist::CGridArtist()	:
out("grid.txt")	{

	out << "In constructor";

	m_redBlock = APAnimationLoader( "Red Tile 20x20.bmp", BLOCK_WIDTH, BLOCK_HEIGHT, 1, 1, 0, 0, 32 );
	m_blueBlock = APAnimationLoader( "Blue Tile 20x20.bmp", BLOCK_WIDTH, BLOCK_HEIGHT, 1, 1, 0, 0, 32 );
	m_greenBlock = APAnimationLoader( "Green Tile 20x20.bmp", BLOCK_WIDTH, BLOCK_HEIGHT, 1, 1, 0, 0, 32 );
	m_yellowBlock = APAnimationLoader( "Yellow Tile 20x20.bmp", BLOCK_WIDTH, BLOCK_HEIGHT, 1, 1, 0, 0, 32 );
	m_orangeBlock = APAnimationLoader( "Orange Tile 20x20.bmp", BLOCK_WIDTH, BLOCK_HEIGHT, 1, 1, 0, 0, 32 );
	m_purpleBlock = APAnimationLoader( "Purple Tile 20x20.bmp", BLOCK_WIDTH, BLOCK_HEIGHT, 1, 1, 0, 0, 32 );

	m_disintegrate = APAnimationLoader( "stuff.bmp", BLOCK_WIDTH, BLOCK_HEIGHT, 12, 12, 0, 124, 32, 2 );
	m_disintegrate->SetColorKey( CColor( 255, 255, 255 ));
	m_grayBlock = APAnimationLoader( "stuff.bmp", BLOCK_WIDTH, BLOCK_HEIGHT, 1, 1, 0, 124, 32 );
}


// Destructor
CGridArtist::~CGridArtist()		{

	APAnimationCleanup( m_redBlock );
	APAnimationCleanup( m_blueBlock );
	APAnimationCleanup( m_greenBlock );
	APAnimationCleanup( m_yellowBlock );
	APAnimationCleanup( m_orangeBlock );
	APAnimationCleanup( m_purpleBlock );

	APAnimationCleanup( m_disintegrate );
	APAnimationCleanup( m_grayBlock );

}


// Sets the grid to be drawn from
void CGridArtist::SetGrid( CGrid* p_grid )		{
	m_grid = p_grid;
}


// Sets the drawing area
void CGridArtist::SetDisplay( CCanvas* p_display )		{
	m_display = p_display;
}


// Draws the grid
void CGridArtist::DrawGrid()	{

	int* grid = m_grid->GetGrid();
	bool updateDisintegrate = false;

	// check the grid for blocks
	for ( int i = 0; i < GRID_HEIGHT; i++ )		{
		int lineIndex = i * GRID_WIDTH;

		for ( int j = 0; j < GRID_WIDTH; j++ )		{

			int blockColor = grid[ lineIndex + j ];
			
			if ( blockColor != BLOCK_UNOCCUPIED )	{
				
				// Test to see what color block goes there
				switch ( blockColor )	{

					case BLOCK_COLOR_RED:
						m_redBlock->Animate( m_display, &CPoint( (j * BLOCK_WIDTH) + GRID_STARTING_X, (i * BLOCK_HEIGHT) + GRID_STARTING_Y ));
						break;
					
					case BLOCK_COLOR_BLUE:
						m_blueBlock->Animate( m_display, &CPoint( (j * BLOCK_WIDTH) + GRID_STARTING_X, (i * BLOCK_HEIGHT) + GRID_STARTING_Y ));
						break;
					
					case BLOCK_COLOR_GREEN:
						m_greenBlock->Animate( m_display, &CPoint( (j * BLOCK_WIDTH) + GRID_STARTING_X, (i * BLOCK_HEIGHT) + GRID_STARTING_Y ));
						break;
					
					case BLOCK_COLOR_YELLOW:
						m_yellowBlock->Animate( m_display, &CPoint( (j * BLOCK_WIDTH) + GRID_STARTING_X, (i * BLOCK_HEIGHT) + GRID_STARTING_Y ));
						break;
					
					case BLOCK_COLOR_PURPLE:
						m_purpleBlock->Animate( m_display, &CPoint( (j * BLOCK_WIDTH) + GRID_STARTING_X, (i * BLOCK_HEIGHT) + GRID_STARTING_Y ));
						break;
						
					case BLOCK_COLOR_ORANGE:
						m_orangeBlock->Animate( m_display, &CPoint( (j * BLOCK_WIDTH) + GRID_STARTING_X, (i * BLOCK_HEIGHT) + GRID_STARTING_Y ));
						break;

					case BLOCK_DISINTEGRATE:
						m_disintegrate->Animate( m_display, &CPoint( (j * BLOCK_WIDTH) + GRID_STARTING_X, (i * BLOCK_HEIGHT) + GRID_STARTING_Y ));
						updateDisintegrate = true;
						break;

					case BLOCK_COLOR_GRAY:
						m_grayBlock->Animate( m_display, &CPoint( (j * BLOCK_WIDTH) + GRID_STARTING_X, (i * BLOCK_HEIGHT) + GRID_STARTING_Y ));
						break;

					default:
						break;

				}
			}
		}
	}

	// Draw the active piece
	int* activePiece = m_grid->GetActivePiece();
	int xPos = m_grid->GetPieceXLoc();
	int yPos = m_grid->GetPieceYLoc();

	for ( int i = 0; i < PIECE_HEIGHT; i++ )		{
		int lineIndex = i * PIECE_WIDTH;

		for ( int j = 0; j < PIECE_WIDTH; j++ )		{

			int blockColor = activePiece[ lineIndex + j ];

			if ( blockColor > 0 )	{
				// Test to see what color block goes there
				switch ( blockColor )	{

					case BLOCK_COLOR_RED:
						m_redBlock->Animate( m_display, &CPoint( ((j + xPos) * BLOCK_WIDTH) + GRID_STARTING_X,
							((i + yPos) * BLOCK_HEIGHT ) + GRID_STARTING_Y ));
						break;
					
					case BLOCK_COLOR_BLUE:
						m_blueBlock->Animate( m_display, &CPoint( ((j + xPos) * BLOCK_WIDTH) + GRID_STARTING_X,
							((i + yPos) * BLOCK_HEIGHT ) + GRID_STARTING_Y ));
						break;
					
					case BLOCK_COLOR_GREEN:
						m_greenBlock->Animate( m_display, &CPoint( ((j + xPos) * BLOCK_WIDTH) + GRID_STARTING_X,
							((i + yPos) * BLOCK_HEIGHT ) + GRID_STARTING_Y ));
						break;
					
					case BLOCK_COLOR_YELLOW:
						m_yellowBlock->Animate( m_display, &CPoint( ((j + xPos) * BLOCK_WIDTH) + GRID_STARTING_X,
							((i + yPos) * BLOCK_HEIGHT ) + GRID_STARTING_Y ));
						break;
					
					case BLOCK_COLOR_PURPLE:
						m_purpleBlock->Animate( m_display, &CPoint( ((j + xPos) * BLOCK_WIDTH) + GRID_STARTING_X,
							((i + yPos) * BLOCK_HEIGHT ) + GRID_STARTING_Y ));
						break;
						
					case BLOCK_COLOR_ORANGE:
						m_orangeBlock->Animate( m_display, &CPoint( ((j + xPos) * BLOCK_WIDTH) + GRID_STARTING_X,
							((i + yPos) * BLOCK_HEIGHT ) + GRID_STARTING_Y ));
						break;

					default:
						break;

				}
			}
		}
	}

	// Draw the next piece
	int* nextPiece = m_grid->GetNextPiece();

	for ( int i = 0; i < PIECE_HEIGHT; i++ )		{
		int lineIndex = i * PIECE_WIDTH;

		for ( int j = 0; j < PIECE_WIDTH; j++ )		{

			int blockColor = nextPiece[ lineIndex + j ];

			if ( blockColor > 0 )	{
				// Test to see what color block goes there
				switch ( blockColor )	{

					case BLOCK_COLOR_RED:
						m_redBlock->Animate( m_display, &CPoint( (j * BLOCK_WIDTH) + NEXT_PIECE_X,
							((i * BLOCK_HEIGHT ) + NEXT_PIECE_Y )));
						break;
					
					case BLOCK_COLOR_BLUE:
						m_blueBlock->Animate( m_display, &CPoint( (j * BLOCK_WIDTH) + NEXT_PIECE_X,
							((i * BLOCK_HEIGHT ) + NEXT_PIECE_Y )));
						break;
					
					case BLOCK_COLOR_GREEN:
						m_greenBlock->Animate( m_display, &CPoint( (j * BLOCK_WIDTH) + NEXT_PIECE_X,
							((i * BLOCK_HEIGHT ) + NEXT_PIECE_Y )));
						break;
					
					case BLOCK_COLOR_YELLOW:
						m_yellowBlock->Animate( m_display, &CPoint( (j * BLOCK_WIDTH) + NEXT_PIECE_X,
							((i * BLOCK_HEIGHT ) + NEXT_PIECE_Y )));
						break;
					
					case BLOCK_COLOR_PURPLE:
						m_purpleBlock->Animate( m_display, &CPoint( (j * BLOCK_WIDTH) + NEXT_PIECE_X,
							((i * BLOCK_HEIGHT ) + NEXT_PIECE_Y )));
						break;
						
					case BLOCK_COLOR_ORANGE:
						m_orangeBlock->Animate( m_display, &CPoint( (j * BLOCK_WIDTH) + NEXT_PIECE_X,
							((i * BLOCK_HEIGHT ) + NEXT_PIECE_Y )));
						break;

					default:
						break;

				}
			}
		}
	}

	if ( updateDisintegrate == true )	{
		m_disintegrate->Update();
	} else	{
		m_disintegrate->Reset();
	}
	
}


