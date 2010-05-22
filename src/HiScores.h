// Contains information about the hi scores
#ifndef	HISCORES_H
#define HISCORES_H

// The number of hi scores to save
const int MAX_HI_SCORES = 4;
const int MAX_SCORE = 999999;


class CHiScores		{

public:

	// Constructor
	CHiScores();

	// Destructor
	~CHiScores();

	// Loads the hi scores from a file
	bool LoadScores();

	// Returns the hi score at the given index
	int GetScore( int p_index );

	// Compares the given score to the current records to determine if it is worth keeping
	void AddScore( int p_newScore );

private:

	// Orders the hi scores
	void SortScores();

	// The hi scores
	int m_hiScore[ MAX_HI_SCORES ];



};

#endif	// HISCORES_H