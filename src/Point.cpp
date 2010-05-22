#include "Point.h"
#include <math.h>

//constructor
CPoint::CPoint ( int x , int y ) 
{
	//set the x and y of the point
	Set ( x , y ) ;
}

CPoint::CPoint ( CPoint& pt ) 
{
	//set x and y of the point
	SetX ( pt.GetX ( ) ) ;
	SetY ( pt.GetY ( ) ) ;
}


//destructor
CPoint::~CPoint ( ) 
{
	//do nothing
}

//properties
int& CPoint::X ( ) 
{
	//return x component
	return ( m_x ) ;
}

int& CPoint::Y ( ) 
{
	//return y component
	return ( m_y ) ;
}

int CPoint::GetX ( ) const
{
	//return x component
	return ( m_x ) ;
}

int CPoint::GetY ( ) const
{
	//return y component
	return ( m_y ) ;
}

void CPoint::SetX ( int x ) 
{
	//assign new value to x component
	m_x = x ;
}

void CPoint::SetY ( int y ) 
{
	//assign new value to y component
	m_y = y ;
}

//setter
CPoint& CPoint::Set ( int x , int y ) 
{
	//set x and y
	X ( ) = x ;
	Y ( ) = y ;
	//return this point
	return ( *this ) ;
}

CPoint& CPoint::Copy ( CPoint& pt ) 
{
	//copy x and y
	X ( ) = pt.X ( ) ;
	Y ( ) = pt.Y ( ) ;
	//return this point
	return ( *this ) ;
}

//move
CPoint& CPoint::Move ( int dx , int dy ) 
{
	//move x and y
	X ( ) += dx ;
	Y ( ) += dy ;
	//return this point
	return ( *this ) ;
}

CPoint& CPoint::Add ( CPoint& pt ) 
{
	//add point to this point
	( *this ) += pt ;
	//return this point
	return ( *this ) ;
}

CPoint& CPoint::Subtract ( CPoint& pt ) 
{
	//subtract point from this point
	( *this ) -= pt ;
	//return this point
	return ( *this ) ;
}

//scale
CPoint& CPoint::Scale ( int scalar ) 
{
	//multiply this point by a scalar
	( *this ) *= scalar ;
	//return this point
	return ( *this ) ;
}

//distance
int CPoint::Distance ( CPoint& pt ) 
{
	//calculate distance
	int distance = X ( ) * X ( ) + Y ( ) * Y ( ) ;
	distance = sqrt ( (float)distance ) ;
	//return the distance
	return ( distance ) ;
}

//operators
//assignment
CPoint& CPoint::operator = ( CPoint& pt ) 
{
	//copy x and y
	X ( ) = pt.X ( ) ;
	Y ( ) = pt.Y ( ) ;
	//return this point
	return ( *this ) ;
}

CPoint& CPoint::operator += ( CPoint& pt ) 
{
	//add to x and y
	X ( ) += pt.X ( ) ;
	Y ( ) += pt.Y ( ) ;
	//return this point
	return ( *this ) ;
}

CPoint& CPoint::operator -= ( CPoint& pt ) 
{
	//subtract x and y
	X ( ) -= pt.X ( ) ;
	Y ( ) -= pt.Y ( ) ;
	//return this point
	return ( *this ) ;
}

CPoint& CPoint::operator *= ( int scalar ) 
{
	//multiply by scalar
	X ( ) *= scalar ;
	Y ( ) *= scalar ;
	//return this point
	return ( *this ) ;
}

CPoint& CPoint::operator /= ( int scalar ) 
{
	//divide by scalar
	X ( ) /= scalar ;
	//return this point
	return ( *this ) ;
}

//unary
CPoint CPoint::operator - ( ) 
{
	//unary negativeness--multiply by -1
	CPoint pt = ( *this ) ;
	pt *= -1 ;
	return ( pt ) ;
}

CPoint CPoint::operator + ( ) 
{
	//unary positiveness
	return ( *this ) ;
}

CPoint CPoint::operator + ( CPoint& pt ) 
{
	//add points together
	CPoint result ;
	result = ( *this ) ;
	result += pt ;
	//return new point
	return ( result ) ;
}

CPoint CPoint::operator - ( CPoint& pt ) 
{
	//subtract points
	CPoint result ;
	result = ( *this ) ;
	result -= pt ;
	//return new point
	return ( result ) ;
}

CPoint CPoint::operator * ( int scalar ) 
{
	//multiply point by scalar
	CPoint result ;
	result = ( *this ) ;
	result *= scalar ;
	//return new point
	return ( result ) ;
}

CPoint CPoint::operator / ( int scalar ) 
{
	//divide by scalar
	CPoint result ;
	result = ( *this ) ;
	result /= scalar ;
	//return new point
	return ( result ) ;
}

//comparison
bool CPoint::operator == ( CPoint& pt ) 
{
	//check for equality
	return ( X ( ) == pt.X ( ) && Y ( ) == pt.Y ( ) ) ;
}

bool CPoint::operator != ( CPoint& pt ) 
{
	//check for inequality
	return ( !( ( *this ) == pt ) ) ;
}

CPoint operator * ( int scalar , CPoint& pt ) 
{
	//scalar*pt rather than pt*scalar, still the same idea...
	CPoint result = pt * scalar ;
	return ( result ) ;
}
