#include "GameEngine.h"
#include <GameEngineBase/GameEngineWindow.h>
#include "GameEngineLevel.h"
#include "GameEngineImageManager.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>

GameEngine* GameEngine::UserContents_ = nullptr;
GameEngineLevel* GameEngine::CurrentLevel_ = nullptr;
//Level을 실행하는 도중 Level이 바뀔 수 있기 때문에 만들었다
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
    //윈도우의 크기가 결정남 (게임마다 윈도우의 크기가 다르기 때문에 GameInit()에서 정해진다)
    UserContents_->GameInit();
    //윈도우 크기와 같은 크기의 BackBuffer를 생성
    WindowMainImage_ = GameEngineImageManager::GetInst()->Create("WindowMainImage", GameEngineWindow::GetHDC());
    BackBufferImage_ = GameEngineImageManager::GetInst()->Create("BackBuffer", GameEngineWindow::GetScale());
}
void GameEngine::EngineLoop()
{
    GameEngineTime::GetInst()->Update();
    // 
    // 엔진수준에서 매 프레임마다 체크하고 싶은거
    UserContents_->GameLoop();
    // 시점함수
    //레벨이 바뀐 시점
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

        //레벨 로딩이 끝난 다음에 타임을 리셋 시켜준다
        GameEngineTime::GetInst()->Reset();

        Rectangle(WindowMainImage_->ImageDC(), 0, 0, WindowMainImage_->GetScale().ix(), WindowMainImage_->GetScale().iy());
        Rectangle(BackBufferImage_->ImageDC(), 0, 0, BackBufferImage_->GetScale().ix(), BackBufferImage_->GetScale().iy());
    }
    if (nullptr == CurrentLevel_)
    {
        MsgBoxAssert("Level is nullptr => GameEngine Loop Error");
    }
    //Level, Actor, Renderer가 호출되기전에 인풋 업데이트를 돌려준다
    GameEngineInput::GetInst()->Update(GameEngineTime::GetInst()->GetDeltaTime());

    // 레벨수준 시간제한이 있는 게임이라면
    //매 프레임마다 시간을 체크해야하는데 그런일들을 함
    CurrentLevel_->Update();
    CurrentLevel_->ActorUpdate();
    CurrentLevel_->ActorRender();
    CurrentLevel_->ActorRelease();
    //백버퍼의 이미지를 윈도우메인 이미지로 copy한다
    WindowMainImage_->BitCopy(BackBufferImage_);
}
void GameEngine::EngineEnd()
{
    UserContents_->GameEnd();

    //레벨 삭제
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
    //내가 원하는 순서대로 지울 수 있게 Destroy 함수를 따로 만들었다
    //이미지매니저 싱글톤 삭제
    GameEngineImageManager::Destroy();
    //윈도우 싱글톤 삭제
    GameEngineWindow::Destroy();
    //인풋 싱글톤 삭제
    GameEngineInput::Destroy();
    //타임 싱글톤 삭제
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

