// EventHandler.cpp: implementation of the CEventHandler class.
//
//////////////////////////////////////////////////////////////////////

#include "EventHandler.h"

//constructor
CEventHandler::CEventHandler()
{
	//do nothing
}

//destructor
CEventHandler::~CEventHandler()
{
	//do nothing
}

//event handling
void CEventHandler::OnEvent(SDL_Event* pEvent)
{
	//filter event
	if(FilterEvent(pEvent)) return;

	//dispatch event
	switch(pEvent->type)
	{
	case SDL_ACTIVEEVENT://activation event
		{
			//what was gained or lost?
			switch(pEvent->active.state)
			{
			case SDL_APPMOUSEFOCUS://mouse focus
				{
					//gain or loss?
					if(pEvent->active.gain)
					{
						//gain
						OnMouseFocus();
					}
					else
					{
						//loss
						OnMouseBlur();
					}
				}break;
			case SDL_APPINPUTFOCUS://input focus
				{
					//gain or loss?
					if(pEvent->active.gain)
					{
						//gain
						OnInputFocus();
					}
					else
					{
						//loss
						OnInputBlur();
					}
				}break;
			case SDL_APPACTIVE://application activation
				{
					//gain or loss?
					if(pEvent->active.gain)
					{
						//gain
						OnRestore();
					}
					else
					{
						//loss
						OnMinimize();
					}
				}break;
			}
		}break;
	case SDL_KEYDOWN://key press
		{
			//key press
			OnKeyDown(pEvent->key.keysym.sym,pEvent->key.keysym.mod,pEvent->key.keysym.unicode);
		}break;
	case SDL_KEYUP://key release
		{
			//key release
			OnKeyUp(pEvent->key.keysym.sym,pEvent->key.keysym.mod,pEvent->key.keysym.unicode);
		}break;
	case SDL_MOUSEMOTION://mouse motion
		{
			OnMouseMove(pEvent->motion.x,pEvent->motion.y,pEvent->motion.xrel,pEvent->motion.yrel,(pEvent->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT))!=0,(pEvent->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT))!=0,(pEvent->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE))!=0);
		}break;
	case SDL_MOUSEBUTTONDOWN://mouse button press
		{
			//which button?
			switch(pEvent->button.button)
			{
			case SDL_BUTTON_LEFT://left button
				{
					OnLButtonDown(pEvent->button.x,pEvent->button.y);
				}break;
			case SDL_BUTTON_RIGHT://right button
				{
					OnRButtonDown(pEvent->button.x,pEvent->button.y);
				}break;
			case SDL_BUTTON_MIDDLE://middle button
				{
					OnMButtonDown(pEvent->button.x,pEvent->button.y);
				}break;
			}
		}break;
	case SDL_MOUSEBUTTONUP://mouse button release
		{
			//which button?
			switch(pEvent->button.button)
			{
			case SDL_BUTTON_LEFT://left button
				{
					OnLButtonUp(pEvent->button.x,pEvent->button.y);
				}break;
			case SDL_BUTTON_RIGHT://right button
				{
					OnRButtonUp(pEvent->button.x,pEvent->button.y);
				}break;
			case SDL_BUTTON_MIDDLE://middle button
				{
					OnMButtonUp(pEvent->button.x,pEvent->button.y);
				}break;
			}
		}break;
	case SDL_JOYAXISMOTION://joystick axis motion
		{
			OnJoyAxis(pEvent->jaxis.which,pEvent->jaxis.axis,pEvent->jaxis.value);
		}break;
	case SDL_JOYBALLMOTION://joystick ball motion
		{
			OnJoyBall(pEvent->jball.which,pEvent->jball.ball,pEvent->jball.xrel,pEvent->jball.yrel);
		}break;
	case SDL_JOYHATMOTION://joystick hat motion
		{
			OnJoyHat(pEvent->jhat.which,pEvent->jhat.hat,pEvent->jhat.value);
		}break;
	case SDL_JOYBUTTONDOWN://joystick button press
		{
			OnJoyButtonDown(pEvent->jbutton.which,pEvent->jbutton.button);
		}break;
	case SDL_JOYBUTTONUP://joystick button release
		{
			OnJoyButtonUp(pEvent->jbutton.which,pEvent->jbutton.button);
		}break;
	case SDL_QUIT://quit event
		{
			//ignore
		}break;
	case SDL_SYSWMEVENT://window manager event
		{
			//ignore
		}break;
	case SDL_VIDEORESIZE://resize video
		{
			//resize handler
			OnResize(pEvent->resize.w,pEvent->resize.h);
		}break;
	case SDL_VIDEOEXPOSE://video expose
		{
			//expose handler
			OnExpose();
		}break;
	default://user defined
		{
			//user event handler
			OnUser(pEvent->user.type,pEvent->user.code,pEvent->user.data1,pEvent->user.data2);
		}break;
	}
}

//event filtering
bool CEventHandler::FilterEvent(SDL_Event* pEvent)
{
	//return false by default
	return(false);
}

//active events
//keyboard(input)
void CEventHandler::OnInputFocus()
{
	//do nothing
}

void CEventHandler::OnInputBlur()
{
	//do nothing
}

//mouse
void CEventHandler::OnMouseFocus()
{
	//do nothing
}

void CEventHandler::OnMouseBlur()
{
	//do nothing
}

//application active
void CEventHandler::OnMinimize()
{
	//do nothing
}

void CEventHandler::OnRestore()
{
	//do nothing
}

//keyboard events
void CEventHandler::OnKeyDown(SDLKey sym,SDLMod mod,Uint16 unicode)
{
	//do nothing
}

void CEventHandler::OnKeyUp(SDLKey sym,SDLMod mod,Uint16 unicode)
{
	//do nothing
}

//mouse events
void CEventHandler::OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle)
{
	//do nothing
}

void CEventHandler::OnLButtonDown(Uint16 x,Uint16 y)
{
	//do nothing
}

void CEventHandler::OnLButtonUp(Uint16 x,Uint16 y)
{
	//do nothing
}

void CEventHandler::OnRButtonDown(Uint16 x,Uint16 y)
{
	//do nothing
}

void CEventHandler::OnRButtonUp(Uint16 x,Uint16 y)
{
	//do nothing
}

void CEventHandler::OnMButtonDown(Uint16 x,Uint16 y)
{
	//do nothing
}

void CEventHandler::OnMButtonUp(Uint16 x,Uint16 y)
{
	//do nothing
}

//joystick events
void CEventHandler::OnJoyAxis(Uint8 which,Uint8 axis,Sint16 value)
{
	//do nothing
}

void CEventHandler::OnJoyButtonDown(Uint8 which,Uint8 button)
{
	//do nothing
}

void CEventHandler::OnJoyButtonUp(Uint8 which,Uint8 button)
{
	//do nothing
}

void CEventHandler::OnJoyHat(Uint8 which,Uint8 hat,Uint8 value)
{
	//do nothing
}

void CEventHandler::OnJoyBall(Uint8 which,Uint8 ball,Sint16 xrel,Sint16 yrel)
{
	//do nothing
}

//resize event
void CEventHandler::OnResize(int w,int h)
{
	//do nothing
}

//expose event
void CEventHandler::OnExpose()
{
	//do nothing
}

//user event
void CEventHandler::OnUser(Uint8 type,int code,void* data1,void* data2)
{
	//do nothing
}
