// Handles the audio

#include "Audio.h"


// Constructor
CAudio::CAudio()		{

	// Initialize FSOUND
	m_result = FMOD::System_Create( &m_audioSystem );
	if ( m_result != FMOD_OK )	{
		//exit( 1 );
	}

	m_result = m_audioSystem->init( AUDIO_CHANNELS, FMOD_INIT_NORMAL, 0 );
	if ( m_result != FMOD_OK )	{
		//exit( 1 );
	}
	
	//// Load the music into memory and set to infinite loop
	m_audioSystem->createSound( "jingjingading.mid", FMOD_DEFAULT, 0, &m_music[ 0 ] );
	m_music[ 0 ]->setLoopCount( -1 );
	m_music[ 0 ]->setMode( FMOD_LOOP_NORMAL );
	m_audioSystem->createSound( "bloobleeblah.mid", FMOD_DEFAULT, 0, &m_music[ 1 ] );
	m_music[ 1 ]->setLoopCount( -1 );
	m_music[ 1 ]->setMode( FMOD_LOOP_NORMAL );
	m_audioSystem->createSound( "I'm at a loss.mid", FMOD_DEFAULT, 0, &m_music[ 2 ] );
	m_music[ 2 ]->setLoopCount( -1 );
	m_music[ 2 ]->setMode( FMOD_LOOP_NORMAL );

	// Play the song
	m_audioSystem->playSound( FMOD_CHANNEL_FREE, m_music[ 0 ], false, &m_musicChannel );
	


}



// Destructor
CAudio::~CAudio()		{

	// This function handles all of the FMOD memory
	m_audioSystem->release();

}



// Plays one of the songs
void CAudio::PlayMusic( int p_index )		{

	m_audioSystem->playSound( FMOD_CHANNEL_REUSE, m_music[ p_index ], false, &m_musicChannel );

}