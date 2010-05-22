//include guards
#ifndef __CANVAS_H__
#define __CANVAS_H__

#include "sdl.h"
#include "color.h"
#include "rectangle.h"
#include <list>
#include <string>
using namespace std;

//CCanvas class
class CCanvas
{
private:
	//a list of update rectangles
	list < SDL_Rect* > m_lstUpdateRects ;

protected:
	//pointer to an SDL_Surface
	SDL_Surface* m_pSurface ;

public:
	//constructor
	CCanvas ( SDL_Surface* pSurface = NULL ) ;

	//destructor
	virtual ~CCanvas ( ) ;

	//getter/setter for the SDL_Surface*
	SDL_Surface* GetSurface ( ) ;
	void SetSurface ( SDL_Surface* pSurface ) ;

	//lock and unlock ( for direct pixel access )
	bool Lock ( ) ;
	void Unlock ( ) ;

	//get/set pixel (canvas should be locked)
	CColor GetPixel ( int x , int y ) ;
	void SetPixel ( int x , int y , CColor& color ) ;

	//match color with closest
	CColor MatchColor ( CColor color ) ;

	//width and height retrieval
	int GetWidth ( ) ;
	int GetHeight ( ) ;

	//add an update rectangle
	void AddUpdateRect ( CRectangle& pUpdateRect ) ;

	//clear all update rectangles
	void ClearUpdateRects ( ) ;

	//update any rectangles in the queue
	void UpdateRects ( ) ;

	//flip surface.  normally, this just updates the entire surface
	bool Flip ( ) ;

	//set a color key
	bool SetColorKey ( CColor& color ) ;

	//retrieve the color key
	CColor GetColorKey ( ) ;

	//clear the color key
	bool ClearColorKey ( ) ;

	//set the clipping rectangle
	void SetClipRect ( CRectangle* pRect ) ;

	//get the clipping rectangle
	CRectangle GetClipRect ( ) ;

	//solid color fill fill a rectangle
	bool FillRect ( CRectangle& rect , CColor& color ) ;

	//clear entire surface to a color
	bool Clear ( CColor& color ) ;

	//blit to this surface from another surface
	bool Blit ( CRectangle& rectDst , CCanvas& cnvSrc , CRectangle& rectSrc ) ;

	//factory methods
	//create an rgb surface of a particular format
	static CCanvas* CreateRGB ( Uint32 flags , int width , int height, int depth, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask) ;
	//create an rgb surface of the display format
	static CCanvas* CreateRGBCompatible ( Uint32 flags , int width , int height ) ;

	//load a bitmap
	static CCanvas* LoadBMP ( string sFileName ) ;
	//load a bitmap, convert it to the display format
	static CCanvas* LoadBMPCompatible ( string sFileName ) ;
} ;

#endif