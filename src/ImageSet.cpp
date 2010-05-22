#include "ImageSet.h"
#include <algorithm>

CImageSet::CImageSet()
{
	ImageList ( ).clear ( ) ;
}

CImageSet::~CImageSet()
{
	vector < CImage* >::iterator iter ;
	CImage* pimg ;
	while ( !ImageList ( ).empty ( ) )
	{
		iter = ImageList().begin ( ) ;
		pimg = *iter ;
		ImageList ( ).erase ( iter ) ;
		delete pimg ;
	}
}

void CImageSet::AddImage ( CImage* pimg ) 
{
	ImageList ( ).push_back ( pimg ) ;
}

bool CImageSet::HasImage ( CImage* pimg ) 
{
	vector < CImage* >::iterator iter = find ( ImageList ( ).begin ( ) , ImageList ( ).end ( ) , pimg ) ;
	return ( iter != ImageList ( ).end ( ) ) ;
}

int CImageSet::FindImage ( CImage* pimg ) 
{
	vector < CImage* >::iterator iter = find ( ImageList ( ).begin ( ) , ImageList ( ).end ( ) , pimg ) ;
	if ( iter == ImageList ( ).end ( ) ) return ( -1 ) ;
	return ( iter - ImageList ( ).begin ( ) ) ;
}

void CImageSet::RemoveImage ( CImage* pimg ) 
{
	vector < CImage* >::iterator iter = find ( ImageList ( ).begin ( ) , ImageList ( ).end ( ) , pimg ) ;
	if ( iter == ImageList ( ).end ( ) ) return ;
	ImageList ( ).erase ( iter ) ;
}

CImage* CImageSet::GetImage ( int index ) 
{
	return ( ImageList ( ) [ index ] ) ;
}

vector < CImage* >& CImageSet::ImageList ( ) 
{
	return ( m_vecImages ) ;
}

int CImageSet::ImageCount ( ) 
{
	return ( ImageList ( ).size ( ) ) ;
}

