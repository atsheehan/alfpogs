// Color.cpp: implementation of the CColor class.
//
//////////////////////////////////////////////////////////////////////

#include "Color.h"

//standard constructor
CColor::CColor(Uint8 r,Uint8 g,Uint8 b)
{
	//set red
	SetR(r);
	//get green
	SetG(g);
	//set blue
	SetB(b);
	//set unused to 0
	m_Color.unused=0;
}

//copy constructor
CColor::CColor(const CColor& Color)
{
	//set red
	SetR(Color.GetR());
	//set green
	SetG(Color.GetG());
	//set blue
	SetB(Color.GetB());
	//set unused to 0
	m_Color.unused=0;
}

//destructor
CColor::~CColor()
{
}

//get rgb
Uint8 CColor::GetR() const
{
	//return red
	return(m_Color.r);
}

Uint8 CColor::GetG() const
{
	//return green
	return(m_Color.g);
}

Uint8 CColor::GetB() const
{
	//return blue
	return(m_Color.b);
}

//set rgb
void CColor::SetR(Uint8 r)
{
	//set red
	m_Color.r=r;
}

void CColor::SetG(Uint8 g)
{
	//set green
	m_Color.g=g;
}

void CColor::SetB(Uint8 b)
{
	//set blue
	m_Color.b=b;
}

//rgb accessors
Uint8& CColor::R()
{
	//return red
	return(m_Color.r);
}

Uint8& CColor::G()
{
	//return green
	return(m_Color.g);
}

Uint8& CColor::B()
{
	//return blue
	return(m_Color.b);
}

//conversion operators
CColor::operator SDL_Color()
{
	//return color
	return(m_Color);
}

CColor::operator SDL_Color*()
{
	//return pointer to color
	return(&m_Color);
}

//assignment operators
CColor& CColor::operator=(CColor& Color)
{
	//set red
	SetR(Color.GetR());
	//set green
	SetG(Color.GetG());
	//set blue
	SetB(Color.GetB());
	//return
	return(*this);
}

CColor& CColor::operator+=(CColor& Color)
{
	//temp var
	int temp;
	//add red
	temp=GetR()+Color.GetR();
	if(temp>255) temp=255;
	SetR(temp);

	//add green
	temp=GetG()+Color.GetG();
	if(temp>255) temp=255;
	SetG(temp);

	//add blue
	temp=GetB()+Color.GetB();
	if(temp>255) temp=255;
	SetB(temp);

	//return
	return(*this);
}

CColor& CColor::operator-=(CColor& Color)
{
	//temp var
	int temp;
	//add red
	temp=GetR()-Color.GetR();
	if(temp<0) temp=0;
	SetR(temp);

	//add green
	temp=GetG()-Color.GetG();
	if(temp<0) temp=0;
	SetG(temp);

	//add blue
	temp=GetB()-Color.GetB();
	if(temp<0) temp=0;
	SetB(temp);

	//return
	return(*this);
}

CColor& CColor::operator*=(CColor& Color)
{
	//temp var
	int temp;
	//add red
	temp=(GetR()*Color.GetR())/255;
	SetR(temp);

	//add green
	temp=(GetG()*Color.GetG())/255;
	SetG(temp);

	//add blue
	temp=(GetB()*Color.GetB())/255;
	SetB(temp);

	//return
	return(*this);
}

CColor& CColor::operator*=(int Multiplier)
{
	//if multiplier is non-positive
	if(Multiplier<=0)
	{
		//make color black
		(*this)=CColor(0,0,0);
	}
	else
	{
		//temp var
		int temp;
		//add red
		temp=(GetR()*Multiplier);
		SetR(temp);

		//add green
		temp=(GetG()*Multiplier);
		SetG(temp);

		//add blue
		temp=(GetB()*Multiplier);
		SetB(temp);
	}
	return(*this);
}

CColor& CColor::operator/=(int Divisor)
{
	//if divisor is non-positive
	if(Divisor<=0)
	{
		//make color black
		(*this)=CColor(0,0,0);
	}
	else
	{
		//temp var
		int temp;
		//add red
		temp=(GetR()/Divisor);
		SetR(temp);

		//add green
		temp=(GetG()/Divisor);
		SetG(temp);

		//add blue
		temp=(GetB()/Divisor);
		SetB(temp);
	}
	return(*this);
}

CColor& CColor::operator|=(CColor& Color)
{
	//do red
	SetR(GetR()|Color.GetR());
	//do green
	SetG(GetG()|Color.GetG());
	//do blue
	SetB(GetB()|Color.GetB());
	//return
	return(*this);
}

CColor& CColor::operator&=(CColor& Color)
{
	//do red
	SetR(GetR()&Color.GetR());
	//do green
	SetG(GetG()&Color.GetG());
	//do blue
	SetB(GetB()&Color.GetB());
	//return
	return(*this);
}

CColor& CColor::operator^=(CColor& Color)
{
	//do red
	SetR(GetR()^Color.GetR());
	//do green
	SetG(GetG()^Color.GetG());
	//do blue
	SetB(GetB()^Color.GetB());
	//return
	return(*this);
}

