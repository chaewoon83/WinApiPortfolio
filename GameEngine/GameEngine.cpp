#include "GameEngine.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineLevel.h>

GameEngine* GameEngine::UserContents_ = nullptr;
GameEngineLevel* GameEngine::CurrentLevel_ = nullptr;
//Level�� �����ϴ� ���� Level�� �ٲ� �� �ֱ� ������ �������
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
    // �������ؿ��� �� �����Ӹ��� üũ�ϰ� ������
    UserContents_->GameLoop();
    // �����Լ�
    //������ �ٲ� ����
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

    // �������� �ð������� �ִ� �����̶��
    //�� �����Ӹ��� �ð��� üũ�ؾ��ϴµ� �׷��ϵ��� ��
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

