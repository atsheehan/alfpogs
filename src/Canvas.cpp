#include "Canvas.h"
#include <memory.h>

CCanvas::CCanvas ( SDL_Surface* pSurface ) 
{
	SetSurface ( pSurface ) ;
	m_lstUpdateRects.clear ( ) ;
}

CCanvas::~CCanvas ( ) 
{
	if ( GetSurface ( ) )
	{
		SDL_FreeSurface ( GetSurface ( ) );
		SetSurface ( NULL ) ;
	}
}

SDL_Surface* CCanvas::GetSurface ( ) 
{
	return ( m_pSurface ) ;
}

void CCanvas::SetSurface ( SDL_Surface* pSurface ) 
{
	m_pSurface = pSurface ;
}

bool CCanvas::Lock ( ) 
{
	if ( SDL_MUSTLOCK ( GetSurface ( ) ) )
	{
		if ( SDL_LockSurface ( GetSurface ( ) ) == 0 )
		{
			return ( true ) ;
		}
		else
		{
			return ( false ) ;
		}
	}
	return ( true ) ;
}

void CCanvas::Unlock ( ) 
{
	if ( SDL_MUSTLOCK ( GetSurface ( ) ) ) 
	{
		SDL_UnlockSurface ( GetSurface ( ) ) ;
	}
}

CColor CCanvas::GetPixel ( int x , int y ) 
{
	Uint32 color = 0 ;
	int position = y * GetSurface ( )->pitch + GetSurface ( )->format->BytesPerPixel * x ;
	char* buffer = ( char* ) GetSurface ( )->pixels ;
	buffer += position ;
	memcpy ( &color , buffer , GetSurface ( )->format->BytesPerPixel ) ;
	CColor col ;
	SDL_GetRGB ( color , GetSurface ( )->format , &col.R ( ) , &col.G ( ) , &col.B ( ) ) ;
	return ( col ) ;
}

void CCanvas::SetPixel ( int x , int y , CColor& color ) 
{
	int position = y * GetSurface ( )->pitch + GetSurface ( )->format->BytesPerPixel * x ;
	char* buffer = ( char* ) GetSurface ( )->pixels ;
	buffer += position ;
	Uint32 col = SDL_MapRGB ( GetSurface ( )->format , color.R ( ) , color.G ( ) , color.B ( ) ) ;
	memcpy ( buffer , &col , GetSurface ( )->format->BytesPerPixel ) ;
}

int CCanvas::GetWidth ( ) 
{
	return ( GetSurface ( )->w ) ;
}

int CCanvas::GetHeight ( ) 
{
	return ( GetSurface ( )->h ) ;
}

void CCanvas::AddUpdateRect ( CRectangle& UpdateRect ) 
{
	SDL_Rect* pRect = NULL ;
	pRect = new SDL_Rect ;
	pRect->x = UpdateRect.X ( ) ;
	pRect->y = UpdateRect.Y ( ) ;
	pRect->w = UpdateRect.W ( ) ;
	pRect->h = UpdateRect.H ( ) ;
	m_lstUpdateRects.push_back ( pRect ) ;
}

void CCanvas::ClearUpdateRects ( ) 
{
	list < SDL_Rect* >::iterator iter ;
	SDL_Rect* pRect ;
	while ( !m_lstUpdateRects.empty ( ) )
	{
		iter = m_lstUpdateRects.begin ( ) ;
		pRect = *iter ;
		m_lstUpdateRects.erase ( iter ) ;
		if ( pRect ) delete pRect ;
	}
}

void CCanvas::UpdateRects ( ) 
{
	list < SDL_Rect* >::iterator iter ;
	SDL_Rect* pRect ;
	for ( iter = m_lstUpdateRects.begin ( ) ; iter != m_lstUpdateRects.end ( ) ; iter ++ )
	{
		pRect = *iter ;
		if ( pRect )
		{
			SDL_UpdateRect ( GetSurface ( ) , pRect->x , pRect->y , pRect->w , pRect->h ) ;
		}
		else
		{
			SDL_UpdateRect ( GetSurface ( ) , 0 , 0 , GetWidth ( ) , GetHeight ( ) ) ;
		}
	}
	ClearUpdateRects ( ) ;
}

bool CCanvas::Flip ( ) 
{
	return ( SDL_Flip ( GetSurface ( ) ) == 0 ) ;
}

