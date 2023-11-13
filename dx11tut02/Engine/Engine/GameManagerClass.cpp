#include "GameManagerClass.h"

GameManagerClass::GameManagerClass()
{
	currentState = States::Start;
}

GameManagerClass::GameManagerClass(const GameManagerClass&)
{
}

GameManagerClass::~GameManagerClass()
{
}

void GameManagerClass::ChangeState(States newState)
{
	currentState = newState;
}

int GameManagerClass::GetState()
{
	return currentState;
}
