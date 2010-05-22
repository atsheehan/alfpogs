// Keeps track of the number of lines cleared and the total score
#ifndef SCORER_H
#define SCORER_H

// These are used to pass information from the menu state to the running state.
extern int g_passLevel;
extern int g_passMusic;

const int MAX_LEVEL = 9;
const int MIN_LEVEL = 0;
const int NUM_OF_LINES_TO_LEVEL = 10;	// Number of lines cleared before increasing the level

const int DEFAULT_DELAY = 1000;	// 1 second
const int MIN_DELAY = 100;	// delay at the max level ( 1/10th of a second)

// The timer delay decreases by this amount each level
const int DELAY_MULTIPLE = (DEFAULT_DELAY - MIN_DELAY) / MAX_LEVEL;

// This is the base amount of points for each line clear
const int BASE_POINTS = 100;

// Forward declaration
class CGridTimer;


class CScorer	{

public:

	// Constructor
	CScorer();

	// Destructor
	~CScorer();

	// Adds lines cleared
	void AddLinesCleared( int p_numberOfLines );

	// Resets the number of lines and total score
	void ResetLines();

	// Sets the level to a specific value
	void SetLevel( int p_level );

	// Sets the grid timer
	void SetTimer( CGridTimer* p_timer );

	// Stops and starts the timer
	void StopTimer();
	void StartTimer();

	// Returns information on the score, lines cleared, or current level
	int GetScore()	{ return m_totalScore;	}
	int GetLevel()	{ return m_level;	}
	int GetLines()	{ return m_numberOfLinesCleared;	}

private:

	// Increases the level and speeds up the blocks
	void IncreaseLevel();

	int m_numberOfLinesCleared;
	int m_totalScore;
	int m_linesUntilLevel;

	// The level determines how fast the blocks move down on the timer
	int m_level;
	int m_delay;
	CGridTimer* m_timer;
};

#endif	// SCORER_H