// The grid contains information for the blocks on the screen
// as well as the falling piece.

#ifndef GRID_H
#define GRID_H

#include "Piece.h"
#include "Scorer.h"
#include <vector>
using std::vector;

// Determines the color of the block in the grid
const int BLOCK_UNOCCUPIED = 0;
const int BLOCK_COLOR_RED = 1;
const int BLOCK_COLOR_BLUE = 2;
const int BLOCK_COLOR_GREEN = 3;
const int BLOCK_COLOR_YELLOW = 4;
const int BLOCK_COLOR_PURPLE = 5;
const int BLOCK_COLOR_ORANGE = 6;
const int BLOCK_DISINTEGRATE = 7;
const int BLOCK_COLOR_GRAY = 8;

// Wait one second for the block to disintegrate
const int DISINTEGRATE_DELAY = 400;

// The size of the grid
const int GRID_WIDTH = 10;
const int GRID_HEIGHT = 22;
const int GRID_ARRAY_SIZE = GRID_WIDTH * GRID_HEIGHT;
const int GRID_OVERFLOW = 2;	// This is the cutoff for where the blocks flow over the top of the grid i.e. game over

// Default piece locations
const int DEFAULT_PIECE_X = 3;
const int DEFAULT_PIECE_Y = 0;

class CHiScores;

class CGrid		{

public:

	// Constructor
	CGrid();

	// Destructor
	~CGrid();

	// Moves the piece to the right or left
	void MovePieceRight();
	void MovePieceLeft();

	// Drops the piece down one step. Returns 1 if it hits something
	int MovePieceDown();

	// Drops the piece until it hits another block or the bottom
	void DropPiece();

	// Rotates the piece clockwise
	void RotatePiece();

	// Returns the grid array
	int* GetGrid();

	// Returns the piece array
	int* GetActivePiece();
	int* GetNextPiece();

	// Returns the pieces location
	int GetPieceXLoc()	{ return m_xPos;	}
	int GetPieceYLoc()	{ return m_yPos;	}

	// Sets the timer for the grid
	void SetScoreTimer( CGridTimer* p_timer );

	// Stops the game when the grid overflows
	void GameOver();

	// Resets the grid and starts over
	void Reset();

	// Restarts the timer
	void Resume();

	// Stops the timer
	void Pause();

	// Returns a pointer to the scorer
	CScorer* GetScorer()	{ return &m_scorer;		}

	// Sets the hi score pointer
	void SetHiScores( CHiScores* p_hiScores )	{ m_hiScores = p_hiScores;	}

	// Returns true if the game is over
	bool IsGameOver()	{ return m_gameOver;	}

	void Update();


private:

	// Attaches the piece to the grid and generates a new piece
	void AttachPieceToGrid();

	// Checks to see if there are any full lines
    void CheckForLines();

	// Clears the lines and drops all of the blocks above it down
	void ClearLines();

	// Sets the disintegrationg animation and pauses the game until they are finished
	void DisintegrateLines();

	// The grid
	int m_grid[ GRID_ARRAY_SIZE ];

	// The active piece and the next piece
	CPiece m_activePiece;
	CPiece m_nextPiece;
	int m_nextPieceConfig;

	// Position of the top left corner of the active piece
	int m_xPos;
	int m_yPos;

	// Controls the levels and scores in the game as well as the speed
	// with which the blocks fall
	CScorer m_scorer;

	// Determines when you can move the piece around the grid
	bool m_gridInactive;
	bool m_gameOver;

	bool m_animating;
	int m_endTime;

	vector<int> m_lines;

	// Checks to see if the hi score beats any previous records
	CHiScores* m_hiScores;
};

#endif	// GRID_H