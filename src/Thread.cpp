// Thread.cpp: implementation of the CThread class.
//
//////////////////////////////////////////////////////////////////////

#include "Thread.h"

//start the thread(should be called by derived classes constructor)
void CThread::Start()
{
	//set running to true
	m_bRunning=true;

	//call onstart handler
	OnStart();

	//get thread pointer
	m_pThread=SDL_CreateThread(CThread::ThreadFunction,this);

	//set thread id
	m_ThreadID=SDL_GetThreadID(m_pThread);
}

//thread function
int CThread::ThreadFunction(void* data)
{
	//cast the thread
	CThread* pThread=(CThread*)data;

	//execute the thread
	int returnvalue=pThread->OnExecute();

	//stop the thread if it is still running
	if(pThread->IsRunning()) pThread->Stop();

	//return the return value
	return(returnvalue);
}

//onstart handler
void CThread::OnStart()
{
}

//onstop handler
void CThread::OnStop()
{
}

//onpause handler
void CThread::OnPause()
{
}

//onresume handler
void CThread::OnResume()
{
}

//constructor
CThread::CThread(CMessageHandler* pmhParent):
CMessageHandler(pmhParent),
m_bRunning(false),
m_bPaused(false),
m_pThread(NULL),
m_ThreadID(0)
{
}

//destructor
CThread::~CThread()
{
	//if running, stop the thread
	if(IsRunning()) Stop();
}

//get thread pointer
SDL_Thread* CThread::GetThread()
{
	//return thread pointer
	return(m_pThread);
}

//get thread id
Uint32 CThread::GetThreadID()
{
	//return thread id
	return(m_ThreadID);
}

//stop the thread
void CThread::Stop()
{
	//running is now false
	m_bRunning=false;
	//call onstop handler
	OnStop();
}

//set paused state
void CThread::Pause()
{
	//set paused to true
	m_bPaused=true;
	//call onpause handler
	OnPause();
}

void CThread::Resume()
{
	//set paused to false
	m_bPaused=false;
	//call onresume handler
	OnResume();
}

//check paused state
bool CThread::IsPaused()
{
	//return paused state
	return(m_bPaused);
}

//check running state
bool CThread::IsRunning()
{
	//return running state
	return(m_bRunning);
}

//thread procedure
int CThread::OnExecute()
{
	//do nothing
	return(0);
}