bool CCanvas::SetColorKey ( CColor& color ) 
{
	Uint32 col = SDL_MapRGB ( GetSurface ( )->format , color.R ( ) , color.G ( ) , color.B ( ) ) ;
	return ( SDL_SetColorKey ( GetSurface ( ) , SDL_SRCCOLORKEY , col ) == 0 ) ;
}

CColor CCanvas::GetColorKey ( ) 
{
	Uint32 col = GetSurface ( )->format->colorkey ;
	CColor color ;
	SDL_GetRGB ( col , GetSurface ( )->format , &color.R ( ) , &color.G ( ) , &color.B ( ) ) ;
	return ( color ) ;
}

bool CCanvas::ClearColorKey ( ) 
{
	return ( SDL_SetColorKey ( GetSurface ( ) , 0 , 0 ) == 0 ) ;
}

void CCanvas::SetClipRect ( CRectangle* pRect ) 
{
	if ( pRect )
	{	
		SDL_SetClipRect ( GetSurface ( ) , *pRect ) ;
	}
	else
	{
		SDL_SetClipRect ( GetSurface ( ) , NULL ) ;
	}
}

CRectangle CCanvas::GetClipRect ( ) 
{
	SDL_Rect rect ;
	SDL_GetClipRect ( GetSurface ( ) , &rect ) ;
	return ( rect ) ;
}

bool CCanvas::FillRect ( CRectangle& rect , CColor& color ) 
{
	Uint32 col = SDL_MapRGB ( GetSurface ( )->format , color.R ( ) , color.G ( ) , color.B ( ) ) ;
	return ( SDL_FillRect ( GetSurface ( ) , rect , col ) == 0 ) ;
}

bool CCanvas::Clear ( CColor& color ) 
{
	Uint32 col = SDL_MapRGB ( GetSurface ( )->format , color.R ( ) , color.G ( ) , color.B ( ) ) ;
	return ( SDL_FillRect ( GetSurface ( ) , NULL , col ) == 0 ) ;
}

bool CCanvas::Blit ( CRectangle& rectDst , CCanvas& cnvSrc , CRectangle& rectSrc ) 
{
	CRectangle rectDst2 = rectDst ;
	return ( SDL_BlitSurface ( cnvSrc.GetSurface ( ) , rectSrc , GetSurface ( ) , rectDst2 ) == 0 );
}

CCanvas* CCanvas::CreateRGB ( Uint32 flags , int width , int height, int depth, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask) 
{
	CCanvas* pCanvas = new CCanvas ( NULL ) ;
	
	pCanvas->SetSurface ( SDL_CreateRGBSurface ( flags , width , height, depth , Rmask, Gmask, Bmask , Amask ) ) ;

	return ( pCanvas ) ;
}

CCanvas* CCanvas::CreateRGBCompatible ( Uint32 flags , int width , int height ) 
{
	SDL_PixelFormat* format = SDL_GetVideoSurface ( )->format ;

	return ( CreateRGB ( flags , width , height , format->BitsPerPixel , format->Rmask , format->Gmask , format->Bmask , format->Amask ) ) ;
}

CCanvas* CCanvas::LoadBMP ( string sFileName ) 
{
	SDL_Surface* pSurface = SDL_LoadBMP ( sFileName.c_str ( ) ) ;
	return ( new CCanvas ( pSurface ) ) ;
}

CCanvas* CCanvas::LoadBMPCompatible ( string sFileName ) 
{
	SDL_Surface* pSurface = SDL_LoadBMP ( sFileName.c_str ( ) ) ;
	SDL_Surface* pSurface2 = SDL_DisplayFormat ( pSurface ) ;
	SDL_FreeSurface ( pSurface ) ;
	return ( new CCanvas ( pSurface2 ) ) ;
}

//match color with closest
CColor CCanvas::MatchColor ( CColor color ) 
{
	//convert it to the pixel format
	Uint32 col = SDL_MapRGB ( GetSurface ( )->format , color.R ( ) , color.G ( ) , color.B ( ) ) ;

	//convert it from the pixel format
	SDL_GetRGB ( col , GetSurface ( )->format , &color.R ( ) , &color.G ( ) , &color.B ( ) ) ;

	//return the matched color
	return ( color ) ;
}
