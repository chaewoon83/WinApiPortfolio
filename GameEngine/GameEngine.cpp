#include "GameEngine.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineLevel.h>

GameEngine* GameEngine::UserContents_ = nullptr;
GameEngineLevel* GameEngine::CurrentLevel_ = nullptr;
//Level을 실행하는 도중 Level이 바뀔 수 있기 때문에 만들었다
GameEngineLevel* GameEngine::NextLevel_ = nullptr;
std::map<std::string, GameEngineLevel*> GameEngine::AllLevels_;

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
    GameEngineWindow::GetInst().MessageLoop(EngineStart, EngineLoop); 
}

void GameEngine::EngineStart()
{
    UserContents_->GameInit();
}
void GameEngine::EngineLoop()
{
    // 엔진수준에서 매 프레임마다 체크하고 싶은거
    UserContents_->GameLoop();
    // 시점함수
    //레벨이 바뀐 시점
    if (nullptr != NextLevel_)
    {
        if (nullptr != CurrentLevel_)
        {
            CurrentLevel_->SceneChangeEnd();
        }
        NextLevel_->SceneChangeStart();
        CurrentLevel_ = NextLevel_;
        NextLevel_ = nullptr;
    }
    if (nullptr == CurrentLevel_)
    {
        MsgBoxAssert("Level is nullptr => GameEngine Loop Error");
    }

    // 레벨수준 시간제한이 있는 게임이라면
    //매 프레임마다 시간을 체크해야하는데 그런일들을 함
    NextLevel_->Update();
}
void GameEngine::EngineEnd()
{
    UserContents_->GameEnd();
    std::map<std::string, GameEngineLevel*>::iterator StartIter = AllLevels_.begin();
    std::map<std::string, GameEngineLevel*>::iterator EndIter = AllLevels_.end();
    for (; StartIter != EndIter; ++StartIter)
    {
        if (nullptr == StartIter->second)
        {
            continue;
        }
        delete StartIter->second;
    }
    GameEngineWindow::Destroy();
}

void GameEngine::ChangeLevel(const std::string _Name)
{
    std::map<std::string, GameEngineLevel*>::iterator FindIter = AllLevels_.find(_Name);
    if (AllLevels_.end() == FindIter)
    {
        MsgBoxAssert("Level Find Error");
        return;
    }
    NextLevel_ = FindIter->second;
}

