#ifndef __COLOR_H__
#define __COLOR_H__

#include "sdl.h"

/*
	==CColor==
	Abstracts SDL_Color
*/
class CColor  
{
private:
	//actual color representation
	SDL_Color m_Color;
public:
	//standard constructor
	CColor(Uint8 r=0,Uint8 g=0,Uint8 b=0);
	//copy constructor
	CColor(const CColor& Color);
	//destructor
	virtual ~CColor();

	//get rgb
	Uint8 GetR() const;
	Uint8 GetG() const;
	Uint8 GetB() const;

	//set rgb
	void SetR(Uint8 r);
	void SetG(Uint8 g);
	void SetB(Uint8 b);

	//rgb accessors
	Uint8& R();
	Uint8& G();
	Uint8& B();

	//conversion operators
	operator SDL_Color();
	operator SDL_Color*();

	//assignment operators
	CColor& operator=(CColor& Color);
	CColor& operator+=(CColor& Color);
	CColor& operator-=(CColor& Color);
	CColor& operator*=(CColor& Color);
	CColor& operator*=(int Multiplier);
	CColor& operator/=(int Divisor);
	CColor& operator|=(CColor& Color);
	CColor& operator&=(CColor& Color);
	CColor& operator^=(CColor& Color);

	//primary colors
	static CColor Red(Uint8 shade=255);
	static CColor Green(Uint8 shade=255);
	static CColor Blue(Uint8 shade=255);

	//secondary colors
	static CColor Yellow(Uint8 shade=255);
	static CColor Cyan(Uint8 shade=255);
	static CColor Magenta(Uint8 shade=255);

	//dark colors
	static CColor DarkRed(Uint8 shade=128);
	static CColor DarkGreen(Uint8 shade=128);
	static CColor DarkBlue(Uint8 shade=128);
	static CColor DarkYellow(Uint8 shade=128);
	static CColor DarkCyan(Uint8 shade=128);
	static CColor DarkMagenta(Uint8 shade=128);

	//light colors
	static CColor LightRed(Uint8 gray=128,Uint8 shade=255);
	static CColor LightGreen(Uint8 gray=128,Uint8 shade=255);
	static CColor LightBlue(Uint8 gray=128,Uint8 shade=255);
	static CColor LightYellow(Uint8 gray=128,Uint8 shade=255);
	static CColor LightCyan(Uint8 gray=128,Uint8 shade=255);
	static CColor LightMagenta(Uint8 gray=128,Uint8 shade=255);

	//grayscale
	static CColor White(Uint8 shade=255);
	static CColor LightGray(Uint8 shade=192);
	static CColor DarkGray(Uint8 shade=128);
	static CColor Black(Uint8 shade=0);
};

//arithmetic operators
CColor operator+(CColor& Color1,CColor& Color2);
CColor operator-(CColor& Color1,CColor& Color2);
CColor operator*(CColor& Color1,CColor& Color2);
CColor operator*(CColor& Color,int Multiplier);
CColor operator/(CColor& Color,int Divisor);

//bitwise operators
CColor operator|(CColor& Color1,CColor& Color2);
CColor operator&(CColor& Color1,CColor& Color2);
CColor operator^(CColor& Color1,CColor& Color2);
CColor operator~(CColor& Color);

//comparison operators
bool operator==(CColor& Color1,CColor& Color2);
bool operator!=(CColor& Color1,CColor& Color2);

#endif //#ifndef __COLOR_H__
