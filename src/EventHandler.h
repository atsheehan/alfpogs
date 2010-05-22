#ifndef __EVENTHANDLER_H__
#define __EVENTHANDLER_H__

#include "Application.h"

/*
	==CEventHandler==
	Event dispatching application class
*/
class CEventHandler : public CApplication  
{
public:
	//constructor
	CEventHandler();
	//destructor
	virtual ~CEventHandler();
	//event handling
	virtual void OnEvent(SDL_Event* pEvent);
	//event filtering
	virtual bool FilterEvent(SDL_Event* pEvent);
//active events
	//keyboard(input)
	virtual void OnInputFocus();
	virtual void OnInputBlur();
	//mouse
	virtual void OnMouseFocus();
	virtual void OnMouseBlur();
	//application active
	virtual void OnMinimize();
	virtual void OnRestore();
//keyboard events
	virtual void OnKeyDown(SDLKey sym,SDLMod mod,Uint16 unicode);
	virtual void OnKeyUp(SDLKey sym,SDLMod mod,Uint16 unicode);
//mouse events
	virtual void OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle);
	virtual void OnLButtonDown(Uint16 x,Uint16 y);
	virtual void OnLButtonUp(Uint16 x,Uint16 y);
	virtual void OnRButtonDown(Uint16 x,Uint16 y);
	virtual void OnRButtonUp(Uint16 x,Uint16 y);
	virtual void OnMButtonDown(Uint16 x,Uint16 y);
	virtual void OnMButtonUp(Uint16 x,Uint16 y);
//joystick events
	virtual void OnJoyAxis(Uint8 which,Uint8 axis,Sint16 value);
	virtual void OnJoyButtonDown(Uint8 which,Uint8 button);
	virtual void OnJoyButtonUp(Uint8 which,Uint8 button);
	virtual void OnJoyHat(Uint8 which,Uint8 hat,Uint8 value);
	virtual void OnJoyBall(Uint8 which,Uint8 ball,Sint16 xrel,Sint16 yrel);
//resize event
	virtual void OnResize(int w,int h);
//expose event
	virtual void OnExpose();
//user event
	virtual void OnUser(Uint8 type,int code,void* data1,void* data2);
};

#endif //#ifndef __EVENTHANDLER_H__
