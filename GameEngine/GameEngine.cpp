#include "GameEngine.h"
#include <GameEngineBase/GameEngineWindow.h>


GameEngine::GameEngine() 
{
}

GameEngine::~GameEngine() 
{
}


void GameEngine::GameInit()
{

}

void GameEngine::GameLoop()
{

}

void GameEngine::GameEnd()
{

}

void GameEngine::WindowCreate()
{
    GameEngineWindow::GetInst().CreateGameWindow(nullptr, "GameWindow");
    GameEngineWindow::GetInst().ShowGameWindow();
    //GameEngineWindow::GetInst().MessageLoop(GameInit, GameLoop);
}

void GameEngine::EngineStart()
{
    UserContents_->EngineStart();
}
void GameEngine::EngineLoop()
{

}
void GameEngine::EngineEnd()
{

}

