//include guards
#ifndef __APPLICATION_H__
#define __APPLICATION_H__

//include message handler(base class)
#include "MessageHandler.h"

/*
	==CApplication==
	Singleton.
	Base class for all other application classes.
*/
class CApplication : public CMessageHandler  
{
private:
	//singleton pointer
	static CApplication* s_pTheApplication;

	//set singleton pointer
	static void SetApplication(CApplication* pTheApp);
public:
	//constructor
	CApplication();

	//destructor
	virtual ~CApplication();

	//initialization
	virtual bool OnInit(int argc,char* argv[]);

	//event occurrence
	virtual void OnEvent(SDL_Event* pEvent);

	//loop behavior
	virtual void OnIdle();

	//cleanup
	virtual void OnExit();

	//execution of application
	static int Execute(int argc,char* argv[]);

	//get singleton
	static CApplication* GetApplication();	
};

#endif //#ifndef __APPLICATION_H__
