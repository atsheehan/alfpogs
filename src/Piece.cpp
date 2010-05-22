 //Controls the six different block configurations

#include "Piece.h"
#include <cstdlib>

// Constructor
CPiece::CPiece()	{
	GenerateNewPiece();
}


// Destructor
CPiece::~CPiece()	{
}


// Rotates the piece counter clockwise
void CPiece::Rotate()	{

	// Loop the rotation if needed
	if ( m_rotation >= NUM_OF_ROTATIONS - 1 )	{
		m_rotation = 0;
	} else	{
		m_rotation++;
	}

	// Copy the configuration into the piece
	for ( int i = 0; i < PIECE_HEIGHT; ++i )	{
		for ( int j = 0; j < PIECE_WIDTH; ++j )		{
			int index = (i * PIECE_WIDTH) + j;
			m_piece[ index ] = ARRAY_CONFIG[ m_config ][ m_rotation ][ index ];
		}
	}
}

// Rotates the piece clockwise
void CPiece::RotateClockwise()		{

	// Loop the rotation if needed
	if ( m_rotation <= 0 )	{
		m_rotation = NUM_OF_ROTATIONS - 1;
	} else	{
		m_rotation--;
	}

	// Copy the configuration into the piece
	for ( int i = 0; i < PIECE_HEIGHT; ++i )	{
		for ( int j = 0; j < PIECE_WIDTH; ++j )		{
			int index = (i * PIECE_WIDTH) + j;
			m_piece[ index ] = ARRAY_CONFIG[ m_config ][ m_rotation ][ index ];
		}
	}
}


// Generates a new piece from one of the six configurations. Returns the configuration index
int CPiece::GenerateNewPiece( int p_config )		{

	// If no config is given, randomly choose one of the six
	if ( p_config < 0 || p_config > 5 )	{
		m_config = rand() % NUM_OF_SHAPES;
	} else	{
		m_config = p_config;
	}

	// Each piece starts in the rotational position 0
	m_rotation = 0;

	// Copy the configuration into the piece
	for ( int i = 0; i < PIECE_HEIGHT; ++i )	{
		for ( int j = 0; j < PIECE_WIDTH; ++j )		{
			int index = (i * PIECE_WIDTH) + j;
			m_piece[ index ] = ARRAY_CONFIG[ m_config ][ m_rotation ][ index ];
		}
	}

	return m_config;
}



// Returns the current configuration
int* CPiece::GetConfiguration()		{
	return m_piece;
}