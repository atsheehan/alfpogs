//sentinel
#ifndef __POINT_H__
#define __POINT_H__

//point class
class CPoint  
{
private:
	//x and y
	int m_x ;
	int m_y ;
public:
	//constructor
	CPoint ( int x = 0 , int y  = 0 ) ;
	CPoint ( CPoint& pt ) ;

	//destructor
	virtual ~CPoint ( ) ;

	//properties
	int& X ( ) ;
	int& Y ( ) ;

	int GetX ( ) const ;
	int GetY ( ) const ;
	void SetX ( int x ) ;
	void SetY ( int y ) ;

	//setter
	CPoint& Set ( int x , int y ) ;
	CPoint& Copy ( CPoint& pt ) ;

	//move
	CPoint& Move ( int dx , int dy ) ;
	CPoint& Add ( CPoint& pt ) ;
	CPoint& Subtract ( CPoint& pt ) ;
	
	//scale
	CPoint& Scale ( int scalar ) ;

	//distance
	int Distance ( CPoint& pt ) ;

	//operators
	//assignment
	CPoint& operator = ( CPoint& pt ) ;
	CPoint& operator += ( CPoint& pt ) ;
	CPoint& operator -= ( CPoint& pt ) ;
	CPoint& operator *= ( int scalar ) ;
	CPoint& operator /= ( int scalar ) ;

	//unary
	CPoint operator - ( ) ;
	CPoint operator + ( ) ;

	CPoint operator + ( CPoint& pt ) ;
	CPoint operator - ( CPoint& pt ) ;
	CPoint operator * ( int scalar ) ;
	CPoint operator / ( int scalar ) ;

	//comparison
	bool operator == ( CPoint& pt ) ;
	bool operator != ( CPoint& pt ) ;

};

CPoint operator * ( int scalar , CPoint& pt ) ;

//sentinel
#endif
