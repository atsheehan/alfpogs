// Timer.cpp: implementation of the CTimer class.
//
//////////////////////////////////////////////////////////////////////

#include "Timer.h"

//timer procedure
Uint32 CTimer::TimerProc(Uint32 interval,void* param)
{
	//cast param
	CTimer* pTimer=(CTimer*)param;

	//call timer handler
	pTimer->OnTimer();

	//return new interval
	return(pTimer->GetInterval());
}

//constructor
CTimer::CTimer(CMessageHandler* pmhParent,Uint32 interval):
CMessageHandler(pmhParent),
m_TimerID(0),
m_Interval(0)
{
	//set the interval
	SetInterval(interval);
}

//destructor
CTimer::~CTimer()
{
	//stop the timer
	Stop();
}

//get interval
Uint32 CTimer::GetInterval()
{
	//return the current interval
	return(m_Interval);
}

//set interval
void CTimer::SetInterval(Uint32 Interval)
{
	//set new interval
	m_Interval=Interval;
}

//get timer id
SDL_TimerID CTimer::GetTimerID()
{
	//return the timer id
	return(m_TimerID);
}

//start timer
void CTimer::Start()
{
	//stop timer if already exists
	if(GetTimerID()) Stop();

	//start the timer
	m_TimerID=SDL_AddTimer(GetInterval(),CTimer::TimerProc,this);
}

//stop timer
void CTimer::Stop()
{
	//stop timer if it exists
	if(GetTimerID())
	{
		//kill the timer
		SDL_RemoveTimer(GetTimerID());
		//set timerid to 0
		m_TimerID=0;
	}
}

//on timer handler
void CTimer::OnTimer()
{
	//do nothing
}

