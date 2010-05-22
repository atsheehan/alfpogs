// Handles the audio
#ifndef AUDIO_H
#define AUDIO_H

// FMOD includes
#include "fmod.hpp"

const int AUDIO_CHANNELS = 100;
const int MUSIC_CHANNEL = 1;

const int MAX_MUSIC = 3;
const int MIN_MUSIC = 1;

class CAudio	{

public:

	// Constructor
	CAudio();

	// Destructor
	~CAudio();

	// Plays one of the songs
	void PlayMusic( int p_index );

private:

	// The music system
	FMOD::System* m_audioSystem;

	// Contains information if any errors occur
	FMOD_RESULT m_result;

	// The songs
	FMOD::Sound* m_music[ MAX_MUSIC ];

	// The music channel
	FMOD::Channel* m_musicChannel;

};


#endif	// AUDIO_H