//primary colors
CColor CColor::Red(Uint8 shade)
{
	//make color
	return(CColor(shade,0,0));
}

CColor CColor::Green(Uint8 shade)
{
	//make color
	return(CColor(0,shade,0));
}

CColor CColor::Blue(Uint8 shade)
{
	//make color
	return(CColor(0,0,shade));
}

//secondary colors
CColor CColor::Yellow(Uint8 shade)
{
	//make color
	return(Red(shade)|Green(shade));
}

CColor CColor::Cyan(Uint8 shade)
{
	//make color
	return(Green(shade)|Blue(shade));
}

CColor CColor::Magenta(Uint8 shade)
{
	//make color
	return(Red(shade)|Blue(shade));
}

//dark colors
CColor CColor::DarkRed(Uint8 shade)
{
	//make color
	return(Red(shade));
}

CColor CColor::DarkGreen(Uint8 shade)
{
	//make color
	return(Green(shade));
}

CColor CColor::DarkBlue(Uint8 shade)
{
	//make color
	return(Blue(shade));
}

CColor CColor::DarkYellow(Uint8 shade)
{
	//make color
	return(Yellow(shade));
}

CColor CColor::DarkCyan(Uint8 shade)
{
	//make color
	return(Cyan(shade));
}

CColor CColor::DarkMagenta(Uint8 shade)
{
	//make color
	return(Magenta(shade));
}

//light colors
CColor CColor::LightRed(Uint8 gray,Uint8 shade)
{
	//make color
	return(Red(shade)|White(gray));
}

CColor CColor::LightGreen(Uint8 gray,Uint8 shade)
{
	//make color
	return(Green(shade)|White(gray));
}

CColor CColor::LightBlue(Uint8 gray,Uint8 shade)
{
	//make color
	return(Blue(shade)|White(gray));
}

CColor CColor::LightYellow(Uint8 gray,Uint8 shade)
{
	//make color
	return(Yellow(shade)|White(gray));
}

CColor CColor::LightCyan(Uint8 gray,Uint8 shade)
{
	//make color
	return(Cyan(shade)|White(gray));
}

CColor CColor::LightMagenta(Uint8 gray,Uint8 shade)
{
	//make color
	return(Magenta(shade)|White(gray));
}

//grayscale
CColor CColor::White(Uint8 shade)
{
	//make color
	return(Red(shade)|Green(shade)|Blue(shade));
}

CColor CColor::LightGray(Uint8 shade)
{
	//make color
	return(White(shade));
}

CColor CColor::DarkGray(Uint8 shade)
{
	//make color
	return(White(shade));
}

CColor CColor::Black(Uint8 shade)
{
	//make color
	return(White(shade));
}

//arithmetic operators
CColor operator+(CColor& Color1,CColor& Color2)
{
	//temp color
	CColor Color3;
	//assign color1
	Color3=Color1;
	//do operator with color2
	Color1+=Color2;
	//return color
	return(Color3);
}

CColor operator-(CColor& Color1,CColor& Color2)
{
	//temp color
	CColor Color3;
	//assign color1
	Color3=Color1;
	//do operator with color2
	Color1-=Color2;
	//return color
	return(Color3);
}

CColor operator*(CColor& Color1,CColor& Color2)
{
	//temp color
	CColor Color3;
	//assign color1
	Color3=Color1;
	//do operator with color2
	Color1*=Color2;
	//return color
	return(Color3);
}

CColor operator*(CColor& Color,int Multiplier)
{
	//temp color
	CColor Color3;
	//assign color1
	Color3=Color;
	//do operator with color2
	Color*=Multiplier;
	//return color
	return(Color3);
}

CColor operator/(CColor& Color,int Divisor)
{
	//temp color
	CColor Color3;
	//assign color1
	Color3=Color;
	//do operator with color2
	Color/=Divisor;
	//return color
	return(Color3);
}

//bitwise operators
CColor operator|(CColor& Color1,CColor& Color2)
{
	//temp color
	CColor Color3;
	//assign color1
	Color3=Color1;
	//do operator with color2
	Color1|=Color2;
	//return color
	return(Color3);
}

CColor operator&(CColor& Color1,CColor& Color2)
{
	//temp color
	CColor Color3;
	//assign color1
	Color3=Color1;
	//do operator with color2
	Color1&=Color2;
	//return color
	return(Color3);
}

CColor operator^(CColor& Color1,CColor& Color2)
{
	//temp color
	CColor Color3;
	//assign color1
	Color3=Color1;
	//do operator with color2
	Color1^=Color2;
	//return color
	return(Color3);
}

CColor operator~(CColor& Color)
{
	//temp color
	CColor Color3;
	//assign
	Color3=Color;
	//do operator
	Color^=CColor(255,255,255);
	//return color
	return(Color3);
}

//comparison operators
bool operator==(CColor& Color1,CColor& Color2)
{
	//do comparison
	return(Color1.GetR()==Color2.GetR()&&Color1.GetG()==Color2.GetG()&&Color1.GetB()==Color2.GetB());
}

bool operator!=(CColor& Color1,CColor& Color2)
{
	//do comparison
	return(!(Color1==Color2));
}

