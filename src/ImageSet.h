#ifndef __IMAGESET_H__
#define __IMAGESET_H__

#include "Image.h"
#include <vector>
using namespace std;

//CImageSet--controls any number of images
class CImageSet  
{
private :
	//container for images
	vector < CImage* > m_vecImages ;
public:
	//construct empty image set
	CImageSet();
	virtual ~CImageSet();
	//add an image
	void AddImage ( CImage* pimg ) ;
	//check for an image in the list
	bool HasImage ( CImage* pimg ) ;
	//find an image
	int FindImage ( CImage* pimg ) ;
	//remove an image
	void RemoveImage ( CImage* pimg ) ;
	//retrieve an image from the list by index
	CImage* GetImage ( int index ) ;
	//access image list directly
	vector < CImage* >& ImageList ( ) ;
	//retrieve number of images in the set
	int ImageCount ( ) ;
};

#endif // !defined(AFX_IMAGESET_H__61209253_2528_46E3_A688_679AA42FFB5E__INCLUDED_)
