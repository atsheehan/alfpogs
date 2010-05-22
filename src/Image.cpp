#include "Image.h"

CImage::CImage ( CCanvas* pcnvSource , CRectangle rcSource , CPoint ptOffset ) 
{
	SetCanvas ( pcnvSource ) ;
	SrcRect ( ) = rcSource ;
	DstRect ( ) = rcSource ;
	DstRect ( ) -= ptOffset ;
}

CImage::~CImage ( ) 
{
}

CCanvas* CImage::GetCanvas ( ) 
{
	return ( m_pcnvSrc ) ;
}

void CImage::SetCanvas ( CCanvas* pcnvSource ) 
{
	m_pcnvSrc = pcnvSource ; 
}

CRectangle& CImage::SrcRect ( ) 
{
	return ( m_rcSrc ) ;
}

CRectangle& CImage::DstRect ( ) 
{
	return ( m_rcDst ) ;
}

void CImage::Put ( CCanvas* pcnvDest , CPoint ptDst ) 
{
	DstRect ( ) += ptDst ;
	pcnvDest->Blit ( DstRect ( ) , *GetCanvas ( ) , SrcRect ( ) ) ;
	DstRect ( ) -= ptDst ;
}


