// Contains information on how to animate an ImageSet

#include "APAnimation.h"

// Constructor
CAnimation::CAnimation( CImageSet* p_frames, int p_delay ) :
m_frames( p_frames ),
m_frameDelay( p_delay ),
m_delayCounter( 0 ),
m_currentFrame( 0 )		{

	// Determine the total number of frames
	if ( m_frames == 0 )	{
		m_totalFrames = 0;
	} else	{
		m_totalFrames = m_frames->ImageCount();
	}
}



// Destructor
CAnimation::~CAnimation()	{
}



// Resets the ImageSet
void CAnimation::SetImages( CImageSet* p_newImageSet )	{
	m_frames = p_newImageSet;
}



// Returns the current ImageSet
CImageSet* CAnimation::GetImages()	{
	return m_frames;
}


// Returns the total number of frames
int CAnimation::GetNumberOfFrames()		{
	return m_totalFrames;
}



// Sets a new frame delay
void CAnimation::SetDelay( int p_newDelay )		{
	m_frameDelay = p_newDelay;
}



// Draws the current frame on the given surface
// at the given coordinates
void CAnimation::Animate( CCanvas* p_destination, 
	CPoint* p_coordinates )		{

	 // Retrieve the current frame from the ImageSet and draw it
	 // on the display surface
	CImage* tempImage = m_frames->GetImage( m_currentFrame );
	
	tempImage->Put( p_destination, *p_coordinates );
}



// Checks to see whether the animation should move to the
// next frame
void CAnimation::Update()	{

	// Check to see if enough time has elapsed to move to the next frame
	if ( m_delayCounter >= m_frameDelay )	{
	
		m_delayCounter = 0;
		// Check to see if the animation should loop back to the start
		if ( m_currentFrame <= ( m_totalFrames - 2 ))	{
			m_currentFrame++;
		} else	{
			m_currentFrame = 0;
		}
	} else	{
		m_delayCounter++;
	}


}


// Resets the frame back to 0
void CAnimation::Reset()	{

	m_currentFrame = 0;

}



// A utility function used to load frames of an animation from a templated bitmap
CAnimation* APAnimationLoader( string p_filename, int p_frameWidth, int p_frameHeight,
int p_totalFrames, int p_numOfColumns, int p_startX, int p_startY, int p_depth, int p_delay )	{

	// Load the entire bitmap onto a surface
	SDL_Surface* templatedBitmap = SDL_LoadBMP( p_filename.c_str() );
	
	if ( templatedBitmap == 0 )	{
		return 0;
	}

	// Create the imageset that holds all of the frames
	CImageSet* newImageSet = new CImageSet();
	
	// source and destination rectangles for blitting
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.h = p_frameHeight;
	srcRect.w = p_frameWidth;

	destRect.x = 0;
	destRect.y = 0;
	destRect.h = p_frameHeight;
	destRect.w = p_frameWidth;

	// Used in creating the Image object. The source rectangle will be the entire
	// surface and there will be no offset
	CRectangle imageRect( 0, 0, p_frameWidth, p_frameHeight );
	CPoint imageOffset( 0, 0 );
	
	// Load each frame onto a new image
	for ( int currFrame = 0; currFrame < p_totalFrames; ++currFrame )	{
		
		// Calculate the x and y coordinates that the next frame will start on
		// from the templated bitmap
		srcRect.x = p_startX + ( currFrame % p_numOfColumns ) * p_frameWidth;
		srcRect.y = p_startY + ( currFrame / p_numOfColumns ) * p_frameHeight;
		
		// Create a new surface and blit the single frame of animation onto it
		SDL_Surface* newFrame = SDL_CreateRGBSurface( SDL_HWSURFACE, p_frameWidth, 
			p_frameHeight, p_depth, 0, 0, 0, 0 );
		SDL_BlitSurface( templatedBitmap, &srcRect, newFrame, &destRect );

        // Create a canvas object to hold the surface, then create an image object
		// to hold the canvas
		CCanvas* newCanvas = new CCanvas( newFrame );
		CImage* newImage = new CImage( newCanvas, imageRect, imageOffset );

		// Add the new image class to the vector
		newImageSet->AddImage( newImage );
	}

	SDL_FreeSurface( templatedBitmap );

	// Create the animation class
	CAnimation* newAnimation = new CAnimation( newImageSet, p_delay );

	// Return a pointer to the CAnimation object
	return newAnimation;
}


void APAnimationCleanup( CAnimation* p_animation )	{

	CImageSet* frames = p_animation->GetImages();
	int totalFrames = p_animation->GetNumberOfFrames();

	// Must delete the Canvases, Images, and ImageSet for the animation
	for ( int currentFrame = 0; currentFrame < totalFrames; currentFrame++ )	{
	
		CImage* tempImage = frames->GetImage( currentFrame );
		CCanvas* tempCanvas = tempImage->GetCanvas();
		
		// The surfaces are freed in the Canvas destructor
		delete tempCanvas;
		tempCanvas = 0;
	}
	// The Image objects are deleted in the ImageSet destructor
	delete frames;
}

// Sets the transparency color key for the animation
void CAnimation::SetColorKey( CColor& p_key )		{

	int totalFrames = m_frames->ImageCount();

	// Set the color key for each surface
	for ( int i = 0; i < totalFrames; i++ )	{
		CImage* image = m_frames->GetImage( i );
		CCanvas* tempCanvas = image->GetCanvas();
		tempCanvas->SetColorKey( p_key );
	}
}