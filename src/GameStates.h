// The base class that all of the game states are derived from. Each contains a public Run()
// function that is called each loop.

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "sdl.h"
#include "MessageHandler.h"

class CGameState	{
public:

	// Constructor
	CGameState();

	// Destructor
	virtual ~CGameState();

	// This function is overwritten for each of the derived classes
	virtual void Run();

	// Handles input for each game state
	virtual void KeyDown( SDLKey p_sym );

	void SetMessageHandler( CMessageHandler* p_messageHandler )		{ m_messageHandler = p_messageHandler;	}
	CMessageHandler* GetMessageHandler()	{ return m_messageHandler;	}

	void SetGameStatePointer( CGameState* p_gameState )		{ m_currentState = p_gameState;	}

private:

	CMessageHandler* m_messageHandler;
	CGameState* m_currentState;

};

#endif	// GAMESTATE_H