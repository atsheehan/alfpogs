#ifndef __TIMER_H__
#define __TIMER_H__

#include "MessageHandler.h"

/*
	==CTimer==
	Base class for all timer classes.
*/
class CTimer : public CMessageHandler  
{
private:
	//timer id
	SDL_TimerID m_TimerID;
	//interval
	Uint32 m_Interval;
	//timer procedure
	static Uint32 TimerProc(Uint32 interval,void* param);
public:
	//constructor
	CTimer(CMessageHandler* pmhParent,Uint32 interval);
	//destructor
	virtual ~CTimer();
	//get interval
	Uint32 GetInterval();
	//set interval
	void SetInterval(Uint32 Interval);
	//get timer id
	SDL_TimerID GetTimerID();
	//start timer
	void Start();
	//stop timer
	void Stop();
	//on timer handler
	virtual void OnTimer();
};

#endif //#ifndef __TIMER_H__
