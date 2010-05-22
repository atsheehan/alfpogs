#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "Canvas.h"

//CImage--abstracts a blittable portion of a canvas
class CImage  
{
private:
	//pointer to canvas
	CCanvas* m_pcnvSrc ;
	//source rectangle
	CRectangle m_rcSrc ;
	//destination rectangle
	CRectangle m_rcDst ;
public:
	//construct from source canvas, source rectangle,and offset point
	CImage ( CCanvas* pcnvSource , CRectangle rcSource , CPoint ptOffset ) ;
	//destroy image
	virtual ~CImage ( ) ;
	//retrieve pointer to canvas
	CCanvas* GetCanvas ( ) ;
	//set new canvas
	void SetCanvas ( CCanvas* pcnvSource ) ;
	//access source rectangle
	CRectangle& SrcRect ( ) ;
	//access destination rectangle
	CRectangle& DstRect ( ) ;
	//blit image onto a canvas
	void Put ( CCanvas* pcnvDest , CPoint ptDst ) ;
};

#endif
