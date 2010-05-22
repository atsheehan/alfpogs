
// Contains information on how to animate an ImageSet

#ifndef APANIMATION_H
#define APANIMATION_H

#include "ImageSet.h"
#include <string>
using std::string;

class CAnimation	{

public:

	// Constructor
	CAnimation( CImageSet* p_frames = 0, int p_delay = 0 );
	// Destructor
	~CAnimation();

	// Resets the ImageSet
	void SetImages( CImageSet* p_newImageSet );

	// Returns the current ImageSet
	CImageSet* GetImages();

	// Returns the total number of frames
	int GetNumberOfFrames();

	// Sets a new frame delay
	void SetDelay( int p_newDelay );

	// Draws the current frame on the given surface
	// at the given coordinates
	void Animate( CCanvas* p_destination, CPoint* p_coordinates );

	// Checks to see whether the animation should move to the
	// next frame
	void Update();

	// Resets the current frame back to zero
	void Reset();

	// Sets the transparency color key for the animation
	void SetColorKey( CColor& p_key );
    
private:

	// Contains the series of images used for the frames of animtion
	CImageSet* m_frames;

	// The total number of frames in the animation
	int m_totalFrames;

	// The current frame that the animation is drawing
	int m_currentFrame;

	// A universal delay for each frame
	int m_frameDelay;
	int m_delayCounter;

};


// A utility function used to load frames of an animation from a templated
// bitmap. 
CAnimation* APAnimationLoader( string p_filename, int p_frameWidth, int p_frameHeight,
					   int p_totalFrames, int p_numOfColumns, int p_startX, int p_startY,
					   int p_depth = 32, int p_delay = 0 );

void APAnimationCleanup( CAnimation* p_animation );

#endif	// APANIMATION_H

