// Application.cpp: implementation of the CApplication class.
//
//////////////////////////////////////////////////////////////////////

#include "Application.h"
#include <stdlib.h>

//singleton pointer
CApplication* CApplication::s_pTheApplication=NULL;

//set singleton pointer
void CApplication::SetApplication(CApplication* pTheApp)
{
	//ensure that there is not already an application
	if(s_pTheApplication!=NULL)
	{
		//more than one application!
		fprintf(stderr,"More than one CApplication created!\n");
		//exit
		exit(1);
	}
	//assign a value to the application
	s_pTheApplication=pTheApp;
}

//constructor
CApplication::CApplication():
CMessageHandler(NULL)
{
	//set the application
	SetApplication(this);
	//initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING)==-1)
	{
		//failure to initialize
		fprintf(stderr,"Failed to Init SDL:%s\n",SDL_GetError());
		//exit
		exit(1);
	}
	//set up SDL_Quit to be called during exit
	atexit(SDL_Quit);
}

//destructor
CApplication::~CApplication()
{
}

//initialization
bool CApplication::OnInit(int argc,char* argv[])
{
	//by default, simply return true
	return(true);
}

//event occurrence
void CApplication::OnEvent(SDL_Event* pEvent)
{
	//by default, do nothing
}

//loop behavior
void CApplication::OnIdle()
{
	//by default, do nothing
}

//cleanup
void CApplication::OnExit()
{
	//by default, do nothing
}

//execution of application
int CApplication::Execute(int argc,char* argv[])
{
	//check for an application
	if(GetApplication()==NULL)
	{
		//no application
		fprintf(stderr,"No application has been instantiated!\n");
		//return error code
		return(-1);
	}
	//attempt to initialize application
	if(!GetApplication()->OnInit(argc,argv))
	{
		//could not initialize
		fprintf(stderr,"Could not initialize application!\n");
		//return
		return(-1);
	}
	//event structure
	SDL_Event event;
	//forever
	for(;;)
	{
		//poll for an event
		if(SDL_PollEvent(&event)==1)
		{
			//check for a quit event
			if(event.type==SDL_QUIT) break;
			//event occurred
			GetApplication()->OnEvent(&event);
		}
		
		
		// called each loop
		GetApplication()->OnIdle();
		
	}
	//clean up
	GetApplication()->OnExit();
	//return
	return(0);
}

//get singleton
CApplication* CApplication::GetApplication()
{
	//return static pointer to application
	return(s_pTheApplication);
}

//main function
int main(int argc,char* argv[])
{
	//run the application
	return(CApplication::Execute(argc,argv));
}