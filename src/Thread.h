#ifndef __THREAD_H__
#define __THREAD_H__

#include "MessageHandler.h"
#include "SDL_thread.h"

/*
	==CThread==
	Base class for all user defined thread classes
*/
class CThread : public CMessageHandler  
{
private:
	//pointer to the thread
	SDL_Thread* m_pThread;
	//thread ID
	Uint32 m_ThreadID;
	//running flag
	bool m_bRunning;
	//suspended flag
	bool m_bPaused;
protected:
	//start the thread(should be called by derived classes constructor)
	void Start();
	//thread function
	static int ThreadFunction(void* data);
	//onstart handler
	virtual void OnStart();
	//onstop handler
	virtual void OnStop();
	//onpause handler
	virtual void OnPause();
	//onresume handler
	virtual void OnResume();
public:
	//constructor
	CThread(CMessageHandler* pmhParent);
	//destructor
	virtual ~CThread();
	//get thread pointer
	SDL_Thread* GetThread();
	//get thread id
	Uint32 GetThreadID();
	//stop the thread
	void Stop();
	//set paused state
	void Pause();
	void Resume();
	//check paused state
	bool IsPaused();
	//check running state
	bool IsRunning();
	//thread procedure
	virtual int OnExecute();
};

#endif //#ifndef __THREAD_H__
