// Draws the grid with all fo the blocks

#ifndef GRIDARTIST_H
#define GRIDARTIST_H

#include "Grid.h"
#include "APAnimation.h"
#include <fstream>
using std::ofstream;

// Grid dimensions
const int GRID_STARTING_X = 220;
const int GRID_STARTING_Y = 0;

const int NEXT_PIECE_X = 490;
const int NEXT_PIECE_Y = 150;

// Block dimensions
const int BLOCK_WIDTH = 20;
const int BLOCK_HEIGHT = 20;

class CGridArtist	{

public:

	// Constructor
	CGridArtist();

	// Destructor
	~CGridArtist();

	// Sets the grid to be drawn from
	void SetGrid( CGrid* p_grid );

	// Sets the drawing area
	void SetDisplay( CCanvas* p_display );

	// Draws the grid
	void DrawGrid();

private:

	CGrid* m_grid;
	CCanvas* m_display;

	CAnimation* m_redBlock;
	CAnimation* m_blueBlock;
	CAnimation* m_greenBlock;
	CAnimation* m_purpleBlock;
	CAnimation* m_orangeBlock;
	CAnimation* m_yellowBlock;
	CAnimation* m_disintegrate;
	CAnimation* m_grayBlock;

	ofstream out;

};

#endif	// GRIDARTIST_H