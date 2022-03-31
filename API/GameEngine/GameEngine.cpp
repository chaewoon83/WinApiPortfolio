#include "GameEngine.h"
#include <GameEngineBase/GameEngineWindow.h>
#include "GameEngineLevel.h"
#include "GameEngineImageManager.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>

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
    GameEngineTime::GetInst()->Update();
    // 
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
        CurrentLevel_ = NextLevel_;
        if (nullptr != CurrentLevel_)
        {
            NextLevel_->LevelChangeStart();
        }
        NextLevel_ = nullptr;

        //���� �ε��� ���� ������ Ÿ���� ���� �����ش�
        GameEngineTime::GetInst()->Reset();

        Rectangle(WindowMainImage_->ImageDC(), 0, 0, WindowMainImage_->GetScale().ix(), WindowMainImage_->GetScale().iy());
        Rectangle(BackBufferImage_->ImageDC(), 0, 0, BackBufferImage_->GetScale().ix(), BackBufferImage_->GetScale().iy());
    }
    if (nullptr == CurrentLevel_)
    {
        MsgBoxAssert("Level is nullptr => GameEngine Loop Error");
    }
    //Level, Actor, Renderer�� ȣ��Ǳ����� ��ǲ ������Ʈ�� �����ش�
    GameEngineInput::GetInst()->Update(GameEngineTime::GetInst()->GetDeltaTime());

    // �������� �ð������� �ִ� �����̶��
    //�� �����Ӹ��� �ð��� üũ�ؾ��ϴµ� �׷��ϵ��� ��
    CurrentLevel_->Update();
    CurrentLevel_->ActorUpdate();
    CurrentLevel_->ActorRender();
    CurrentLevel_->ActorRelease();
    //������� �̹����� ��������� �̹����� copy�Ѵ�
    WindowMainImage_->BitCopy(BackBufferImage_);
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
    //���� ���ϴ� ������� ���� �� �ְ� Destroy �Լ��� ���� �������
    //�̹����Ŵ��� �̱��� ����
    GameEngineImageManager::Destroy();
    //������ �̱��� ����
    GameEngineWindow::Destroy();
    //��ǲ �̱��� ����
    GameEngineInput::Destroy();
    //Ÿ�� �̱��� ����
    GameEngineTime::Destroy();
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

