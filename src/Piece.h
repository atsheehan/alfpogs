// Controls the six different block configurations

#ifndef PIECE_H
#define PIECE_H

// Dimensions of the piece
const int PIECE_WIDTH = 4;
const int PIECE_HEIGHT = 4;
const int PIECE_ARRAY_SIZE = PIECE_WIDTH * PIECE_HEIGHT;

// Configurations
const int NUM_OF_SHAPES = 6;
const int NUM_OF_ROTATIONS = 4;
const int ARRAY_CONFIG[ NUM_OF_SHAPES ][ NUM_OF_ROTATIONS ][ PIECE_ARRAY_SIZE ]	=
{
	{
		{ 0, 0, 1, 0,
		  0, 0, 1, 0,
		  0, 0, 1, 0,
		  0, 0, 1, 0
		},
		{ 0, 0, 0, 0,
		  0, 0, 0, 0,
		  1, 1, 1, 1,
		  0, 0, 0, 0
		},
		{ 0, 1, 0, 0,
		  0, 1, 0, 0,
		  0, 1, 0, 0,
		  0, 1, 0, 0
		},
		{ 0, 0, 0, 0,
		  1, 1, 1, 1,
		  0, 0, 0, 0,
		  0, 0, 0, 0
		}
	},
	{
		{ 0, 0, 2, 0,
		  0, 0, 2, 0,
		  0, 2, 2, 0,
		  0, 0, 0, 0
		},
		{ 0, 0, 0, 0,
		  0, 2, 0, 0,
		  0, 2, 2, 2,
		  0, 0, 0, 0
		},
		{ 0, 0, 0, 0,
		  0, 2, 2, 0,
		  0, 2, 0, 0,
		  0, 2, 0, 0
		},
		{ 0, 0, 0, 0,
		  2, 2, 2, 0,
		  0, 0, 2, 0,
		  0, 0, 0, 0
		}
	},
	{
		{ 0, 3, 0, 0,
		  0, 3, 0, 0,
		  0, 3, 3, 0,
		  0, 0, 0, 0
		},
		{ 0, 0, 0, 0,
		  0, 3, 3, 3,
		  0, 3, 0, 0,
		  0, 0, 0, 0
		},
		{ 0, 0, 0, 0,
		  0, 3, 3, 0,
		  0, 0, 3, 0,
		  0, 0, 3, 0
		},
		{ 0, 0, 0, 0,
		  0, 0, 3, 0,
		  3, 3, 3, 0,
		  0, 0, 0, 0
		}
	},
	{
		{ 0, 4, 0, 0,
		  0, 4, 4, 0,
		  0, 0, 4, 0,
		  0, 0, 0, 0
		},
		{ 0, 0, 0, 0,
		  0, 0, 4, 4,
		  0, 4, 4, 0,
		  0, 0, 0, 0
		},
		{ 0, 0, 0, 0,
		  0, 4, 0, 0,
		  0, 4, 4, 0,
		  0, 0, 4, 0
		},
		{ 0, 0, 0, 0,
		  0, 4, 4, 0,
		  4, 4, 0, 0,
		  0, 0, 0, 0
		}
	},
	{
		{ 0, 0, 5, 0,
		  0, 5, 5, 0,
		  0, 5, 0, 0,
		  0, 0, 0, 0
		},
		{ 0, 0, 0, 0,
		  0, 5, 5, 0,
		  0, 0, 5, 5,
		  0, 0, 0, 0
		},
		{ 0, 0, 0, 0,
		  0, 0, 5, 0,
		  0, 5, 5, 0,
		  0, 5, 0, 0
		},
		{ 0, 0, 0, 0,
		  5, 5, 0, 0,
		  0, 5, 5, 0,
		  0, 0, 0, 0
		}
	},
	{
		{ 0, 0, 0, 0,
		  0, 6, 6, 0,
		  0, 6, 6, 0,
		  0, 0, 0, 0
		},
		{ 0, 0, 0, 0,
		  0, 6, 6, 0,
		  0, 6, 6, 0,
		  0, 0, 0, 0
		},
		{ 0, 0, 0, 0,
		  0, 6, 6, 0,
		  0, 6, 6, 0,
		  0, 0, 0, 0
		},
		{ 0, 0, 0, 0,
		  0, 6, 6, 0,
		  0, 6, 6, 0,
		  0, 0, 0, 0
		}
	}
};

class CPiece	{

public:

	// Constructor
	CPiece();

	// Destructor
	~CPiece();

	// Rotates the piece counter clockwise
	void Rotate();

	// Rotates the piece clockwise
	void RotateClockwise();

	// Generates a new piece from one of the six configurations. Returns the configuration index
	int GenerateNewPiece( int p_config = -1 );

	// Returns the current configuration
	int* GetConfiguration();

private:

	// Holds the configuration of the piece
	int m_piece[ PIECE_ARRAY_SIZE ];

	// The index for the configuration
	int m_config;

	// The current rotational shape of the piece
	int m_rotation;


};

#endif	// PIECE_H