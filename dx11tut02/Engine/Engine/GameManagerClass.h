#pragma once
////////////////////////////////////////////////////////////////////////////////
// Filename: GameManagerClass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GAMEMANAGERCLASS_H_
#define _GAMEMANAGERCLASS_H_


//////////////
// INCLUDES //
//////////////


////////////////////////////////////////////////////////////////////////////////
// Class name: GameManagerClass.h
////////////////////////////////////////////////////////////////////////////////

enum States
{
	Start, Serve, Play, Done
};

class GameManagerClass
{
	
	int currentState;

public:

	GameManagerClass();
	GameManagerClass(const GameManagerClass&);
	~GameManagerClass();
	void ChangeState(States);
	int GetState();
};

#endif