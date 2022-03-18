#include "GameEngine.h"
#include <GameEngineBase/GameEngineWindow.h>
#include "GameEngineLevel.h"
#include "GameEngineImageManager.h"

GameEngine* GameEngine::UserContents_ = nullptr;
GameEngineLevel* GameEngine::CurrentLevel_ = nullptr;
//Level�� �����ϴ� ���� Level�� �ٲ� �� �ֱ� ������ �������
GameEngineLevel* GameEngine::NextLevel_ = nullptr;
GameEngineImage* GameEngine::BackBufferImage_ = nullptr;
GameEngineImage* GameEngine:: WindowMainImage_ = nullptr;
std::map<std::string, GameEngineLevel*> GameEngine::AllLevels_;

HDC GameEngine::BackBufferDC()
{
    return BackBufferImage_->ImageDC();
}

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
    //�������� ũ�Ⱑ ������ (���Ӹ��� �������� ũ�Ⱑ �ٸ��� ������ GameInit()���� ��������)
    UserContents_->GameInit();
    //������ ũ��� ���� ũ���� BackBuffer�� ����
    WindowMainImage_ = GameEngineImageManager::GetInst()->Create("WindowMainImage", GameEngineWindow::GetHDC());
    BackBufferImage_ = GameEngineImageManager::GetInst()->Create("BackBuffer", GameEngineWindow::GetScale());
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
            CurrentLevel_->LevelChangeEnd();
        }
        NextLevel_->LevelChangeStart();
        CurrentLevel_ = NextLevel_;
        NextLevel_ = nullptr;
    }
    if (nullptr == CurrentLevel_)
    {
        MsgBoxAssert("Level is nullptr => GameEngine Loop Error");
    }

    // �������� �ð������� �ִ� �����̶��
    //�� �����Ӹ��� �ð��� üũ�ؾ��ϴµ� �׷��ϵ��� ��
    CurrentLevel_->Update();
    CurrentLevel_->ActorUpdate();
    CurrentLevel_->ActorRender();
    //������� �̹����� ��������� �̹����� copy�Ѵ�
    WindowMainImage_->BitCopy(BackBufferImage_, {0, 0}, {0, 0}, WindowMainImage_->GetScale());
}
void GameEngine::EngineEnd()
{
    UserContents_->GameEnd();

    //���� ����
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
    //�̹��� ����
    GameEngineImageManager::Destroy();\
    //������ ����
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
