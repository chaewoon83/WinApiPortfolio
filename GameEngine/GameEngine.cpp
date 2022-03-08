#include "GameEngine.h"
#include <GameEngineContents/TitleLevel.h>
#include <GameEngineContents/PlayLevel.h>
#include <GameEngineContents/EndLevel.h>

GameEngine::GameEngine() 
{
}

GameEngine::~GameEngine() 
{
}


void GameEngine::GameInit()
{
	CreateLevel<TitleLevel>("Title");
	CreateLevel<PlayLevel>("Play");
	CreateLevel<EndLevel>("End");
}

void GameEngine::GameLoop()
{

}

void GameEngine::GameEnd()
{

}


